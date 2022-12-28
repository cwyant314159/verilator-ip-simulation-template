#include <verilated.h>

#include "hello.hpp"
#include "tb_alu.h"

constexpr int MAX_TIME = 20;

int main(void)
{
    int sim_time = 0;
    tb_alu *dut = new tb_alu;
    Hello::greet(27);

    while(sim_time < MAX_TIME) {
        dut->clock ^= 1;
        dut->eval();
        sim_time++;
    }

    dut->final();

    delete dut;
    return 0;
}
