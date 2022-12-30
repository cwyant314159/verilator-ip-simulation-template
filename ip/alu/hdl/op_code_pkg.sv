package op_code_pkg;

typedef enum logic [2:0] {
  OP_AND   = 'h0,
  OP_NAND  = 'h1,
  OP_OR    = 'h2,
  OP_NOR   = 'h3,
  OP_XOR   = 'h4,
  OP_XNOR  = 'h5,
  OP_NOT_A = 'h6,
  OP_NOT_B = 'h7
} operation_t /*verilator public*/;

endpackage
