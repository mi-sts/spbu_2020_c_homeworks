cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        )

set(LIST_LIB
        library/list/list.c
        )

add_library(library ${SOURCE_LIB})
add_library(list_library ${LIST_LIB})

add_executable(task_1.2 homework_1/task_2.c)
add_executable(task_1.4 homework_1/task_4.c)
add_executable(task_2.1 homework_2/task_1.c)
add_executable(task_3.1 homework_3/task_1.c)

target_link_libraries(task_3.1 list_library)