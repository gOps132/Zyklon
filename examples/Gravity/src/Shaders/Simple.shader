#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position; // Vertex position

uniform mat4 u_view_projection; // Combined View-Projection Matrix from camera
uniform mat4 u_transform;           // Model Matrix for the object

void main()
{
    // Transform the vertex position by the model, view, and projection matrices
    gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; // Output color of the fragment

uniform vec3 u_Color; // A uniform color (e.g., from BasicLitMaterial::m_color)

void main() 
{
    // Output a solid color using the uniform color, with full opacity
    color = vec4(u_Color, 1.0);
}