cmake_minimum_required(VERSION 3.5)

project (TestGame LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_library(sdl STATIC)
target_sources(sdl PRIVATE "src/sdl/SDLWrapper.cpp")
target_include_directories(sdl PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(sdl INTERFACE "${PROJECT_SOURCE_DIR}/src/sdl")
target_link_libraries(sdl PUBLIC SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)
target_link_libraries(sdl INTERFACE SDL2::SDL2main) # SDL2main runs SDL2 main function which then calls the source main

add_library(components STATIC)
target_sources(components PRIVATE
    "src/component/Vector2D.cpp"
    "src/component/PathComponent.cpp"
)
target_include_directories(components INTERFACE "${PROJECT_SOURCE_DIR}/src/component")

add_library(systems STATIC)
target_sources(systems PRIVATE 
    "src/system/TextureSystem.cpp"
    "src/system/PositionSystem.cpp"
    "src/system/GunSystem.cpp"
    "src/system/ColliderSystem.cpp"
    "src/system/SystemManager.cpp"
)
target_link_libraries(systems PRIVATE sdl components)
target_include_directories(systems PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(systems INTERFACE "${PROJECT_SOURCE_DIR}/src/system")

add_executable(SpaceShooter 
    "src/main.cpp" 
    "src/Game.cpp"
    "src/EnemyManager.cpp"
    "src/EntityManager.cpp" 
    "src/PlayerController.cpp" 
    "src/KeyboardManager.cpp" 
    "src/TextureRepo.cpp"
    "src/LevelManager.cpp"
    "src/TextRenderer.cpp"
    "src/BackgroundManager.cpp"
    "src/MusicManager.cpp"
)
target_link_libraries(SpaceShooter
    sdl
    components
    systems
)
## Below line removals terminal window from executable
target_link_options(SpaceShooter PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")