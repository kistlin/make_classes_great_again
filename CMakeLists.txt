cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

project(make_classes_great_again)

add_executable(main main.cpp)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET main POST_BUILD
        COMMENT "Copy file that will be read during execution of main()"
        COMMAND ${CMAKE_COMMAND} -E
        copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/test.txt $<TARGET_FILE_DIR:main>
        )