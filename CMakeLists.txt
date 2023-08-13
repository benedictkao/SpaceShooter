cmake_minimum_required(VERSION 3.5)

project (TestGame LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(main "src/main.cpp" "src/SDLWrapper.cpp" "src/Game.cpp" "src/EntityManager.cpp" "src/KeyboardManager.cpp")
target_link_libraries(main SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image) # SDL2main runs SDL2 main function which then calls this source main