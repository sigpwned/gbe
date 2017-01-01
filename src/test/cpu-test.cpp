#define BOOST_TEST_MODULE cputest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cpu.h"

BOOST_AUTO_TEST_SUITE(cputest)

BOOST_AUTO_TEST_CASE(reg_af_test)
{
  unsigned char* memory=(unsigned char *) malloc(64*1024);

  struct cpu cpu;
  cpu_init(&cpu, memory);

  BOOST_CHECK(cpu_get_a(&cpu) == 0);
  BOOST_CHECK(cpu_get_f(&cpu) == 0);

  cpu_set_a(&cpu, 56);
  BOOST_CHECK(cpu_get_a(&cpu) == 56);
  BOOST_CHECK(cpu_get_af(&cpu) == (56 << 8 | 0));

  cpu_set_f(&cpu, 89);
  BOOST_CHECK(cpu_get_f(&cpu) == 89);
  BOOST_CHECK(cpu_get_af(&cpu) == (56 << 8 | 89));
}

BOOST_AUTO_TEST_SUITE_END()
