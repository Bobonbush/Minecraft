cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OPENGL)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Specify the path to GLFW
set(GLFW_PATH "GLFW")
set(GLAD_PATH "GLAD")
set(GLM_PATH "GLM")
set(Utils "Script/Utils")
set(Game "Script/Game")
set(Script "Script")



include_directories(${GLFW_PATH}/include)
include_directories(${GLAD_PATH}/include)
include_directories(${GLM_PATH})
include_directories(${Utils})
include_directories(${Game})
include_directories(${Script})


link_directories(${GLFW_PATH}/lib-vc2022)


add_executable(OPENGL Script/main.cpp
                      GLAD/src/glad.c
                      Script/Utils/shader.cpp
                      Script/Utils/Texture.cpp 
                      Script/Utils/Camera.h
                      Script/Game/game.cpp 
                      Script/Game/Player.cpp
                      Script/Settings.cpp
                      Script/Game/Blocks.cpp
                      Script/Algorithm.h
                      Script/Resource/ShaderLoad.cpp
                      Script/Resource/TextureLoad.cpp
                      Script/Resource/PerlinNoise.cpp
                      Script/Resource/db_perlin.hpp
                      Script/Game/world.cpp
                      Script/Physic/rigidbody.cpp
                      Script/Physic/PhysicVariable.cpp
                      Script/Game/Chunks.cpp
                      Script/Game/skybox.cpp
                      Script/Game/mapGen.cpp
                      
)
        
target_link_libraries(OPENGL glfw3 opengl32)


set(ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
set(SHADERDIR "${CMAKE_CURRENT_SOURCE_DIR}/Shader")
set(AssimpDir "${CMAKE_CURRENT_SOURCE_DIR}/Assimp/bin/Release")

add_custom_command(TARGET OPENGL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${ASSETS} $<TARGET_FILE_DIR:OPENGL>/Assets)
add_custom_command(TARGET OPENGL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${SHADERDIR} $<TARGET_FILE_DIR:OPENGL>/Shaders)
        
