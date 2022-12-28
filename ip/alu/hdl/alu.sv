module alu (

    /* clocking interface */
    input  logic       clock,
    input  logic       reset,

    /* control interface */
    input  logic[2:0]  op,

    /* data input interfaces */
    input  logic       in_valid,
    input  logic[31:0] a,
    input  logic[31:0] b,

    /* data ouput interface */
    output logic       out_valid,
    output logic[31:0] out
);

typedef enum logic[2:0] {
    OP_AND   = 'h0,
    OP_NAND  = 'h1,
    OP_OR    = 'h2,
    OP_NOR   = 'h3,
    OP_XOR   = 'h4,
    OP_XNOR  = 'h5,
    OP_NOT_A = 'h6,
    OP_NOT_B = 'h7
} op_code_t /* verilator public */;

logic       valid_reg;
logic[2:0]  op_reg;
logic[31:0] a_reg;
logic[31:0] b_reg;

logic       next_out_valid;
logic[31:0] next_out;

assign next_out_valid = valid_reg;

always_comb
begin
    case(op_reg)
    OP_AND   : next_out =   a_reg & b_reg;
    OP_NAND  : next_out = ~(a_reg & b_reg);
    OP_OR    : next_out =   a_reg | b_reg;
    OP_NOR   : next_out = ~(a_reg | b_reg);
    OP_XOR   : next_out =   a_reg ^ b_reg;
    OP_XNOR  : next_out = ~(a_reg ^ b_reg);
    OP_NOT_A : next_out = ~a_reg;
    OP_NOT_B : next_out = ~b_reg;
    endcase
end

always_ff @ (posedge clock or posedge reset)
begin
    op_reg    <= (reset) ? '0 : op;

    valid_reg <= (reset) ? '0 : in_valid;
    a_reg     <= (reset) ? '0 : a;
    b_reg     <= (reset) ? '0 : b;

    out_valid <= (reset) ? '0 : next_out_valid;
    out       <= (reset) ? '0 : next_out;
end

endmodule
