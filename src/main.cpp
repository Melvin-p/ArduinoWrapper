#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "./library/adwr.hpp"

TEST_CASE("testing the String class") {
    String test_string = "Hello";
    CHECK(test_string.equals("Hello"));
    CHECK_FALSE(test_string.equals("World"));
}
