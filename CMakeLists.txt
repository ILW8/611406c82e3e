cmake_minimum_required(VERSION 3.0)
project(threatspike_tech_questions)

set(CMAKE_CXX_STANDARD 20)

add_executable(threatspike_tech_question_1 q1.cpp)
add_executable(threatspike_tech_question_2 q2.cpp)

add_library(parse_uri parse_uri.cpp)
add_executable(threatspike_tech_question_3 q3.cpp q3.h)
target_link_libraries(threatspike_tech_question_3 PRIVATE parse_uri)



add_subdirectory(Google_tests)