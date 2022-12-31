#include "sim_not_block.hpp"

// MAIN
int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);

    SimNotBlock simDut;

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        simDut.IoTest(a);
    }
    
    return 0;
}
