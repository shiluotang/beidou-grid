file(GLOB_RECURSE
    LIBRARY_SOURCES
    LIST_DIRECTORIES TRUE
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cc
    *.cpp)
add_library(beidou_grid STATIC)
target_sources(beidou_grid PRIVATE ${LIBRARY_SOURCES})
target_include_directories(beidou_grid PUBLIC ${CMAKE_SOURCE_DIR}/include)
