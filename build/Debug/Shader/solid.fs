#version 330 core
out vec4 FragColor;

float fog_density = 0.02;
float gradient = 2.;

vec4 fogColor = vec4( 0.6 ,  0.6 ,  0.6  , 1.0);

in vec2 TexCoord;
uniform sampler2D samplerTexture;
in vec4 positionRelativeToCamera;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor = vec3(0.6,  0.6 ,  0.6);

float ambientStrength = 0.5;
float specularStrength = 0.5;
float shininess = 32.0;

float getFogFactor(float dist, float farPlane)
{
    float FogMax = 1.0 * farPlane;
    float FogMin = 0.5 * farPlane;
    if(dist > FogMax) return 1.0;
    if(dist < FogMin) return 0.0;   
    return (dist - FogMin) / (FogMax - FogMin);
}

float getFogFactorAlpha(float d , float nearPlane, float farPlane) {
    float FogMax = 1.0 * farPlane;
    float FogMin = 0.75 * farPlane;

    if(d > FogMax) return 1.0;
    if(d < FogMin) return 0.0;

    return (d - FogMin) / (FogMax - FogMin);
}


vec3 lightCalculation(vec3 normal, vec3 lightDir, vec3 viewDir)
{
    vec3 ambient = ambientStrength * lightColor;
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;



    vec3 result = ambient + diffuse + specular;
    return result;

}



void main()
{
    FragColor = texture(samplerTexture, TexCoord);
    float dist = length(positionRelativeToCamera.xyz);
    if(FragColor.a < 0.1)
    {
        discard;
    }

    float visibility = getFogFactor(dist, 160.0);
    float alpha = getFogFactorAlpha(dist, 0.1, 160.0);
    
    
    

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos); 
    vec3 result = lightCalculation(norm, lightDir, viewDir);
    FragColor = FragColor * vec4(result, 1.0);
    FragColor = mix(FragColor, fogColor, visibility);
    FragColor.a *= 1 - alpha;
    
    if(FragColor.a < 0.1)
    {
        discard;
    }
}