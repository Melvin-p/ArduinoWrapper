
find_package(Boost REQUIRED COMPONENTS system)

add_library(
    SerialProd
    STATIC
serial.cpp
)

target_link_libraries(SerialProd PRIVATE Boost::system)
target_include_directories(SerialProd PRIVATE ${Boost_INCLUDE_DIRS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(SerialProd PRIVATE BOOST_CB_DISABLE_DEBUG )
set_target_properties(SerialProd PROPERTIES
POSITION_INDEPENDENT_CODE ON
EXCLUDE_FROM_ALL ON)

add_library(
    SerialCon
    STATIC
serial.cpp
)

target_link_libraries(SerialCon PRIVATE Boost::system)
target_include_directories(SerialCon PRIVATE ${Boost_INCLUDE_DIRS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(SerialCon PRIVATE CONSUMER BOOST_CB_DISABLE_DEBUG)
set_target_properties(SerialCon PROPERTIES
POSITION_INDEPENDENT_CODE ON
EXCLUDE_FROM_ALL ON)