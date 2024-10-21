cmake_minimum_required(VERSION 3.0.2)

project(CSPlayer)

set(source src/main_miniaudio.cpp)

add_executable(CSPlayer ${source})

target_compile_options(CSPlayer PUBLIC /DUNICODE /D_UNICODE)

target_link_options(CSPlayer PUBLIC /subsystem:windows /entry:mainCRTStartup)

target_include_directories(CSPlayer 
                           PUBLIC include
                           )

include(FetchContent)
FetchContent_Declare(
    SFML
    URL https://github.com/SFML/SFML/archive/refs/tags/2.5.1.zip
)

FetchContent_MakeAvailable(SFML)

target_include_directories(CSPlayer 
                           PUBLIC lib
                           )

target_link_libraries(CSPlayer 
                      sfml-graphics
                      sfml-system
                      sfml-window
                      )
                      
install(TARGETS CSPlayer DESTINATION ${CMAKE_SOURCE_DIR}/bin)