#version 330 core
out vec4 FragColor;
uniform sampler2D texture1;


in vec2 TexCoord;
in vec3 Color;

float near = 0.1;
float far = 30.0;

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near -z * (far - near));
}

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    FragColor = texture(texture1, TexCoord) *vec4(vec3(1.0), 1.0) ;
    if(FragColor.a < 0.1)
        discard;
}