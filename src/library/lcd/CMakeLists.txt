find_package(Boost COMPONENTS system REQUIRED)

add_library(
    LcdComProd
    STATIC
lcdipc.cpp
)

target_link_libraries(LcdComProd PRIVATE Boost::system)
target_include_directories(LcdComProd PRIVATE ${Boost_INCLUDE_DIRS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(LcdComProd PROPERTIES
POSITION_INDEPENDENT_CODE ON
EXCLUDE_FROM_ALL ON)


add_library(
    LcdComCon
    STATIC
lcdipc.cpp
)

target_link_libraries(LcdComCon PRIVATE Boost::system)
target_include_directories(LcdComCon PRIVATE ${Boost_INCLUDE_DIRS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(LcdComCon PRIVATE CONSUMER)
set_target_properties(LcdComCon PROPERTIES
POSITION_INDEPENDENT_CODE ON
EXCLUDE_FROM_ALL ON)

