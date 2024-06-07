#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 fragPos;
out vec2 v_uv;

// TODO: replace with global transform
// uniform mat4 model;

uniform mat4 u_view_projection;
uniform mat4 u_transform;

void main()
{
	// vec4 world_space = model * vec4(aPos, 1.0f);
	
	v_uv = vec2(aTexCoord.x, aTexCoord.y);
	fragPos = aPos;

	// gl_Position = view_projection * world_space;

	gl_Position = u_view_projection * u_transform * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec2 v_uv;

uniform float u_time;
uniform vec2 u_params;

// adapted from https://thebookofshaders.com/edit.php#10/ikeda-simple-grid.frag
float grid(vec2 st, float res)
{
  vec2 grid = fract(st*res);
  return (step(res,grid.x) * step(res,grid.y));
}

void main()
{
	vec2 grid_uv = v_uv.xy * u_params.x; // scale
	float x = grid(grid_uv, u_params.y); // resolution
	FragColor.rgb = vec3(0.5) * x;  
	FragColor.a = 1.0;

	// FragColor = vec4(v_uv.x * cos(u_time),v_uv.x,v_uv.y, 1.0);
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	// FragColor = mix(texture(texture1, v_uv), texture(texture2, v_uv), 0.2);
}