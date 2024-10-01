#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
// layout(location = 2) in vec2 a_uv;

uniform vec3 u_color;
out vec3 v_position;
out vec4 v_color;

uniform mat4 u_view_projection;
uniform mat4 u_transform;
// uniform vec3 u_stretch;
uniform float u_time;

void main() 
{
	v_position = a_position;
	// v_color = vec4(u_color * vec3(a_uv.x, a_uv.y, a_position.y),1.0);
	v_color = vec4(u_color.x, u_color.y, u_color.z, 1.0f);
	// view on the entire viewport
	gl_Position = u_view_projection * vec4(v_position, 1.0);
	// gl_Position = u_view_projection * u_transform * vec4(v_position, 1.0);
	// gl_Position = vec4(v_position, 1.0);
}

#shader fragment
#version 330 core

in vec3 v_position;
in vec4 v_color;

layout(location = 0) out vec4 color;

void main() 
{
	color = v_color;
}
