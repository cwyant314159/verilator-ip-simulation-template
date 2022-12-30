/****** alu.sv ******/
module alu #(
    parameter int WIDTH = 6
) (
    input logic              clk,
    input logic              rst,

    input  logic[2:0]        op_in,
    input  logic[WIDTH-1:0]  a_in,
    input  logic[WIDTH-1:0]  b_in,
    input  logic             in_valid,

    output logic [WIDTH-1:0] out,
    output logic             out_valid
);

import op_code_pkg::*;

logic [2:0]       op_in_r;
logic [WIDTH-1:0] a_in_r;
logic [WIDTH-1:0] b_in_r;
logic             in_valid_r;
logic [WIDTH-1:0] result;

// Register all inputs
always_ff @ (posedge clk, posedge rst)
begin
    // register all inputs
    op_in_r    <= (rst) ? '0 : op_in;
    a_in_r     <= (rst) ? '0 : a_in;
    b_in_r     <= (rst) ? '0 : b_in;
    in_valid_r <= (rst) ? '0 : in_valid;

    // register all outputs
    out       <= (rst) ? '0 : result;
    out_valid <= (rst) ? '0 : in_valid_r;
end

// Compute the result
assign result = ('0 == in_valid_r)    ? '0                 :
                (OP_AND   == op_in_r) ?   a_in_r & b_in_r  :
                (OP_NAND  == op_in_r) ? ~(a_in_r & b_in_r) :
                (OP_OR    == op_in_r) ?   a_in_r | b_in_r  :
                (OP_NOR   == op_in_r) ? ~(a_in_r | b_in_r) :
                (OP_XOR   == op_in_r) ?   a_in_r ^ b_in_r  :
                (OP_XNOR  == op_in_r) ? ~(a_in_r ^ b_in_r) :
                (OP_NOT_A == op_in_r) ? ~a_in_r            :
                (OP_NOT_B == op_in_r) ? ~b_in_r            :
                                        '0                 ;

endmodule
