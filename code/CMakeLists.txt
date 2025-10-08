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

add_compile_definitions(DEBUG_VERSION)

include_directories(
    inc/
    inc/adapter
    inc/controller
    inc/inputs
    inc/logger
    inc/model/snake
    inc/model/terrain
    inc/model/tools
    inc/settings
    inc/view
    inc/view/state
)

add_executable(
    main src/main.cpp
    src/adapter/SnakeAdapter.cpp
    src/controller/Controller.cpp
    src/inputs/PlayerInputs.cpp
    src/logger/Logger.cpp
    src/model/snake/SnakePart.cpp
    src/model/snake/Snake.cpp
    src/model/terrain/World.cpp
    src/model/tools/Bound.cpp
    src/model/tools/Direction.cpp
    src/model/tools/BoundFactory.cpp
    src/model/tools/ObjectTracker.cpp
    src/view/state/SplashState.cpp
    src/view/AnimatedSprite.cpp
    src/view/ResourceManager.cpp
    src/view/StateMachine.cpp
    inc/adapter/Adaptable.h
    inc/adapter/Adapter.h
    inc/adapter/SnakeAdapter.h
    inc/controller/Controller.h
    inc/inputs/PlayerInputs.h
    inc/logger/Logger.h
    inc/model/snake/Snake.h
    inc/model/snake/SnakePart.h
    inc/model/terrain/World.h
    inc/model/tools/Bound.h
    inc/model/tools/BoundFactory.h
    inc/model/tools/Direction.h
    inc/model/tools/ObjectTracker.h
    inc/settings/Settings.h
    inc/view/state/SplashState.h
    inc/view/AnimatedSprite.h
    inc/view/ResourceManager.h
    inc/view/StateMachine.h
    inc/view/State.hpp
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
