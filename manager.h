/*
 * Copyright (c) 2016 CERN
 * @author Maciej Suminski <maciej.suminski@cern.ch>
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

#ifndef MANAGER_H
#define MANAGER_H

#include "compiler_interface.h"
#include <list>

class Simulator;
class Net;
class ModuleInstance;

/**
 * @brief Class responsible for mixed-language elaboration and simulation.
 * Creates simulator instances as needed and coordinates them.
 */
class Manager {
public:
    Manager();
    virtual ~Manager();

    /**
     * @brief Adds a new simulator instance to be managed.
     * @param sim is the instance to be added.
     * @param type is instance type.
     */
    void add_instance(Compiler::Type type, Compiler* sim);
    void add_instance(Compiler* sim, Compiler::Type type) {
       add_instance( type, sim );
    };

    /**
     * @brief Starts the simulation.
     * @param step is when we have to stop.
     * @return 0 if success. Non zero value in case of failure.
     */
    int run( CompilerStep );

    // TODO interface to inspect signals, variables, control the sim flow?

private:
    ///> Instances of simulators to manage.
    std::map<Compiler*, Compiler::Type> instances_;

    ///> Keep list of modules that have to be notified
    ///> when a particular signal changes.
    std::map<Net*, std::list<ModuleInstance*> > sensitivity_;

    ///> Currently active Compiler (i.e. executing code)
    Compiler* current_comp_;

    CompilerStep current_step_;
};

#endif /* MANAGER_H */
