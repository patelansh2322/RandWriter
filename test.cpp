// Copyright [2025] Ansh Patel

#include <fstream>
#include <sstream>
#include "RandWriter.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RandWriterTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Constructor_InvalidInput) {
    BOOST_REQUIRE_THROW(RandWriter("short", 10), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(OrderK_Check) {
    RandWriter rw("abcabcabc", 2);
    BOOST_REQUIRE_EQUAL(rw.orderK(), 2);
}


BOOST_AUTO_TEST_CASE(Generate_Valid) {
    RandWriter rw("abcabcabc", 2);
    std::string result = rw.generate("ab", 10);
    BOOST_REQUIRE_EQUAL(result.length(), 10);
    BOOST_REQUIRE(result.substr(0, 2) == "ab");
}
