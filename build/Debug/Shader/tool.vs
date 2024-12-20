#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
out vec2 TexCoord;
out vec3 Normal;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 positionRelativeToCamera;
out vec3 FragPos;




void main()
{
    
    gl_Position = projection * view * model * vec4(aPos, 1.0) ;
    positionRelativeToCamera = view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal;  

    FragPos = vec3(model * vec4(aPos, 1.0));
} 