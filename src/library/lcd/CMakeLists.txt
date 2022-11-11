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
target_compile_options(LcdComProd PRIVATE
    $<$<NOT:$<BOOL:${WIN32}>>:
            $<$<CXX_COMPILER_ID:GNU>:-fPIC>
            $<$<CXX_COMPILER_ID:Clang>:-fPIC>
    >
)

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
target_compile_options(LcdComCon PRIVATE
    $<$<NOT:$<BOOL:${WIN32}>>:
            $<$<CXX_COMPILER_ID:GNU>:-fPIC>
            $<$<CXX_COMPILER_ID:Clang>:-fPIC>
    >
)
