#version 330 core
out vec4 FragColor;
uniform sampler2D texture1;


in vec2 TexCoord;
in vec3 Color;

in vec3 FragPos;
in vec3 Normal;

float near = 0.1;
float far = 300.0;

uniform vec3 lightColor = vec3(1.0);
uniform vec3 lightPos = vec3(0.0, 0.0, 0.0);
vec3 FogColor = vec3(0.1, 0.1, 0.1);


uniform vec3 viewPos = vec3(0.0, 0.0, 0.0);
uniform float linear = 0.014;
uniform float quadratic = 0.007;
uniform float constant = 1.0;
float specularStrength = 0.5;


vec4 CalculateColor() {
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;



    vec3 result = ambient + diffuse; 

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 distance = normalize(lightPos - FragPos);
    float distanceToLight = length(distance);
    float attenuation = 1.0 / (constant + linear * distanceToLight + quadratic * (distanceToLight * distanceToLight));

    result += specular;
    result *= attenuation;
    return vec4(result, 1.0);
}

float getFogFactor(float d) {
    const float fogDensity = 0.1;
    const float fogStart = 0.0;
    const float fogEnd = 100.0;
    float f = exp2(-d * fogDensity);
    if(d <= fogStart)
        return 0.0;
    if(d >= fogEnd)
        return 1.0;

    return 1 - (fogEnd - d) * (fogEnd - fogStart);


}


void main()
{

    // Depth
    
    float depth = length(FragPos - viewPos) / (far - near);
    vec4 ResultColor = CalculateColor();
    float d = length(FragPos - viewPos);
    float fogFactor = getFogFactor(d);

    
    FragColor = texture(texture1, TexCoord) * ResultColor;
    //FragColor = mix(texture(texture1, TexCoord) * ResultColor , vec4(FogColor, 1.f), fogFactor);
    //FragColor = mix(texture(texture1, TexCoord) * ResultColor , vec4(FogColor, fogFactor),  fogFactor);
    if(FragColor.a < 0.5)
        discard;
}