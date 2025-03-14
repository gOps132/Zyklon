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

// Uniforms for lighting
uniform vec3 u_color;
uniform vec3 u_ambient_light_color;
uniform float u_ambient_light_intensity;

// Uniforms for procedural pattern
uniform vec2 u_resolution;
uniform float u_time;

// Inputs
in vec3 v_position; // Object space position passed from the vertex shader
in vec3 v_color;
in vec3 v_directional_light_color; 
in float v_directional_light_intensity;

// Utility Functions
float random(in vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(
        mix(random(i + vec2(0.0, 0.0)), random(i + vec2(1.0, 0.0)), u.x),
        mix(random(i + vec2(0.0, 1.0)), random(i + vec2(1.0, 1.0)), u.x),
        u.y
    );
}

mat2 rotate2d(float angle) {
    return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}

float lines(in vec2 pos, float b) {
    float scale = 1.0;
    pos *= scale;
    return smoothstep(0.0, .5 + b * .5, abs((sin(pos.x * 3.1415) + b * 2.0)) * .5);
}

void main() 
{
    // Calculate lighting colors
    vec3 ambient_color = u_ambient_light_color * u_ambient_light_intensity;
    vec3 diffuse_color = v_directional_light_color * v_directional_light_intensity;
    vec3 lighting_color = ambient_color + diffuse_color;

    // Use object-space position for procedural pattern
    vec3 pos = v_position; // Object-space coordinates

    // Scale and transform the position for better texture detailing
    vec2 st = pos.xy * 10.0; // Use X and Y from object space (scale by 10.0 for detail)
    st = rotate2d(noise(st + u_time * 0.5)) * st; // Animated noise-based rotation

    // Generate procedural pattern
    float pattern = lines(st, 0.1);

    // Combine procedural effect with lighting
    vec3 final_color = mix(lighting_color, vec3(pattern) + u_color, 0.5); // Blend lighting with pattern
    color = vec4(final_color, 1.0);
}
