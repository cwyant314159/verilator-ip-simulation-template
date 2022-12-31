/*
 *  NOT Block
 *  
 *  The NOT Block module implements a configurable width NOT gate for use in the
 *  ALU. This block is completely combinational, and it relies on higher level
 *  modules to register inputs and outputs as required by the application. 
 */
module not_block #(
    parameter int WIDTH = 8
) (
    input  logic[WIDTH-1:0] in,
    output logic[WIDTH-1:0] out
);

assign out = ~in;

endmodule
