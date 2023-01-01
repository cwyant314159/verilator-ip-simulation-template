Verilator IP Simulation Template
================================

This project is inteded to serve as a template for the development of IP cores
simulated with Verilator. The design under test is an ALU module that implements
an AND, NAND, OR, NOR, XOR, and XNOR operation on two configurable length inputs
both `a` and `b` individually. There are also opcodes for a unary NOT on `a` and
`b`. To make this small example project a little more complex, the actual
operations are done inside of sub-modules that are instantiated in the main ALU
module.

Required Software
-----------------

The following is a list of all software needed to run the simulations in this
repo.

- make
- Verilator
- GCC

All scripts and Makefiles assume the tools will be on the system path.

Folder Structure
----------------

The folder structure for this project is inspired by the folder structure I used
during my time working as a hardware engineer developing firmware for FPGA's. A
given project would have a directory called IP that would contain all the custom
(i.e. not vendor provided) IP cores developed for a given project. Each IP core
has its own subdirectory within the IP folder. In these subdirectories are the
HDL, device driver (C/C++), TCL scripts, and simulations for a given module. The
project mainly focuses on creating a template for Verilator simulations, so the
devce drivers and TCL scripts have been omitted.

Each module should have one or more simulations. In most cases, a single
simulation that exercises the main scenarios as well as some known edge cases
of the main module is good enough. However, if the module has several
sub-modules (like the ALU), it is often best to simulate these smaller pieces
in isolation. This project takes the latter approach and implements a simulation
for each operation block and the top level ALU IP core.

Besides the IP core folder for the ALU, the IP directory also contains a
Verilator support directory. This directory contains a Makefile whose only
purpose is to compile the required C++ files from the Verilator install into an
archive file for use in each simulation. The Makefile also copies the header
files from the Verilator install into a project local include directory. This
keeps individual simulaiton Makefiles from referencing system install paths.
This odd design decision was made to allow a C++ simulation to link the
Verilated HDL archive file instead of using Verilator to build the test bench
executable with `--exe` and `--build`. By building simulations this way, the
test bench can be implemented using multiple C++ files and lead to more
re-usable test benches. All tutorials I found online only showed supplying
Verilator with one `main.cpp` file that contained the entire test bench.

If you know of a way to get Verilator to build a multiple C++ files, please
submit a pull-request with an example. I am very interested to know if it's
possible.


Simulation Makefiles
--------------------

The Makefiles in the module's simulation directory follow the same structure
as the Makefile in my [generic-application-template](https://github.com/cwyant314159/generic-application-template)
repo. This README will only discuss any important differences from the 
template Makefile.

The first major difference between the simulation Makefile and the template is
the inclusion of variables related to the Verilator support ( `VERI_xx` ) and
the DUT ( `DUT_LIB` ) libraries. These variables setup the paths and library
names needed by the Verilator and C++ compiles.

Variables prefixed with `SV_` are for specifying SystemVerilog (or Verilog)
source files and include paths. Since SystemVerilog packages must be listed
first when calling the Verilator command, a separate `SV_PKGS` variable is
created and assigned to the first elements of the `SV_SRCS` variable. Verilator
is a little weird in that the directories of the source files must be passed to
verilator with the `-I` argument (similar to GCC's `-I`). The variable
`SV_INC_DIRS` will contain the relative directory paths of all the files in the
`SV_SRCS` variable.

The `VERI_FLAGS` variable contains all the flags passed to Verilator for both
verilation and linting.

There are several additional targets that are required to handle Verilator 
simulation builds. To just verilate the HDL, a user can run the `verilate`
target. The output of this target is the DUT static library located in the
directory specified in the `VERI_DIR` variable. The `lint` target will run
Verilator with the `--lint-only` argument and output all linter violations to
the terminal.

Aside from the additional variables and targets, there is also an dependency
ordering requirment on the `all` and application linking target. To link the
supporting libraries and object files in the correct order, the linking target
must list the dependencies in the following order: 

1. C++ object files ( `OBJS` )
2. DUT library ( `DUT_LIB` ) 
3. Verilator support library ( `VERI_SUPPORT_LIB` )

```bash
# C++ application link target. The
# ordering of the target dependencies
# matters. 
$(BIN_DIR)/$(BIN): $(OBJS) $(DUT_LIB) $(VERI_SUPPORT_LIB)
```

This ordering only ensures all object and library files are linked in the
correct order. To handle the build order, the `all` target must have its
dependencies in the following order: 

1. Verilator support library ( `VERI_SUPPORT_LIB` )
2. DUT library ( `DUT_LIB` )
3. C++ object files ( `OBJS` )

```bash
# Build the entire test bench. The
# all target buids the Verilator
# support library and the DUT library
# before building the final test bench
# executable.
all: $(VERI_SUPPORT_LIB) $(DUT_LIB) $(BIN_DIR)/$(BIN) 
```
