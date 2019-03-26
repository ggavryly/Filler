cmake_minimum_required(VERSION 3.13)
project(Filler C)

set(CMAKE_C_STANDARD 99)

include_directories(libft)
link_directories(libft)

add_executable(Filler
        src/free.c
        src/read.c
        src/start.c
        src/parse.c
        src/main.c
        src/solve.c)

target_link_libraries(Filler -lft)