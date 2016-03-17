#ifndef COMPILER_INTERFACE_H
#define COMPILER_INTERFACE_H

/*
 * Copyright (c) 2016 CERN
 * @author Michele Castellana <michele.castellana@cern.ch>
 *
 * This source code is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "analyzer.h"
#include "elaborator.h"
#include "simulator.h"

/**
 * @brief Class that represents a single compiler instance. Icarus and GHDL
 * have to provide such interface.
 */
class Compiler : public virtual Analyzer, public virtual Elaborator, public virtual Simulator {
   public:
      Compiler() {};
      virtual ~Compiler() {};

      enum Type { VERILOG, VHDL };

};

#endif /* COMPILER_INTERFACE_H */
