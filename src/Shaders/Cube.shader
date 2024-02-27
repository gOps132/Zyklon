#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_frag_position;
out vec3 v_normal;

void main() 
{
	v_normal = a_Normal;

	// vec4 new_pos = model * vec4(a_Position, 1.0);
	// v_frag_position = new_pos
	// v_normal = normalize(mat3(transpose(inverse(model)) * a_Normal));

	// gl_Position = projection * view * vec4(new_pos, 1.0);

	vec4 world_position = model * vec4(a_Position, 1.0);
	vec4 clip_position = projection * view * world_position;

	v_frag_position = vec3(clip_position.x, clip_position.y, clip_position.z);

	gl_Position = clip_position;

	// gl_Position = vec4(a_Position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
// in vec3 v_frag_position;
in vec3 v_normal;

// vec3 light_color = vec3(0.1,0.1,0.1);

void main() 
{
	// calculate lighting
	// float ambient_strength = 0.1;
	// vec3 ambient = light_color * ambient_strength;
	// vec3 normalize = normalize(v_normal);
	// vec3 lightDir = normalize( - FragPos);
    // float diffuseStrength = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = lightColor * diffuseStrength;

    // vec3 diffuse = light_color;

    // color = vec4(ambient + diffuse, 1.0);

	color = vec4(0.2,0.3,0.4, 1.0);
}