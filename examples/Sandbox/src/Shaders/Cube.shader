#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 fragPos;
out vec2 TexCoord;

// TODO: replace with global transform
// uniform mat4 model;

uniform mat4 u_view_projection;
uniform mat4 u_transform;

void main()
{
	// vec4 world_space = model * vec4(aPos, 1.0f);
	
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	fragPos = aPos;

	// gl_Position = view_projection * world_space;

	gl_Position = u_view_projection * u_transform * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec2 TexCoord;

uniform float u_time;

// texture samplers
// uniform sampler2D texture1;
// uniform sampler2D texture2;

void main()
{
	FragColor = vec4(TexCoord.x * sin(u_time),TexCoord.y,TexCoord.y, 1.0);
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}