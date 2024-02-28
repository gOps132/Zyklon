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
	v_frag_position = a_Position;

	// multiply vertex coordinates a_position to model matrix to
	// transform vertex coordinates into world space

	// gl_Position = projection * view * model * vec4(a_Position, 1.0);
	gl_Position = vec4(a_Position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_frag_position;
in vec3 v_normal;

uniform vec3 light_color; // Sample light color

void main() 
{
  // Calculate a normalized vector pointing to the light source
//   vec3 light_direction = normalize(vec3(0.0, 1.0, 0.0) - v_frag_position);

  // Calculate diffuse lighting based on the dot product of light direction and normal
//   float diffuse_factor = dot(v_normal, light_direction);
//   vec3 diffuse = diffuse_factor * light_color;

  // Set the final fragment color
//   color = vec4(diffuse, 1.0); // Use the calculated diffuse color

//   color = vec4(light_color, 1.0); // Use the calculated diffuse color
  color = vec4(v_frag_position, 1.0); // Use the calculated diffuse color
}