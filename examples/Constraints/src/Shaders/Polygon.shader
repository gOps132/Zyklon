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

uniform sampler2D u_Texture;

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

	float displacement = texture(u_Texture, v_uv).r;
	vec3 displaced_position = v_position + a_normal  * displacement;

	gl_Position = u_view_projection * u_transform * vec4(v_position, 1.0);
	// gl_Position = u_view_projection * u_transform * vec4(displaced_position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_color;
uniform vec3 u_ambient_light_color;
uniform float u_ambient_light_intensity;
uniform sampler2D u_Texture;

in vec3 v_position;
in vec3 v_color;

in vec3 v_directional_light_color; 
in float v_directional_light_intensity;
in vec2 v_uv;

void main() 
{
	vec3 ambient_color = u_ambient_light_color * u_ambient_light_intensity;
	vec3 diffuse_color =  v_directional_light_color * v_directional_light_intensity;
	vec3 final_color = u_color * (ambient_color + diffuse_color);

	vec4 texture_color = texture(u_Texture, v_uv);

	color = vec4(final_color, 1.0) * texture_color;
	// color = vec4(vec3(v_uv.x, v_uv.y, v_uv.x * v_uv.y), 1.0);

	// color = vec4(final_color, 1.0);
}

