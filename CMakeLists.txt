cmake_minimum_required(VERSION 3.10)

project(smenu C)
set(CMAKE_C_STANDARD 99)

# Find required packages
find_package(PkgConfig REQUIRED)

# Check for available backends
find_package(X11)
pkg_check_modules(WAYLAND wayland-client wayland-cursor wayland-egl xkbcommon)

# Display available backends
if(X11_FOUND)
    message(STATUS "X11 found: ${X11_FOUND}")
endif()

if(WAYLAND_FOUND)
    message(STATUS "Wayland found: ${WAYLAND_FOUND}")
endif()

# Let user choose backend if multiple are available
if(X11_FOUND AND WAYLAND_FOUND)
    set(BACKEND_CHOICES "X11" "Wayland")
    set(DEFAULT_BACKEND "X11")
    
    # Set a cache variable for backend selection
    set(SMENU_BACKEND "${DEFAULT_BACKEND}" CACHE STRING "Backend to use for display")
    set_property(CACHE SMENU_BACKEND PROPERTY STRINGS ${BACKEND_CHOICES})
    
    message(STATUS "Multiple backends available. Using: ${SMENU_BACKEND}")
    message(STATUS "To change backend, use: -DSMENU_BACKEND=Wayland or -DSMENU_BACKEND=X11")
    
elseif(X11_FOUND)
    set(SMENU_BACKEND "X11")
    message(STATUS "Using X11 backend (only available backend)")
    
elseif(WAYLAND_FOUND)
    set(SMENU_BACKEND "Wayland") 
    message(STATUS "Using Wayland backend (only available backend)")
    
else()
    message(FATAL_ERROR "No display backend found! Need either X11 or Wayland.")
endif()

include_directories(.)

# Common compiler flags
set(COMMON_COMPILE_OPTIONS -O2 -DNDEBUG -s -flto -Wall -Wextra -std=c99 -fno-strict-aliasing)

# Common link libraries
set(COMMON_LIBS m raylib GL pthread dl rt)

# Backend-specific setup
if(SMENU_BACKEND STREQUAL "Wayland")
    if(NOT WAYLAND_FOUND)
        message(FATAL_ERROR "Wayland backend requested but Wayland not found!")
    endif()
    
    # Add Wayland specific definitions
    add_compile_definitions(USE_WAYLAND)
    
    # Wayland specific libraries
    set(BACKEND_LIBS ${WAYLAND_LIBRARIES})
    message(STATUS "Configured for Wayland backend")
    
else()  # X11 backend
    if(NOT X11_FOUND)
        message(FATAL_ERROR "X11 backend requested but X11 not found!")
    endif()
    
    # X11 specific definitions if needed
    add_compile_definitions(USE_X11)
    
    # X11 specific libraries
    set(BACKEND_LIBS X11)
    if(X11_LIBRARIES)
        list(APPEND BACKEND_LIBS ${X11_LIBRARIES})
    endif()
    
    # Add X11 include directories
    if(X11_INCLUDE_DIR)
        include_directories(${X11_INCLUDE_DIR})
    endif()
    
    message(STATUS "Configured for X11 backend")
endif()

# Collect all source files and headers
file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

add_executable(smenu ${SOURCES} ${HEADERS})

target_compile_options(smenu PRIVATE ${COMMON_COMPILE_OPTIONS})

target_link_libraries(smenu ${COMMON_LIBS} ${BACKEND_LIBS})


message(STATUS "")
message(STATUS "Backend: ${SMENU_BACKEND}")
message(STATUS "C Standard: ${CMAKE_C_STANDARD}")
message(STATUS "Build type: Release (optimized)")

