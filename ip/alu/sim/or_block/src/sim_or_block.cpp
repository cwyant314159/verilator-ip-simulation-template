#include "sim_or_block.hpp"

#include <iostream>

SimOrBlock::SimOrBlock()
{
  Verilated::traceEverOn(true);
  mDut.trace(&mTrace, 5);
  mTrace.open("waveform.vcd");

  std::cout << "SIMULATION BEGIN\n";
}

SimOrBlock::~SimOrBlock()
{
  std::cout << "SIMULATION END\n";
  std::cout << "Tests: " << mTestCount << '\n';
  std::cout << "Fails: " << mFailCount << '\n';
  mDut.final();
  mTrace.close();
}

void SimOrBlock::IoTest(vluint32_t a, vluint32_t b)
{
  std::cout << "IO Test (a = " << a << " b = "<< b << ")\n";
  mTestCount++;
  mDut.invert = 0;
  mDut.a = a;
  mDut.b = b;
  tick();

  // The actual width of the DUT is 8. Really need to find a way to
  // automatically control this.
  const vluint8_t actual_out   = mDut.out;
  const vluint8_t expected_out = a | b;

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "IO test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimOrBlock::InvertIoTest(vluint32_t a, vluint32_t b)
{
  std::cout << "Inverted IO Test (a = " << a << " b = "<< b << ")\n";
  mTestCount++;
  mDut.invert = 1;
  mDut.a = a;
  mDut.b = b;
  tick();

  // The actual width of the DUT is 8. Really need to find a way to
  // automatically control this.
  const vluint8_t actual_out   = mDut.out;
  const vluint8_t expected_out = ~(a | b);

  if (expected_out != actual_out) {
    mFailCount++;
    std::cout << "-------------------------------------------------\n";
    std::cout << "Inverted IO test failed\n";
    std::cout << "Expected: " << expected_out << '\n';
    std::cout << "Actual  : " << actual_out   << '\n';
    std::cout << "-------------------------------------------------\n";
  }
}

void SimOrBlock::tick()
{ 
  mDut.eval();
  mTrace.dump(mSimTime);
  mSimTime++;
}