#include "sim_alu.hpp"

#include <iostream>

#include "tb_alu_op_code_pkg.h"

SimAlu::SimAlu()
{
  Verilated::traceEverOn(true);
  mDut.trace(&mTrace, 5);
  mTrace.open("waveform.vcd");

  std::cout << "SIMULATION BEGIN\n";
}

SimAlu::~SimAlu()
{
  std::cout << "SIMULATION END\n";
  std::cout << "Tests: " << mTestCount << '\n';
  std::cout << "Fails: " << mFailCount << '\n';
  mDut.final();
  mTrace.close();
}

vluint64_t SimAlu::get_fail_count()
{
  return mFailCount;
}

void SimAlu::op_and_test(vluint32_t a, vluint32_t b)
{
  std::cout << "AND Test (a = " << a << " b = " << b << ")\n";
  mTestCount++;
  mDut.op_in = tb_alu_op_code_pkg::OP_AND;
  mDut.a_in  = a;
  mDut.b_in  = b;
  assert_valid();

  while (mDut.out_valid != 1) {
    wait_cycles(1);
  }

  const vluint32_t actual_out   = mDut.out;
  const vluint32_t expected_out = a & b;

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "AND test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimAlu::op_nand_test(vluint32_t a, vluint32_t b)
{
  std::cout << "NAND Test (a = " << a << " b = " << b << ")\n";
  mTestCount++;
  mDut.op_in = tb_alu_op_code_pkg::OP_NAND;
  mDut.a_in  = a;
  mDut.b_in  = b;
  assert_valid();

  while (mDut.out_valid != 1) {
    wait_cycles(1);
  }

  const vluint32_t actual_out   = mDut.out;
  const vluint32_t expected_out = ~(a & b);

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "NAND test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimAlu::op_or_test(vluint32_t a, vluint32_t b)
{
  std::cout << "OR Test (a = " << a << " b = " << b << ")\n";
  mTestCount++;
  mDut.op_in = tb_alu_op_code_pkg::OP_OR;
  mDut.a_in  = a;
  mDut.b_in  = b;
  assert_valid();

  while (mDut.out_valid != 1) {
    wait_cycles(1);
  }

  const vluint32_t actual_out   = mDut.out;
  const vluint32_t expected_out = a | b;

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "OR test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimAlu::op_nor_test(vluint32_t a, vluint32_t b)
{
  std::cout << "NOR Test (a = " << a << " b = " << b << ")\n";
  mTestCount++;
  mDut.op_in = tb_alu_op_code_pkg::OP_NOR;
  mDut.a_in  = a;
  mDut.b_in  = b;
  assert_valid();

  while (mDut.out_valid != 1) {
    wait_cycles(1);
  }

  const vluint32_t actual_out   = mDut.out;
  const vluint32_t expected_out = ~(a | b);

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "NOR test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimAlu::op_xor_test(vluint32_t a, vluint32_t b)
{
  std::cout << "XOR Test (a = " << a << " b = " << b << ")\n";
  mTestCount++;
  mDut.op_in = tb_alu_op_code_pkg::OP_XOR;
  mDut.a_in  = a;
  mDut.b_in  = b;
  assert_valid();

  while (mDut.out_valid != 1) {
    wait_cycles(1);
  }

  const vluint32_t actual_out   = mDut.out;
  const vluint32_t expected_out = a ^ b;

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "XOR test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimAlu::op_xnor_test(vluint32_t a, vluint32_t b)
{
  std::cout << "XNOR Test (a = " << a << " b = " << b << ")\n";
  mTestCount++;
  mDut.op_in = tb_alu_op_code_pkg::OP_XNOR;
  mDut.a_in  = a;
  mDut.b_in  = b;
  assert_valid();

  while (mDut.out_valid != 1) {
    wait_cycles(1);
  }

  const vluint32_t actual_out   = mDut.out;
  const vluint32_t expected_out = ~(a ^ b);

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "XNOR test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimAlu::op_not_a_test(vluint32_t a)
{
  std::cout << "NOT A Test (a = " << a << ")\n";
  mTestCount++;
  mDut.op_in = tb_alu_op_code_pkg::OP_NOT_A;
  mDut.a_in  = a;
  assert_valid();

  while (mDut.out_valid != 1) {
    wait_cycles(1);
  }

  const vluint32_t actual_out   = mDut.out;
  const vluint32_t expected_out = ~(a);

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "NOT A test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}


void SimAlu::op_not_b_test(vluint32_t b)
{
  std::cout << "NOT B Test (b = " << b << ")\n";
  mTestCount++;
  mDut.op_in = tb_alu_op_code_pkg::OP_NOT_B;
  mDut.b_in  = b;
  assert_valid();

  while (mDut.out_valid != 1) {
    wait_cycles(1);
  }

  const vluint32_t actual_out   = mDut.out;
  const vluint32_t expected_out = ~(b);

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "NOT B test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimAlu::reset(vluint64_t cycles)
{
  mDut.rst      = 1;
  mDut.in_valid = 0;
  mDut.a_in     = 0;
  mDut.b_in     = 0;
  mDut.op_in    = tb_alu_op_code_pkg::OP_NOT_A;
  wait_cycles(2);
  
  mDut.rst = 0;
  wait_cycles(1);
}

void SimAlu::wait_cycles(vluint64_t cycles)
{
  const vluint64_t target_count = cycles + mPosEdgeCnt;

  while(target_count != mPosEdgeCnt) {
    tick();
  }
}

void SimAlu::assert_valid()
{
  mDut.in_valid = 1;
  wait_cycles(1);
  mDut.in_valid = 0;
  wait_cycles(1);
}

void SimAlu::tick()
{ 
  mDut.clk ^= 1;
  mDut.eval();

  if (1 == mDut.clk) {
    ++mPosEdgeCnt;
  }

  mTrace.dump(mSimTime);
  mSimTime++;
}