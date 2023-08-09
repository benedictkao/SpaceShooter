cmake_minimum_required(VERSION 3.5)

project (TestGame LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(SDL2 REQUIRED)

add_executable(main "src/main.cpp" "src/SDL.cpp" "src/Game.cpp")
target_link_libraries(main SDL2::SDL2 SDL2::SDL2main) # SDL2main runs SDL2main function which then calls this source main