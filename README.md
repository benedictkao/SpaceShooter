# Space Shooter

## Summary

Simple space-themed shoot-em-up game written in C++ to practice data-driven ECS architecture and low-level SDL graphics and music libraries.

## Demo

![Demo](https://github.com/benedictkao/SpaceShooter/tree/master/demo/space-shooter-demo.mp4)

## External Libraries
* [SDL2](https://github.com/libsdl-org/SDL) to create window and renderer
* [SDL2_image](https://github.com/libsdl-org/SDL_image) to load png images for sprites
* [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf) to load ttf fonts fortexts
* [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer) to load wav and mp3 files for music

## How to Compile

### Windows (Visual Studio)

1. Clone this repo
2. Download the above external libraries from the GitHub pages linked in the [External Libraries](#external-libraries) section.
3. Add `CMAKE_PREFIX_PATH` as an environment variable and add the libraries' location(s) to that path
4. Put all the `.dll` files from all of the downloaded libraries into the output directories of the build target (this is defined as `"{PROJECT_SOURCE_DIR}/out/build/{BUILD_TARGET}"` in the `CMakePresets.json` file included in this project
5. Build and run either through Visual Studio Code or command line

### Mac

1. Clone this repo
2. Install the required libraries with the below commands:
```
brew install SDL2
brew install SDL2_image
brew install SDL2_ttf
brew install SDL2_mixer
```
3. Build and run either through IDE or command line
