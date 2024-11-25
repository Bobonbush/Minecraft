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
set(Script "Script")
set(JSON "json-develop")
set(WORLD "Script/World")



include_directories(${GLFW_PATH}/include)
include_directories(${GLAD_PATH}/include)
include_directories(${JSON}/include)
include_directories(${GLM_PATH})
include_directories(${Utils})
include_directories(${Script})
include_directories(${WORLD})

link_directories(${GLFW_PATH}/lib-vc2022)


add_executable(OPENGL Script/main.cpp
                      GLAD/src/glad.c
                      Script/Utils/Shader.cpp 
                      Script/Utils/Texture.cpp
                      Script/Model.cpp
                      Script/Mesh.cpp
                      Script/Application.cpp
                      Script/Renderer/RenderInfo.h
                      Script/Physics/AABB.cpp
                      Script/Entity.cpp
                      Script/Mesh.cpp
                      Script/Model.cpp
                      Script/Algorithm.h
                      Script/Utils/Singleton.h
                      Script/Renderer/RenderMaster.cpp
                      Script/Utils/Camera.cpp
                      Script/Config.cpp
                      Script/Utils/File.cpp
                      Script/Texture&Shader/TextureBind.cpp
                      Script/Renderer/QuadRenderer.cpp
                      Script/Texture&Shader/TextureBind.cpp
                      Script/Texture&Shader/ShaderManager.cpp
                      Script/States/StateBase.h
                      Script/Player/player.cpp
                      Script/Texture&Shader/TextureAtlas.cpp
                      Script/Renderer/CubeRenderer.cpp
                      Script/World/Block/BlockDatabase.cpp
                      Script/World/Block/BlockData.cpp
                      Script/World/Block/Block.cpp
                      Script/World/Block/BlockType.cpp
                      Script/World/Block/ChunkBlock.cpp
                      Script/World/Chunk/ChunkBuilder.cpp
                      Script/World/Chunk/ChunkMesh.cpp
                      Script/World/Chunk/Chunk.h
                      Script/World/Chunk/ChunkSection.cpp
                      Script/Renderer/ChunkRenderer.cpp
                      Script/Maths/FastNoise.cpp
                      Script/World/World.cpp
                      Script/World/Chunk/ChunkManager.cpp
                      Script/Physics/PhysicCons.cpp
                      Script/Physics/RigidBody.cpp
                      Script/States/SceneState.cpp
                      Script/Maths/Ray.cpp
                      Script/World/WorldGenerator/Terrain.cpp
                      Script/World/WorldGenerator/Biome/Biome.cpp
                      Script/World/WorldGenerator/Biome/Ocean.cpp
                      Script/World/WorldGenerator/Biome/grassland.cpp
                      Script/World/WorldGenerator/Biome/highMountain.cpp
                      Script/World/WorldGenerator/Biome/Desert.cpp
                      Script/Maths/Frustum.cpp
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
                       ${SHADERDIR} $<TARGET_FILE_DIR:OPENGL>/Shader)
        
