Verilator IP Simulation Template
================================

This project is inteded to serve as a template for the development of IP cores
simulated with Verilator. The design under test is an ALU module that implements
an AND, NAND, OR, NOR, XOR, and XNOR operation on two configurable length inputs
both `a` and `b` individually. There are also opcodes for a unary NOT on `a` and
`b`. To make this small example project a little more complex, the actual
operations are done inside of sub-modules that are instantiated in the main ALU
module.

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

Required Software
-----------------

> _TODO_

Simulation Makefiles
--------------------

> _TODO_
