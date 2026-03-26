add_library(parser arg_parser.cpp arg_parser.h)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})