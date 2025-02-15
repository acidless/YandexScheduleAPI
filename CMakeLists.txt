cmake_minimum_required(VERSION 3.10)
project(yandex_schedule VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(TARGETS my_library DESTINATION lib)
install(FILES include/my_library.hpp DESTINATION include)