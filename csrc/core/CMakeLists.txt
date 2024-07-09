
file(GLOB core_src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB core_header ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)
add_library(core SHARED ${core_src})