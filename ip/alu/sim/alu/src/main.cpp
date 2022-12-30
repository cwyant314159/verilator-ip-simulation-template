#include "sim_alu.hpp"

// MAIN
int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);

    SimAlu sim_alu;

    sim_alu.reset();

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            sim_alu.op_and_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            sim_alu.op_nand_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            sim_alu.op_or_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            sim_alu.op_nor_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            sim_alu.op_xor_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFF; ++a) {
        for (vluint32_t b = 0; b <= 0xFF; ++b) {
            sim_alu.op_xnor_test(a, b);
        }
    }

    for (vluint32_t a = 0; a <= 0xFFFF; ++a) {
        sim_alu.op_not_a_test(a);
    }

    for (vluint32_t b = 0; b <= 0xFFFF; ++b) {
        sim_alu.op_not_b_test(b);
    }
    
    return 0;
}
