#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

struct DirectionalLight {
	vec3 direction;
	vec3 color;
};

out vec3 v_position;
out vec3 v_color;
out vec2 v_uv;

uniform vec3 u_directional_light_color;

uniform mat4 u_view_projection;
uniform mat4 u_transform;
uniform vec3 u_stretch;
uniform float u_time;

out vec3 v_directional_light_color; 
out float v_directional_light_intensity;

void main()
{
	v_position = a_position;
	v_uv = a_uv;

	DirectionalLight directional_light;
	directional_light.direction = vec3(0.5, 0.5, -0.5 );
	directional_light.color = u_directional_light_color;

	float intensity = dot(a_normal, directional_light.direction);
	v_directional_light_intensity = (intensity > 0.0) ? intensity : 0.0;
	v_directional_light_color = directional_light.color;

	v_color = u_directional_light_color;

	gl_Position = u_view_projection * u_transform * vec4(v_position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_color;
uniform vec3 u_ambient_light_color;
uniform float u_ambient_light_intensity;
uniform float u_time;

in vec3 v_position;
in vec3 v_color;

in vec3 v_directional_light_color; 
in float v_directional_light_intensity;
in vec2 v_uv;

// Some useful functions
vec3 mod289(vec3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec2 mod289(vec2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec3 permute(vec3 x) { return mod289(((x*34.0)+1.0)*x); }

//
// Description : GLSL 2D simplex noise function
//      Author : Ian McEwan, Ashima Arts
//  Maintainer : ijm
//     Lastmod : 20110822 (ijm)
//     License :
//  Copyright (C) 2011 Ashima Arts. All rights reserved.
//  Distributed under the MIT License. See LICENSE file.
//  https://github.com/ashima/webgl-noise
//
float snoise(vec2 v) {

    // Precompute values for skewed triangular grid
    const vec4 C = vec4(0.211324865405187,
                        // (3.0-sqrt(3.0))/6.0
                        0.366025403784439,
                        // 0.5*(sqrt(3.0)-1.0)
                        -0.577350269189626,
                        // -1.0 + 2.0 * C.x
                        0.024390243902439);
                        // 1.0 / 41.0

    // First corner (x0)
    vec2 i  = floor(v + dot(v, C.yy));
    vec2 x0 = v - i + dot(i, C.xx);

    // Other two corners (x1, x2)
    vec2 i1 = vec2(0.0);
    i1 = (x0.x > x0.y)? vec2(1.0, 0.0):vec2(0.0, 1.0);
    vec2 x1 = x0.xy + C.xx - i1;
    vec2 x2 = x0.xy + C.zz;

    // Do some permutations to avoid
    // truncation effects in permutation
    i = mod289(i);
    vec3 p = permute(
            permute( i.y + vec3(0.0, i1.y, 1.0))
                + i.x + vec3(0.0, i1.x, 1.0 ));

    vec3 m = max(0.5 - vec3(
                        dot(x0,x0),
                        dot(x1,x1),
                        dot(x2,x2)
                        ), 0.0);

    m = m*m ;
    m = m*m ;

    // Gradients:
    //  41 pts uniformly over a line, mapped onto a diamond
    //  The ring size 17*17 = 289 is close to a multiple
    //      of 41 (41*7 = 287)

    vec3 x = 2.0 * fract(p * C.www) - 1.0;
    vec3 h = abs(x) - 0.5;
    vec3 ox = floor(x + 0.5);
    vec3 a0 = x - ox;

    // Normalise gradients implicitly by scaling m
    // Approximation of: m *= inversesqrt(a0*a0 + h*h);
    m *= 1.79284291400159 - 0.85373472095314 * (a0*a0+h*h);

    // Compute final noise value at P
    vec3 g = vec3(0.0);
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.yz = a0.yz * vec2(x1.x,x2.x) + h.yz * vec2(x1.y,x2.y);
    return 130.0 * dot(m, g);
}

void main() 
{
	vec3 ambient_color = u_ambient_light_color * u_ambient_light_intensity;
	vec3 diffuse_color =  v_directional_light_color * v_directional_light_intensity;
	vec3 lighting_color = u_color * (ambient_color + diffuse_color);

	vec2 st = v_uv;

	// scale to see the pattern 
	st *= 5.0;

    vec3 pattern_color = vec3(snoise(st + u_time)*.5+.5) + u_color;
	vec3 final_color = mix(lighting_color, pattern_color, 0.5); // Blend lighting with pattern

	color = vec4(final_color, 1.0);
}
