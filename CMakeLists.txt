cmake_minimum_required(VERSION 3.12)
project(GenWorld VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform-specific dependencies
if(UNIX AND NOT APPLE)
    # Linux-specific
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
endif()

# For GCC/Clang filesystem linking
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
endif()

find_package(OpenGL REQUIRED)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#------------------------------------------------------------------------------
# Fonts Configuration
# This section handles the configuration and setup of fonts used in the project.
# Add font-related settings, dependencies, or path configurations here.
#------------------------------------------------------------------------------
set(FONT_DIR "${CMAKE_SOURCE_DIR}/Resources/assets/fonts/Source_Sans_3/static")
set(REGULAR_FONT "${FONT_DIR}/SourceSans3-Regular.ttf")
set(BOLD_FONT "${FONT_DIR}/SourceSans3-Bold.ttf")

include(CTest)
enable_testing()

# Platform-specific source files
if(WIN32)
    set(PLATFORM_SOURCES
        src/Utils/Platform/FileDialogsWindows.cpp
    )
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_SOURCES
        src/Utils/Platform/FileDialogsLinux.cpp
    )
endif()

file(GLOB_RECURSE MY_SOURCES 
    CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Remove platform-specific files from general sources to avoid duplicates
list(FILTER MY_SOURCES EXCLUDE REGEX ".*FileDialogs(Windows|Linux)\\.cpp$")

add_executable(${PROJECT_NAME} ${MY_SOURCES} ${PLATFORM_SOURCES} ${GLFW-CMAKE-STARTER-SRC})

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_NO_EXPORT OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
configure_file("${PROJECT_SOURCE_DIR}/vendor/assimp/include/assimp/config.h.in" "${PROJECT_SOURCE_DIR}/vendor/assimp/include/assimp/config.h")
configure_file("${PROJECT_SOURCE_DIR}/vendor/assimp/contrib/zlib/zconf.h.cmakein" "vendor/assimp/contrib/zlib/zconf.h")

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/assimp)

include_directories(${CMAKE_SOURCE_DIR}/ImGui)
include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC glfw 
    PUBLIC glad 
    PUBLIC glm 
    PUBLIC assimp
    ${OPENGL_LIBRARIES}
    $<$<PLATFORM_ID:Linux>:${GTK3_LIBRARIES}>
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
    PUBLIC vendor/assimp/include
    PUBLIC ImGui
    $<$<PLATFORM_ID:Linux>:${GTK3_INCLUDE_DIRS}>
)

# Add compile definitions/flags for GTK if on Linux
if(UNIX AND NOT APPLE)
    target_compile_options(${PROJECT_NAME} PUBLIC ${GTK3_CFLAGS_OTHER})
endif()

# Copy assets to build directory.
# This is a temporary solution, we will use CMake to copy assets to the build directory.
# This ensures that we can reference the locations without having to worry about the relative paths.
file(GLOB_RECURSE SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*")
file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Resources/*")
file(GLOB_RECURSE MODEL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Models/*")
file(GLOB_RECURSE TEXTURE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Textures/*")

foreach(FILE ${SHADER_FILES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Shaders" "${FILE}")
    configure_file(${FILE} "${CMAKE_CURRENT_BINARY_DIR}/Shaders/${REL_PATH}" COPYONLY)
endforeach()

foreach(FILE ${RESOURCE_FILES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Resources" "${FILE}")
    configure_file(${FILE} "${CMAKE_CURRENT_BINARY_DIR}/Resources/${REL_PATH}" COPYONLY)
endforeach()

foreach(FILE ${MODEL_FILES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Models" "${FILE}")
    configure_file(${FILE} "${CMAKE_CURRENT_BINARY_DIR}/Models/${REL_PATH}" COPYONLY)
endforeach()

foreach(FILE ${TEXTURE_FILES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Textures" "${FILE}")
    configure_file(${FILE} "${CMAKE_CURRENT_BINARY_DIR}/Textures/${REL_PATH}" COPYONLY)
endforeach()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)