set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system)

add_library(
        eepromProd
        STATIC
        eepromIPC.cpp
)

target_link_libraries(eepromProd PRIVATE Boost::system)
target_include_directories(eepromProd PRIVATE ${Boost_INCLUDE_DIRS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(eepromProd PRIVATE BOOST_CB_DISABLE_DEBUG)
set_target_properties(eepromProd PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        EXCLUDE_FROM_ALL ON)

add_library(
        eepromCon
        STATIC
        eepromIPC.cpp
)

target_link_libraries(eepromCon PRIVATE Boost::system)
target_include_directories(eepromCon PRIVATE ${Boost_INCLUDE_DIRS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(eepromCon PRIVATE CONSUMER BOOST_CB_DISABLE_DEBUG)
set_target_properties(eepromCon PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        EXCLUDE_FROM_ALL ON)