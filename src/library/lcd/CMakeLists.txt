find_package(Boost COMPONENTS system REQUIRED)

add_library(
    libLcdComProd
    STATIC
lcdipc.cpp
lcdipc.hpp
def.hpp
)

target_link_libraries(libLcdComProd PRIVATE Boost::system)
target_include_directories(libLcdComProd PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_options(libLcdComProd PRIVATE
    $<$<NOT:$<BOOL:${WIN32}>>:
            $<$<CXX_COMPILER_ID:GNU>:-fPIC>
            $<$<CXX_COMPILER_ID:Clang>:-fPIC>
    >
)

add_library(
    libLcdComCon
    STATIC
lcdipc.cpp
lcdipc.hpp
def.hpp
)

target_link_libraries(libLcdComCon PRIVATE Boost::system)
target_include_directories(libLcdComCon PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(libLcdComCon PRIVATE CONSUMER)
target_compile_options(libLcdComCon PRIVATE
    $<$<NOT:$<BOOL:${WIN32}>>:
            $<$<CXX_COMPILER_ID:GNU>:-fPIC>
            $<$<CXX_COMPILER_ID:Clang>:-fPIC>
    >
)
