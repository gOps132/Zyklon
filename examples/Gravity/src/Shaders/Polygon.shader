#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec3 v_world_normal;
out vec3 v_world_position;
out vec2 v_uv;

uniform mat4 u_view_projection;
uniform mat4 u_model; // Assuming u_transform is now passed as u_model
uniform mat3 u_normal_matrix; // Needed for correct normal transformation

void main()
{
    // Transform vertex position to world space
    vec4 world_pos = u_model * vec4(a_position, 1.0);
    v_world_position = world_pos.xyz;

    // Transform normal to world space (using normal matrix for non-uniform scaling)
    v_world_normal = u_normal_matrix * a_normal;

    v_uv = a_uv;

    gl_Position = u_view_projection * world_pos;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

// Material uniforms from BasicLitMaterial.cpp
uniform vec3 u_Color; // Matches m_color
uniform sampler2D u_Texture; // Matches m_texture (sampler unit is set via setUniform1i)

// Ambient Light uniforms from BasicLitMaterial.cpp
uniform vec3 u_AmbientLightColor;
uniform float u_AmbientLightIntensity;

// Directional Light uniforms from BasicLitMaterial.cpp
uniform vec3 u_DirectionalLightDirection; // Direction FROM the light source
uniform vec3 u_DirectionalLightColor;

in vec3 v_world_normal;
in vec3 v_world_position;
in vec2 v_uv;

void main() 
{
    vec3 normal = normalize(v_world_normal);

    // Light direction (normalize since it's a direction, not a position)
    // Assuming u_DirectionalLightDirection points FROM the light source towards the scene
    vec3 light_direction = normalize(-u_DirectionalLightDirection); 

    // Material Albedo (base color), combined with texture
    vec3 material_albedo = u_Color * texture(u_Texture, v_uv).rgb;

    // 1. Ambient Lighting
    vec3 ambient_component = u_AmbientLightColor * u_AmbientLightIntensity * material_albedo;

    // 2. Diffuse Lighting
    float diffuse_factor = max(dot(normal, light_direction), 0.0);
    vec3 diffuse_component = u_DirectionalLightColor * diffuse_factor * material_albedo;

    // Final color (only ambient + diffuse based on your C++ material)
    vec3 final_rgb_color = ambient_component + diffuse_component;

    color = vec4(final_rgb_color, 1.0);
}