cmake_minimum_required(VERSION 3.18)
project(LM_Server C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(pos_sockets)
include_directories(LM_logika)


add_executable(
        LM_Server main.c
        pos_sockets/active_socket.c
        pos_sockets/active_socket.h
        pos_sockets/char_buffer.c
        pos_sockets/char_buffer.h
        pos_sockets/linked_list.h
        pos_sockets/passive_socket.c
        pos_sockets/passive_socket.h
        buffer.h
        LM_logika/Simulacia.c
        LM_logika/Simulacia.h
        LM_logika/Mravec.h
        LM_logika/Mravec.c
        LM_logika/Pole.h
        LM_logika/Pole.c
        LM_logika/Plocha.h
        LM_logika/Plocha.c)

target_link_libraries(LM_Server pthread)




