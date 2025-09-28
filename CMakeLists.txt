cmake_minimum_required(VERSION 3.15)

project(tram-sim VERSION 0.1 LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put build outputs in the source tree so the executable will sit next to data/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Sources - add new .cpp files here when you create them
set(SOURCES
    main.cpp
    data_loaders.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Make sure headers/ is on the include path so you can include "headers/.."
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# For this small project we place the final executable in the project root so it can
# find `data/stops.json` by the simple relative path "data/stops.json". This keeps
# the layout identical to the source tree: `tram-sim.exe` next to `data/`.

# Compiler warning flags: be useful but not noisy.
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /WX-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wno-unused-parameter)
    # Enable link-time optimization for Release-type builds if supported
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported)
    if(ipo_supported)
        set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
    endif()
endif()

# Helpful targets and usage notes (not required)
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Sources: ${SOURCES}")

# End of file
