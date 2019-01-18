cmake_minimum_required (VERSION 2.8.7)
project (cpp_redis_test)

#add_library(lib )

###
# variables
###
set(CPP_REDIS_INCLUDES ${PROJECT_SOURCE_DIR}/includes)
set(TACOPIE_INCLUDES ${PROJECT_SOURCE_DIR}/includes)

###
# includes
###
include_directories(${CPP_REDIS_INCLUDES} ${TACOPIE_INCLUDES})

###
# libraries
###
link_directories("${PROJECT_SOURCE_DIR}/lib")

###
# compilation options
###
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra -O3")

add_executable (cpp_redis_test cpp_redis_test.cpp)
target_link_libraries(cpp_redis_test cpp_redis)
target_link_libraries(cpp_redis_test tacopie)
target_link_libraries(cpp_redis_test pthread)

add_executable (cpp_redis_sub_test cpp_redis_sub_test.cpp)
target_link_libraries(cpp_redis_sub_test cpp_redis)
target_link_libraries(cpp_redis_sub_test tacopie)
target_link_libraries(cpp_redis_sub_test pthread)

add_executable (cpp_redis_pub_test cpp_redis_pub_test.cpp)
target_link_libraries(cpp_redis_pub_test cpp_redis)
target_link_libraries(cpp_redis_pub_test tacopie)
target_link_libraries(cpp_redis_pub_test pthread)