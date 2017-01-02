#define BOOST_TEST_MODULE cputest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cpu.h"
#include "opcodes.h"

BOOST_AUTO_TEST_SUITE(cputest)

BOOST_AUTO_TEST_CASE(reg_af_test)
{
  unsigned char memory[64*1024];

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

BOOST_AUTO_TEST_CASE(program_1)
{
  unsigned char memory[64*1024];

  unsigned char program[]={
    LD_A_D8, 0x17,
    XOR_A_A,
    INC_A,
    INC_A,
    PREFIX_CB, SLA_A,
    ADD_A_A,
    HALT
  };

  memcpy(memory, program, sizeof(program));

  struct cpu cpu;
  cpu_init(&cpu, memory);

  BOOST_CHECK(cpu_get_a(&cpu) == 0);

  int ticks=0, max_ticks=1024;
  while(ticks<max_ticks && !cpu.halted) {
    cpu_tick(&cpu);
    ticks = ticks+1;
  }

  BOOST_CHECK(ticks < max_ticks);
  BOOST_CHECK(cpu.halted);
  BOOST_CHECK(cpu_get_a(&cpu) == 8);
}

BOOST_AUTO_TEST_SUITE_END()
