#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
    FragColor = mix(FragColor, vec4(0.01 ,  0.01 ,  0.1  , 1.0), 0.45);
}