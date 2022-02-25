cmake_minimum_required(VERSION 3.20)
project(go_back_n_simul C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(go_back_n_simul
        common.c
        imports.h
        ports.h
        receiver.c
        sender.c)
