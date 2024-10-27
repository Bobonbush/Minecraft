#version 330 core
out vec4 FragColor;
uniform sampler2D texture1;


in vec2 TexCoord;
in vec3 Color;

float near = 0.1;
float far = 100.0;

uniform vec3 lightColor = vec3(1.0);
uniform vec3 lightPos = vec3(0.0, 0.0, 0.0);


vec4 CalculateColor() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient;

    return vec4(result, 1.0);
}

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near -z * (far - near));
}

void main()
{

    // Depth
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    vec4 ResultColor = CalculateColor();

    FragColor = texture(texture1, TexCoord) * ResultColor; 
    //FragColor = texture(texture1, TexCoord) * ResultColor *  vec4(vec3(depth), 1.0) ;
    if(FragColor.a < 0.1)
        discard;
}