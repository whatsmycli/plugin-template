cmake_minimum_required(VERSION 3.15)

# Project name - Change this to your plugin name
project(myplugin VERSION 1.0.0)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# Build shared library (plugin)
add_library(${PROJECT_NAME} SHARED
    plugin.cpp
)

# Platform-specific configuration
if(LINUX)
    # Linux: .so file
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PREFIX ""
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".so"
    )
elseif(WIN32)
    # Windows: .dll file
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PREFIX ""
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".dll"
    )
elseif(APPLE)
    # macOS: .dylib file
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PREFIX "lib"
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".dylib"
    )
endif()

# Compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # GCC/Clang flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -O3
    )
elseif(MSVC)
    # MSVC flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /O2
    )
endif()

# Installation (optional)
# Uncomment if you want 'make install' to copy the plugin
# install(TARGETS ${PROJECT_NAME}
#     LIBRARY DESTINATION lib/whatsmy/plugins/${PROJECT_NAME}
#     RUNTIME DESTINATION lib/whatsmy/plugins/${PROJECT_NAME}
# )

# Print build information
message(STATUS "Building plugin: ${PROJECT_NAME}")
message(STATUS "Plugin version: ${PROJECT_VERSION}")
if(LINUX)
    message(STATUS "Platform: Linux")
    message(STATUS "Output: ${PROJECT_NAME}.so")
elseif(WIN32)
    message(STATUS "Platform: Windows")
    message(STATUS "Output: ${PROJECT_NAME}.dll")
elseif(APPLE)
    message(STATUS "Platform: macOS")
    message(STATUS "Output: lib${PROJECT_NAME}.dylib")
endif()

