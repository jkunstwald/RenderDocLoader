cmake_minimum_required(VERSION 3.0)
project(RenderDocLoader)

#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(rdocloader STATIC 
    "include/renderdoc/loader.hh"
    "src/loader.cc"
    "src/renderdoc_app.hh"
)

target_include_directories(rdocloader PUBLIC "include")
