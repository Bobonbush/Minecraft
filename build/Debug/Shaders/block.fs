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


void main()
{

    // Depth
    
    float depth = length(FragPos - viewPos) / (far - near);
    vec4 ResultColor = CalculateColor();

    FragColor = texture(texture1, TexCoord) * ResultColor ; 
    //FragColor = texture(texture1, TexCoord) * ResultColor *  vec4(vec3(depth), 1.0) ;
    if(FragColor.a < 0.5 || depth > 0.5)
        discard;
}