#include "sim_not_block.hpp"

#include <iostream>

SimNotBlock::SimNotBlock()
{
  Verilated::traceEverOn(true);
  mDut.trace(&mTrace, 5);
  mTrace.open("waveform.vcd");

  std::cout << "SIMULATION BEGIN\n";
}

SimNotBlock::~SimNotBlock()
{
  std::cout << "SIMULATION END\n";
  std::cout << "Tests: " << mTestCount << '\n';
  std::cout << "Fails: " << mFailCount << '\n';
  mDut.final();
  mTrace.close();
}

vluint64_t SimNotBlock::get_fail_count()
{
  return mFailCount;
}

void SimNotBlock::IoTest(vluint32_t in)
{
  std::cout << "IO Test (in = " << in << ")\n";
  mTestCount++;
  mDut.in = in;
  tick();

  // The actual width of the DUT is 8. Really need to find a way to
  // automatically control this.
  const vluint8_t actual_out   = mDut.out;
  const vluint8_t expected_out = ~in;

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "IO test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimNotBlock::tick()
{ 
  mDut.eval();
  mTrace.dump(mSimTime);
  mSimTime++;
}