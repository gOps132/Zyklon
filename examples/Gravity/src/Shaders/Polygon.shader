#shader vertex
#version 330 core

// Input attributes from your vertex array layout
layout(location = 0) in vec3 a_position; // Vertex position in object's local space
layout(location = 1) in vec3 a_normal;   // Vertex normal in object's local space
layout(location = 2) in vec2 a_uv;       // Texture UV coordinates

// Outputs (varyings) to be interpolated and passed to the fragment shader
out vec3 v_world_normal;        // Normalized normal vector in world space
out vec3 v_world_position;      // Vertex position in world space
out vec2 v_uv;                  // Texture UVs

// Uniforms (data passed from C++ per draw call or scene)
uniform mat4 u_view_projection;   // Combined View and Projection matrix (from camera)
uniform mat4 u_model;             // Model matrix (transforms object from local to world space)
uniform mat3 u_normal_matrix;     // Normal matrix (inverse transpose of the 3x3 u_model matrix)
                                  // This is crucial for correctly transforming normals under non-uniform scaling.

// Note: Removed u_DirectionalLightColor, u_DirectionalLightDirection, u_Color, u_time, u_Texture
//       from the vertex shader as they are primarily used for lighting/texturing in the fragment shader.
//       Also removed v_color, v_directional_light_color, v_directional_light_intensity outputs
//       as lighting will be computed entirely in the fragment shader.

void main()
{
    // 1. Transform vertex position from local space to world space
    //    We use vec4(a_position, 1.0) because positions are points and need a W component of 1.
    vec4 world_pos = u_model * vec4(a_position, 1.0);
    v_world_position = world_pos.xyz; // Pass world position to fragment shader

    // 2. Transform normal from local space to world space
    //    We use the normal_matrix here. Normals are directions, so the W component is 0.
    //    This must be normalized to ensure it remains a unit vector after interpolation.
    v_world_normal = u_normal_matrix * a_normal;

    // 3. Pass texture UVs directly to the fragment shader
    v_uv = a_uv;

    // 4. Calculate the final clip-space position for rendering
    gl_Position = u_view_projection * world_pos;
}

#shader fragment
#version 330 core

// Output to the framebuffer (usually screen)
layout(location = 0) out vec4 color;

// Uniforms (material properties, set by BasicLitMaterial::bind())
uniform vec3 u_Color;        // This is your base material color (albedo)
uniform sampler2D u_Texture; // The texture sampler

// Uniforms for Ambient Light (set by BasicLitMaterial::bind() or other scene lighting setup)
uniform vec3 u_AmbientLightColor;
uniform float u_AmbientLightIntensity;

// Uniforms for Directional Light (set by BasicLitMaterial::bind() or other scene lighting setup)
uniform vec3 u_DirectionalLightDirection; // Direction FROM the light source (in world space)
uniform vec3 u_DirectionalLightColor;     // Color of the directional light

// Inputs (varyings) interpolated from the vertex shader for the current fragment
in vec3 v_world_normal;     // Interpolated normal in world space
in vec3 v_world_position;   // Interpolated position in world space
in vec2 v_uv;               // Interpolated texture UV

void main() 
{
    // Ensure the normal is a unit vector. It's often normalized here due to interpolation issues.
    vec3 normal = normalize(v_world_normal);

    // Calculate the direction from the fragment to the light source.
    // We negate u_DirectionalLightDirection because it's defined as pointing *FROM* the light.
    vec3 light_direction = normalize(-u_DirectionalLightDirection); 

    // --- How u_Color is used as the base color ---
    // The material's base color (albedo) is a combination of the uniform u_Color
    // and the color sampled from the texture at the current UV coordinate.
	vec4 tex = texture(u_Texture, v_uv);
    vec3 material_albedo = u_Color * tex.rgb;

    // --- Lighting Calculations ---

    // 1. Ambient Lighting Component
    //    This provides a basic, non-directional illumination, ensuring parts of the model
    //    not directly hit by diffuse light are still visible.
    vec3 ambient_component = u_AmbientLightColor * u_AmbientLightIntensity * material_albedo;

    // 2. Diffuse Lighting Component
    //    This simulates the light scattering off the surface based on the angle between
    //    the surface normal and the light direction.
    //    max(..., 0.0) ensures we don't get negative light if the light is behind the surface.
    float diffuse_factor = max(dot(normal, light_direction), 0.0);
    vec3 diffuse_component = u_DirectionalLightColor * diffuse_factor * material_albedo;

    // 3. Final Color
    //    The total light applied to the material's albedo.
    vec3 final_rgb_color = ambient_component + diffuse_component;

    // Output the final calculated color for the fragment, with full opacity.
    color = tex;
}