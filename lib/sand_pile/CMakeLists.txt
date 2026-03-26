add_library(sand_pile sand_pile.cpp sand_pile.h)

target_include_directories(sand_pile PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(sand_pile PUBLIC parser field tsv_reader bmp_writer)