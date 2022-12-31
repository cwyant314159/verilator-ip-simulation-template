#pragma once

#include <verilated.h>
#include <verilated_vcd_c.h>

#include "tb_alu.h"

class SimAlu {

public:
  SimAlu();
  ~SimAlu();
  vluint64_t get_fail_count();
  void op_and_test(vluint32_t a, vluint32_t b);
  void op_nand_test(vluint32_t a, vluint32_t b);
  void op_or_test(vluint32_t a, vluint32_t b);
  void op_nor_test(vluint32_t a, vluint32_t b);
  void op_xor_test(vluint32_t a, vluint32_t b);
  void op_xnor_test(vluint32_t a, vluint32_t b);
  void op_not_a_test(vluint32_t a);
  void op_not_b_test(vluint32_t b);
  void reset(vluint64_t cycles = 2);
  void wait_cycles(vluint64_t cycles);

private:
  tb_alu        mDut;
  VerilatedVcdC mTrace;
  
  vluint64_t mSimTime    = 0;
  vluint64_t mPosEdgeCnt = 0;
  vluint64_t mTestCount  = 0;
  vluint64_t mFailCount  = 0;

  void assert_valid();
  void tick();
};