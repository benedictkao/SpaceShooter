cmake_minimum_required(VERSION 3.5)

project (TestGame LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(components STATIC)
target_sources(components PRIVATE
    "src/component/Vector2D.cpp"
    "src/component/GunComponent.cpp"
    "src/component/TransformComponent.cpp"
)

add_executable(main 
    "src/main.cpp" 
    "src/SDLWrapper.cpp" 
    "src/Game.cpp" 
    "src/EntityManager.cpp" 
    "src/KeyboardManager.cpp" 
    "src/PlayerController.cpp" 
    "src/TextureManager.cpp"
    "src/PositionManager.cpp"
    "src/GunManager.cpp"
    "src/EntityCleaner.cpp"
    "src/ColliderSystem.cpp"
)
target_link_libraries(main
    SDL2::SDL2
    # SDL2main runs SDL2 main function which then calls this source main
    SDL2::SDL2main
    SDL2_image::SDL2_image
    components
)