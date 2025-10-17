cmake_minimum_required(VERSION 3.10)

project(smenu C)
set(CMAKE_C_STANDARD 99)


include_directories(.)

# Combine all link options into one call
add_link_options(-lm -lraylib -lGL -lpthread -ldl -lrt -lX11 -O2 -DNDEBUG -s -flto -Wall -Wextra -std=c99 -fno-strict-aliasing)

# Collect all source files and headers
file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

# Add the executable
add_executable(smenu ${SOURCES} ${HEADERS})
