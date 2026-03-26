add_library(bmp_writer bmp_writer.cpp bmp_writer.h)

target_include_directories(bmp_writer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(bmp_writer PUBLIC field)