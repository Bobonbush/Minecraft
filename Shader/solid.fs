#version 330 core
out vec4 FragColor;

float fog_maxdist = 2200.0;
float fog_mindist = 0.01;
float fog_density = 0.02;
float gradient = 2.;

vec4 fogColor = vec4(0.01 ,  0.01 ,  0.1  , 1.0);

in vec2 TexCoord;
uniform sampler2D samplerTexture;
uniform float alpha;
in vec4 positionRelativeToCamera;



void main()
{
    FragColor = texture(samplerTexture, TexCoord);
    float dist = length(positionRelativeToCamera.xyz);
    float visibility = exp(-pow(dist * fog_density, gradient)); 

    
    if(visibility  < 0.000001) {
        //discard;
    }
    if(visibility  > 1.02) {
        discard;
    }
    
    if(visibility > 2.0) {
        discard;
    }
    

    visibility = clamp(visibility, 0.0, 1.0);
    
    FragColor = mix(FragColor, fogColor, 1 - visibility);
    if(FragColor.a < 0.1) discard;
}