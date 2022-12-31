/*
 *  AND Block
 *  
 *  The AND Block module implements a configurable width AND gate for use in the
 *  ALU. An inversion signal is included to invert AND gate output for NAND gate
 *  behavior. This block is completely combinational, and it relies on higher
 *  level modules to register inputs and outputs as required by the application. 
 */
module and_block #(
    parameter int WIDTH = 8
) (
    input  logic            invert,
    input  logic[WIDTH-1:0] a,
    input  logic[WIDTH-1:0] b,
    output logic[WIDTH-1:0] out
);

logic[WIDTH-1:0] int_result;

// Compute an internal result so the inversion logic looks a little cleaner.
assign int_result = a & b;

// But not much cleaner since everyone hates the ternary operator for some
// reason.
assign out = (invert) ? ~int_result : int_result;

endmodule
