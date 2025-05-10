cmake_minimum_required(VERSION 3.31.7)
project(Original_Idea)

set(CMAKE_CXX_STANDARD 20)

# Set path to SFML 2.6.2
set(CMAKE_PREFIX_PATH "C:/Libraries/SFML-2.6.2/")

# Explicitly set SFML_DIR to the folder containing SFMLConfig.cmake
set(SFML_DIR "C:/Libraries/SFML-2.6.2/lib/cmake/SFML")

# Find the SFML packages (components for SFML 2.x)
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

# Add executable
add_executable(gmdv main.cpp)

# Link SFML libraries (SFML 2.x uses the old target names without `sfml::`)
target_link_libraries(gmdv
        sfml-graphics
        sfml-window
        sfml-system
)
