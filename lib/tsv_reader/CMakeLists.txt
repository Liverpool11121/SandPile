add_library(tsv_reader tsv_reader.cpp tsv_reader.h)

target_include_directories(tsv_reader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tsv_reader PUBLIC parser field)