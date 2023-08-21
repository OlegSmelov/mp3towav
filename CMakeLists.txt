cmake_minimum_required(VERSION 3.26)
project(mp3towav C)

set(CMAKE_C_STANDARD 99)

add_executable(mp3towav main.c
        wave.c
        wave.h)

add_executable(mp3towav_test
        tests/wave_test.c
        wave.c)

enable_testing()

add_test(
    NAME mp3towav_test
    COMMAND $<TARGET_FILE:mp3towav_test>
)
