find_package(Boost COMPONENTS system REQUIRED)

add_library(
        LcdProd
        STATIC
        LcdIPC.cpp
)

target_link_libraries(LcdProd PRIVATE Boost::system)
target_include_directories(LcdProd PRIVATE ${Boost_INCLUDE_DIRS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(LcdProd PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        EXCLUDE_FROM_ALL ON)


add_library(
        LcdCon
        STATIC
        LcdIPC.cpp
)

target_link_libraries(LcdCon PRIVATE Boost::system)
target_include_directories(LcdCon PRIVATE ${Boost_INCLUDE_DIRS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(LcdCon PRIVATE CONSUMER)
set_target_properties(LcdCon PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        EXCLUDE_FROM_ALL ON)

