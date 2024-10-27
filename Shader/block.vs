#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTransition;
layout (location = 4) in vec3 aNormal;
out vec2 TexCoord;
  
out vec3 ourColor;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{   


    
    vec4 ActualPos = model * vec4(aPos, 1.0) ;
    vec4 pos = vec4(ActualPos.x + aTransition.x, ActualPos.y + aTransition.y, ActualPos.z + aTransition.z,ActualPos.w);
    gl_Position = projection * view * pos ; 
    ourColor = aColor;
    TexCoord = aTexCoord;

    FragPos = vec3(pos);
    Normal = mat3(transpose(inverse(model))) * aNormal;

    
} 