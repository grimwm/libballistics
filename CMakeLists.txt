cmake_minimum_required(VERSION 3.1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
project(ballistics C CXX)

include_directories(include)
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -finline-functions -O3")

list(APPEND EXEC_SOURCES example.c)

list(APPEND LIB_SOURCES angle.c atmosphere.c retard.c solve.c windage.c zero.c)

add_executable(example ${EXEC_SOURCES})
target_link_libraries(example PRIVATE m ballistics)
#install(TARGETS example DESTINATION bin)

add_library(ballistics STATIC ${LIB_SOURCES})
target_link_libraries(ballistics PRIVATE m)
set_target_properties(ballistics PROPERTIES LINK_FLAGS "-Wl,--whole-archive")
install(TARGETS ballistics DESTINATION lib)
install(FILES include/ballistics.h DESTINATION include)

# To workaround the fact CLion doesn't have a way to do `make install`:
add_custom_target(install_${PROJECT_NAME}
        ${CMAKE_MAKE_PROGRAM} install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")
