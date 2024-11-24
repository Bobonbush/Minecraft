#version 330 core
out vec4 FragColor;


in vec2 TexCoord;
uniform sampler2D samplerTexture;
uniform float alpha;

void main()
{
    FragColor = texture(samplerTexture, TexCoord);
}