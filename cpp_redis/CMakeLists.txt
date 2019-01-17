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

add_executable (cpp_redis_test cpp_redis_test.cpp)
target_link_libraries(cpp_redis_test cpp_redis)
target_link_libraries(cpp_redis_test tacopie)
target_link_libraries(cpp_redis_test pthread)
