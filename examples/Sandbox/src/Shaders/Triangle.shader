#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

out vec3 v_Position;
out vec4 v_Color;

void main() 
{
	v_Position = a_Position;
	v_Color = a_Color;
	gl_Position = vec4(a_Position, 1.0);
}

#shader fragment
#version 330 core

in vec3 v_Position;   
in vec4 v_Color;

layout(location = 0) out vec4 color;

void main() 
{
	color = vec4(v_Position * 0.5 + 0.5, 1.0);
	color = v_Color;
}
