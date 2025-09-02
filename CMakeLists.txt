cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(
    main src/main.cpp
    src/adapter/SnakeAdapter.cpp
    src/controller/Controller.cpp
    src/inputs/PlayerInputs.cpp
    src/model/snake/SnakePart.cpp
    src/model/snake/Snake.cpp
    src/model/terrain/World.cpp
    src/model/tools/Bound.cpp
    src/model/tools/Direction.cpp
    src/model/tools/ObjectTracker.cpp
    src/view/state/SplashState.cpp
    src/view/AnimatedSprite.cpp
    src/view/ResourceManager.cpp
    src/view/StateMachine.cpp
    src/view/State.hpp
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
