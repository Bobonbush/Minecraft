#version 330 core
out vec4 FragColor;

uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 viewPos;


in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;




struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutoff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
void main()
{

    
    vec3 norm = normalize(Normal);

    vec3 lightDir = normalize(light.position - FragPos);

    float theta = dot(lightDir, normalize(-light.direction));
    

    float epsilon = light.cutoff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 diffuse =   light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    vec3 ambient =  vec3(texture(material.diffuse, TexCoord)) * light.ambient;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  light.specular *spec *  vec3(texture(material.specular , TexCoord)) ;
    diffuse *= intensity;
    specular *= intensity;
    vec3 result = (ambient + diffuse + specular) * attenuation  ;
    FragColor = vec4(result, 1.0);




    
    
}