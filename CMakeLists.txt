set(PROJECT_NAME Original_Idea)

cmake_minimum_required(VERSION 3.31.7)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

# Set path to SFML 2.6.2
set(CMAKE_PREFIX_PATH "./SFML-2.6.2/")

# Explicitly set SFML_DIR to the folder containing SFMLConfig.cmake
set(SFML_DIR "./SFML-2.6.2/lib/cmake/SFML")

# Find the SFML packages (components for SFML 2.x)
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

# Add executable
add_executable(${PROJECT_NAME}
        main.cpp
        game.cpp
        player.cpp
        npc.h
        npc.cpp
        base_projectile.h
        first_projectile.h
        first_projectile.cpp
        second_projectile.h
        second_projectile.cpp
)

# Link SFML libraries (SFML 2.x uses the old target names without sfml::)
target_link_libraries(${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
)