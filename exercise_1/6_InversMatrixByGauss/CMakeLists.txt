cmake_minimum_required(VERSION 3.5)

project(Project)

#set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_STANDARD 03)
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_C_STANDARD 89)
#set(CMAKE_C_STANDARD 90)
#set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wno-unused-parameter -fPIC -march=native")

set(SOURCE

	main.cpp

)
set(HEADERS

    matrix.h
    test.h

)

add_executable(out ${SOURCE} ${HEADERS} )
