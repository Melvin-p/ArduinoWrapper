find_package(Boost COMPONENTS system REQUIRED)

add_library(
    LcdComProd
    STATIC
lcdipc.cpp
lcdipc.hpp
charSetMap.hpp
charSetMap.cpp
def.hpp
)

target_link_libraries(LcdComProd PRIVATE Boost::system)
target_include_directories(LcdComProd PRIVATE ${Boost_INCLUDE_DIRS})

add_library(
    LcdComCon
    STATIC
lcdipc.cpp
lcdipc.hpp
charSetMap.hpp
charSetMap.cpp
def.hpp
)

target_link_libraries(LcdComCon PRIVATE Boost::system)
target_include_directories(LcdComCon PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(LcdComCon PRIVATE CONSUMER)
