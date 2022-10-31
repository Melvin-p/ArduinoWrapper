find_package(Boost COMPONENTS system REQUIRED)

add_library(
    LcdCom
    STATIC
lcdipc.cpp
lcdipc.hpp
)

target_link_libraries(LcdCom PRIVATE Boost::system)
target_include_directories(LcdCom PRIVATE ${Boost_INCLUDE_DIRS})




