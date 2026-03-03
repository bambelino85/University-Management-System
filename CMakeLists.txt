cmake_minimum_required(VERSION 3.16)
project(UniversityManagementSystem VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)

# Level 3 - base (no dependencies)
add_library(ums-person INTERFACE)
target_include_directories(ums-person INTERFACE include/)

# Level 2 - depend on ums-person
add_library(ums-student INTERFACE)
target_include_directories(ums-student INTERFACE include/)
target_link_libraries(ums-student INTERFACE ums-person)

add_library(ums-faculty INTERFACE)
target_include_directories(ums-faculty INTERFACE include/)
target_link_libraries(ums-faculty INTERFACE ums-person)

add_library(ums-course INTERFACE)
target_include_directories(ums-course INTERFACE include/)
target_link_libraries(ums-course INTERFACE ums-person)

# Level 1 - depends on all Level 2
add_library(ums-database INTERFACE)
target_include_directories(ums-database INTERFACE include/)
target_link_libraries(ums-database INTERFACE ums-student ums-faculty ums-course)

# Main executable - depends on ums-database
add_executable(university_app src/main.cpp)
target_link_libraries(university_app ums-database)
install(TARGETS university_app DESTINATION bin)
