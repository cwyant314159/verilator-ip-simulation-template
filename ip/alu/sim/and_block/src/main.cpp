#include "sim_and_block.hpp"

// MAIN
int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);

    SimAndBlock simDut;

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            simDut.IoTest(a, b);
        }
    }
    
    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            simDut.InvertIoTest(a, b);
        }
    }

    return 0;
}
