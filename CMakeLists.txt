cmake_minimum_required(VERSION 3.12)
project(yandex_schedule VERSION 1.0 LANGUAGES CXX)

add_library(
    ${PROJECT_NAME}
    STATIC
    src/YandexScheduleAPI.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 1.11.0)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} PUBLIC cpr::cpr nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(
    FILES 
    include/YandexScheduleAPI.h
    DESTINATION include
)

set(TEST_FILE "${CMAKE_SOURCE_DIR}/test/test.cpp")
if(EXISTS ${TEST_FILE})
    add_executable(yandex_schedule_test ${TEST_FILE})
    target_link_libraries(yandex_schedule_test PRIVATE yandex_schedule)
endif()