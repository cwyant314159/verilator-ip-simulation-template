/****** alu.sv ******/
module alu #(
    parameter int WIDTH = 6
) (
    input logic             clk,
    input logic             rst,

    input  logic[2:0]       op_in,
    input  logic[WIDTH-1:0] a_in,
    input  logic[WIDTH-1:0] b_in,
    input  logic            in_valid,

    output logic[WIDTH-1:0] out,
    output logic            out_valid
);

import op_code_pkg::*;

logic [2:0]       op_in_r;
logic [WIDTH-1:0] a_in_r;
logic [WIDTH-1:0] b_in_r;
logic             in_valid_r;
logic             inv;
logic [WIDTH-1:0] and_out;
logic [WIDTH-1:0] or_out;
logic [WIDTH-1:0] xor_out;
logic [WIDTH-1:0] not_a_out;
logic [WIDTH-1:0] not_b_out;
logic [WIDTH-1:0] result;

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

// Determine if the invert control bit needs to be set.
assign inv = (OP_NAND  == op_in_r) ? '1 :
             (OP_NOR   == op_in_r) ? '1 :
             (OP_XNOR  == op_in_r) ? '1 :
                                     '0 ;

// Output the result based on the op code.
always_comb
begin
    if (!in_valid_r)
    begin
        result = '0;
    end
    else if (OP_AND == op_in_r || OP_NAND == op_in_r)
    begin
        result = and_out;
    end
    else if (OP_OR == op_in_r || OP_NOR == op_in_r)
    begin
        result = or_out;
    end
    else if (OP_XOR == op_in_r || OP_XNOR == op_in_r)
    begin
        result = xor_out;
    end
    else if (OP_NOT_A == op_in_r)
    begin
        result = not_a_out;
    end
    else if (OP_NOT_B == op_in_r)
    begin
        result = not_b_out;
    end
    else
    begin
        result = '0;
    end
end

// Module instances
and_block #(
    .WIDTH(WIDTH)
) and0 (
    .invert (inv),
    .a      (a_in_r),
    .b      (b_in_r),
    .out    (and_out)
);

or_block #(
    .WIDTH(WIDTH)
) or0 (
    .invert (inv),
    .a      (a_in_r),
    .b      (b_in_r),
    .out    (or_out)
);

xor_block #(
    .WIDTH(WIDTH)
) xor0 (
    .invert (inv),
    .a      (a_in_r),
    .b      (b_in_r),
    .out    (xor_out)
);

not_block #(
    .WIDTH(WIDTH)
) notA_0 (
    .in     (a_in_r),
    .out    (not_a_out)
);

not_block #(
    .WIDTH(WIDTH)
) notB_0 (
    .in     (b_in_r),
    .out    (not_b_out)
);

endmodule
