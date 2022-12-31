#include "sim_alu.hpp"

// MAIN
int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);

    SimAlu simDut;

    simDut.reset();

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            simDut.op_and_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            simDut.op_nand_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            simDut.op_or_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            simDut.op_nor_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            simDut.op_xor_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            simDut.op_xnor_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFFFF; ++a) {
        simDut.op_not_a_test(a);
    }

    for (vluint32_t b = 0; b <= 0xFFFF; ++b) {
        simDut.op_not_b_test(b);
    }
    
    return simDut.get_fail_count() > 0;
}
