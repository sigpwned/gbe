#define BOOST_TEST_MODULE opcodestest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(opcodestest)

BOOST_AUTO_TEST_CASE(example)
{
  BOOST_CHECK(1 < 2);
}

BOOST_AUTO_TEST_SUITE_END()
