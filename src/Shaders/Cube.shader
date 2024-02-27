#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec3 v_Position;
out vec3 v_Normal;

void main() 
{
	v_Position = a_Position;
	v_Normal = a_Normal;

	gl_Position = vec4(a_Position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec3 v_Normal;

void main() 
{
	// color = vec4(0.2, 0.3, 0.8, 1.0);
	color = vec4(v_Normal, 1.0);
}