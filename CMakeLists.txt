cmake_minimum_required(VERSION 3.20)
 
project("Hamster" CXX CUDA)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(csrc/core)
 
add_executable(${PROJECT_NAME} main.cu)
 
find_package(NumCpp REQUIRED)
target_link_libraries(${PROJECT_NAME}
    NumCpp::NumCpp
    core
)
