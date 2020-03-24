cmake_minimum_required(VERSION 3.15)
project(Pong)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED SDL2)

add_executable(Pong src/main.cpp src/Game.cpp inc/Game.hpp src/GameObject.cpp inc/GameObject.hpp src/TextureManager.cpp inc/TextureManager.hpp src/ScoreManager.cpp inc/ScoreManager.hpp src/AILogic.cpp inc/AILogic.hpp inc/IEntity.hpp)

target_link_libraries(Pong
        PRIVATE SDL2
        PRIVATE SDL2_image
        PRIVATE SDL2_ttf)