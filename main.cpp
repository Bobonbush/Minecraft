#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"



class Program {
    public :
    
        GLFWwindow* window;
        Program() {
            window = nullptr;
        }

        ~Program() {
           delete window;
        }

        void Init() {

            
            if (!glfwInit()) {
                std::cout << "Error: GLFW not initialized" << std::endl;
                return;
            }

            
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(1400, 800, "OpenGL", NULL, NULL);
            if (!window) {
                std::cout << "Error: Window not created" << std::endl;
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(window);
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Error: GLAD not initialized" << std::endl;
                glfwTerminate();
                return;
            }

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            glViewport(0, 0, 1400, 800);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        }

        void Run() {
            Init();


            float vertices[] = {
                // position               // normalize      // TexCoord
                 0.5f, 0.5f, 0.0f,     0.0f, 0.0f, -1.f,    1.0f, 1.0f,    // top right
                 0.5f, -0.5f, 0.0f,    0.0f, 0.0f, -1.f,   1.0f, 0.0f,// bottom right
                -0.5f,  -0.5f, 0.0f,   0.0f, 0.0f, -1.f,  0.0f, 0.0f,// bottom left
                -0.5f, 0.5f , 0.0f,    0.0f, 1.0f, -1.f,  0.0f , 1.0f,// top left

                 0.5f, 0.5f, 1.f,     0.0f, 0.0f, 1.f,     1.0f, 1.0f,// top right
                 0.5f, -0.5f, 1.f,    0.0f, 0.0f, 1.f,    1.0f, 0.0f,// bottom right
                -0.5f,  -0.5f, 1.f,   0.0f, 0.0f, 1.f,  0.0f, 0.0f,// bottom left
                -0.5f, 0.5f , 1.f,    0.0f, 0.0f, 1.f, 0.0f , 1.0f, // top left

                -0.5f, 0.5f, 0.0f,     -1.0f, 0.0f, 0.0f,    1.0f, 1.0f,  // top right
                -0.5f, -0.5f, 0.0f,    -1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 1.f,    -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,/// bottom left
                -0.5f, 0.5f, 1.f,     -1.0f, 0.0f, 0.0f, 0.0f , 1.0f, // top left

                0.5f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,     1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // bottom right
                0.5f, -0.5f, 1.f,      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
                0.5f, 0.5f, 1.f,       1.0f, 0.0f, 0.0f,  0.0f , 1.0f, // top left

                0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // top right
                0.5f, 0.5f, 1.f,      0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // bottom right
                -0.5f, 0.5f, 1.f,     0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f, 0.0f , 1.0f,  // top left

                0.5f, -0.5f, 0.0f,      0.0f, -1.0f, 0.0f,   1.0f, 1.0f,   // top right
                0.5f, -0.5f, 1.f,      0.0f, -1.0f, 0.0f,    1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 1.f,     0.0f, -1.0f, 0.0f,   0.0f, 0.0f,// bottom left
                -0.5f, -0.5f, 0.0f,     0.0f, -1.0f ,0.0f,  0.0f , 1.0f // top left
 




            };
            unsigned int indices[] = {
                0, 1, 3,
                1, 2, 3,

                4, 5, 7,
                5, 6, 7,

                8, 9, 11,
                9, 10, 11,

                12, 13, 15,
                13, 14, 15,

                16, 17, 19,
                17, 18, 19,

                20, 21, 23,
                21, 22, 23,

                
            };

            Shader shader("vertex.vs", "fragment.fs");
            Shader light("vertex.vs", "lightSource.fs");

            Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

            unsigned int VBO, VAO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ARRAY_BUFFER, 0);



            glBindVertexArray(0);

            unsigned int lightVao;
            glGenVertexArrays(1, &lightVao);
            glBindVertexArray(lightVao);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);


            glBindVertexArray(0);
            float lastTime = 0.0f;
            float MouseLastX = 400, MouseLastY = 300;
            bool firstMouse = true;
            glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)  
            };

            Model ourModel("Assets/backpack.obj");
            while (!glfwWindowShouldClose(window)) {

                glm::vec3 lightPos = glm::vec3(0.f + 2.f*sin(glfwGetTime()) , 0.f + 2.f* cos(glfwGetTime())   , 0.5f + 0 * cos(glfwGetTime()));
                lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
                float currentTime = glfwGetTime();
                float delta = currentTime - lastTime;
                lastTime = currentTime;

                double currentX, currentY;
                glfwGetCursorPos(window, &currentX, &currentY);
                
                if (firstMouse) {
                    MouseLastX = currentX;
                    MouseLastY = currentY;
                    firstMouse = false;
                }

                float xOffset = currentX - MouseLastX;
                float yOffset = MouseLastY - currentY;

                MouseLastX = currentX;
                MouseLastY = currentY;
                camera.ProcessMouseMovement(xOffset, yOffset);

                processInput(window, delta, camera);              
                
                shader.use();
                
                glm::mat4 projection = glm::mat4(1.0f);
                glm::mat4 view = glm::mat4(1.0f);
                glm::mat4 model = glm::mat4(1.0f);
                projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

                view =  camera.GetViewMatrix();
                shader.setMat4("projection", projection);
                shader.setMat4("view", view);
                shader.setVec3("lightPos", lightPos);
                shader.setVec3("viewPos", camera.Position);

                shader.setVec3("material.ambient", glm::vec3(1.f, 0.5f, 0.31f));
                shader.setVec3("material.diffuse", glm::vec3(1.f, 0.5f, 0.31f));
                shader.setVec3("material.specular", glm::vec3(0.f, 0.f, 0.f));
                shader.setFloat("material.shininess", 32.0f);

                

                

                glm::vec3 lightColor = glm::vec3(1.f, 1.f, 1.f);
                glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
                
                shader.setVec3("ObjectColor", objectColor);
                shader.setVec3("LightColor", lightColor);

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glBindVertexArray(VAO);

                shader.setMat4("model", model);
                
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, TextureLoader::LoadTexture("Assets/container2.png"));
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, TextureLoader::LoadTexture("Assets/container2_specular.png"));
                shader.setInt("material.diffuse", 0);
                shader.setInt("material.specular", 1);

                shader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));

                shader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
                shader.setFloat("light.constant", 1.0f);
                shader.setFloat("light.linear", 0.09f);
                shader.setFloat("light.quadratic", 0.032f);
                shader.setVec3("light.position", camera.Position);
                shader.setVec3("light.direction", camera.Front);
                shader.setFloat("light.cutoff", glm::cos(glm::radians(12.5f)));
                shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
                for(int i = 0 ; i < 10 ; i++) {
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, cubePositions[i]);
                    float angle = 20.0f * i;
                    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                    shader.setMat4("model", model);
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                }

                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
                model = glm::scale(model, glm::vec3(1.f));
                shader.setMat4("model", model);
                ourModel.Draw(shader);
                

                light.use();
                light.setMat4("projection", projection);
                light.setMat4("view", view);
                model = glm::mat4(1.0f);

                
                model = glm::translate(model, lightPos);
                model = glm::scale(model, glm::vec3(0.2f));
                
                light.setMat4("model", model);
                
                glBindVertexArray(lightVao);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

                
                
                


                
                
                //glBindVertexArray(VAO);

                //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                
                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            glfwTerminate();
        
        }


        void processInput(GLFWwindow *window, float deltaTime, Camera &camera)
        {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
        
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboard(RIGHT, deltaTime);
        }           
};


int main() {
    Program * program = new Program();
    program -> Run();    
    return 0;
}