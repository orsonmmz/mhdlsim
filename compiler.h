#ifndef COMPILER_H
#define COMPILER_H

#include "analyzer.h"
#include "elaborator.h"
#include "simulator.h"

/**
 * @brief Class that represents a single compiler instance. Icarus and GHDL
 * have to provide such interface.
 */
class Compiler : public Analyzer, public Elaborator, public Simulator {
public:
    Compiler();
    virtual ~Compiler();

    enum Type { Verilog, VHDL };

};

#endif /* COMPILER_H */
