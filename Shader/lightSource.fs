#version 330 core
out vec4 FragColor;
  
uniform vec3 LightColor;
uniform vec3 ObjectColor;
in vec2 TexCoord;


void main()
{
    FragColor = vec4( 1.0);
    //FragColor = texture(ourTexture, TexCoord);
}