#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

uniform vec3 skyColor = vec3(1.0);

void main()
{    
    FragColor = texture(skybox, TexCoords) * vec4(skyColor, 1.0);
}