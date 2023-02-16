
set(PROJECT_SOURCES
    main.cpp
)

# find doctest
# vcpkg port for doctest does not have include dir for some reason
# this method allows doctest_include_dire to passed in as a build option if required

if(${VCPKG_TOOLCHAIN} AND NOT DEFINED doctest_include_dire)
    find_package(doctest REQUIRED)
    set(doctest_include_dire "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include")
endif()

if(DEFINED doctest_include_dire)
    add_executable(ArduinoWrapper-test ${PROJECT_SOURCES})
    target_link_libraries(ArduinoWrapper-test PUBLIC ArduinoWrapper)
    target_include_directories(ArduinoWrapper-test PRIVATE ${doctest_include_dire})
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(ArduinoWrapper-test  PRIVATE
            $<$<CXX_COMPILER_ID:Clang>:-fprofile-arcs -ftest-coverage>
        )
        target_link_options(ArduinoWrapper-test  PRIVATE
            $<$<CXX_COMPILER_ID:Clang>:-fprofile-arcs -ftest-coverage>
        )
    endif()
endif()

