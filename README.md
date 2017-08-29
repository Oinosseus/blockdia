# blockdia

A library for abstract visualization of data processing.

All steps of the dataprocessing are shown as separate blocks.
These blocks can be connected together through Inputs and Outputs.
Every block can have public and private parameters assigned.

The library does not include any functions behind the blocks.
It only provides classes (based on the Qt framework) for easy visulazitation.  
Blocks can be created, edited and exported as "block definition" (XML).
Diagrams (flow charts) can be created, edited and exported as "process definition" (XML).

The idea is that external data processing systems provide functionality
that can be abstracted as block definitions
and can be configured by importing the process definition.


# Build Prerequisites

1. [qt](https://www.qt.io/) >= 5.6
2. [doxygen](http://www.stack.nl/~dimitri/doxygen/)
3. [python](https://www.python.org/) >= 3.5

# Build Workflow

Use the ./make.py command to build the library or documentation.

Examples:  
./make -h  
./make build -h  
./make build --debug  
./make all  

