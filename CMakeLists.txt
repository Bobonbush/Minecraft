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
set(Sound "irrKlang")



include_directories(${GLFW_PATH}/include)
include_directories(${GLAD_PATH}/include)
include_directories(${JSON}/include)
include_directories(${GLM_PATH})
include_directories(${Utils})
include_directories(${Script})
include_directories(${WORLD})
include_directories(${Sound}/include)
set(FreeType_PATH "FreeType")

link_directories(${GLFW_PATH}/lib-vc2022)
include_directories(${FreeType_PATH}/include)
link_directories(${FreeType_PATH}/objs)
link_directories(${Sound}/lib/Winx64-visualStudio)

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
                      Script/World/Chunk/Chunk.cpp
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
                      Script/Renderer/Skybox.cpp
                      Script/States/PlayingState.cpp
                      Script/States/Cursor.cpp
                      Script/Player/Inventory.cpp
                      Script/Renderer/hitbox.cpp
                      Script/Renderer/SpriteRenderer.cpp
                      Script/Player/Inventory.cpp
                      Script/Player/InteractiveBox.cpp
                      Script/Player/InventoryHandBox.cpp
                      Script/Player/InventoryBuilder.cpp
                      Script/Texture&Shader/TextureManager.cpp
                      Script/Texture&Shader/SoundEngine.cpp
                      Script/Item/Item.cpp
                      Script/Player/InventoryManager.cpp
)
        
target_link_libraries(OPENGL glfw3 opengl32)
target_link_libraries(OPENGL freetype)
target_link_libraries(OPENGL irrKlang)


set(ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
set(SHADERDIR "${CMAKE_CURRENT_SOURCE_DIR}/Shader")
set(AssimpDir "${CMAKE_CURRENT_SOURCE_DIR}/Assimp/bin/Release")
set(FREETYPE "${CMAKE_CURRENT_SOURCE_DIR}/FreeType/objs")
set(IRRKLANG "${CMAKE_CURRENT_SOURCE_DIR}/irrKlang/lib/Winx64-visualStudio")

add_custom_command(TARGET OPENGL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${ASSETS} $<TARGET_FILE_DIR:OPENGL>/Assets)
add_custom_command(TARGET OPENGL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${SHADERDIR} $<TARGET_FILE_DIR:OPENGL>/Shader)

add_custom_command(TARGET OPENGL POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${FREETYPE} $<TARGET_FILE_DIR:OPENGL>)

add_custom_command(TARGET OPENGL POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${IRRKLANG} $<TARGET_FILE_DIR:OPENGL>)
        
