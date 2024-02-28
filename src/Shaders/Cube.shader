#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_frag_position;
out vec3 v_normal;

void main() 
{
	v_frag_position = a_position;
	// multiply vertex coordinates a_position to model matrix to
	// transform vertex coordinates into world space

	// gl_Position = projection * view * model * vec4(a_position, 1.0f);
	gl_Position = vec4(a_position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_frag_position;

uniform vec3 light_color; // Sample light color

void main() 
{
  color = vec4(v_frag_position, 1.0); // Use the calculated diffuse color
}