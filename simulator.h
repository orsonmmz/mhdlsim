/*
 * Copyright (c) 2016 CERN
 * @author Maciej Suminski <maciej.suminski@cern.ch>
 *
 * This source code is free software; you can redistribute it
 * and/or modify it in source code form under the terms of the GNU
 * General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "module.h"

///> Universal simulation time unit.
typedef sim_time_t unsigned long long;

/**
 * @brief Class that represents a single simulator instance. Icarus and GHDL
 * have to provide such interface.
 */
class Simulator {
public:
    enum sim_type { Verilog, VHDL };

    Simulator()
    virtual ~Simulator();

    /**
     * @brief Initializes the simulator.
     * @return 0 in case of success.
     */
    virtual int initialize() = 0;

    /**
     * @brief Analyzes the input files.
     * @return 0 in case of success.
     */
    virtual int analyze() = 0;

    /**
     * @brief Performs elaboration of the required entity/arch.
     * @param ent entity name.
     * @param arch architecture name.
     * @return unknown modules/architectures discovered during elaboration.
     */
    virtual ModuleInstance* elaborate(const std::string& ent, const std::string& arch) = 0;

    /**
     * @brief Complete the elaboration.
     * @param modules modules/architectures needed to complete the elaboration.
     * @return 0 in case of success.
     */
    virtual int elaborate(ModuleInstance* modules) = 0;

    /**
     * @brief Creates an instance with a given name.
     * This function is to be called by the Manager. It will also assign nets
     * to ports.
     */
    // TODO generic/parameters?
    ModuleInstance& instantiate(const ModuleInterface& iface);

    /**
     * @brief Notifies the simulator that a net value has changed.
     * @param net is the net which value has just changed.
     */
    void notify(Net* net);

    /**
     * @brief Executes the next event from the event queue.
     * @return 0 in case of success.
     */
    virtual int step_event() = 0;

    /**
     * @brief Returns the timestamp of the next event in the event queue.
     * @return Timestamp of the next event to be executed.
     */
    virtual sim_time_t next_event() const;

    /**
     * @brief Returns the current simulation time.
     */
    virtual sim_time_t current_time() const;

    /**
     * @brief Add file(s).
     */
    virtual void add_files(std::set<std::string&>&);
    virtual void add_file(const std::string&) = 0;

    /**
     * @brief Advances the simulation by time. All events in the queue will be
     * executed.
     * @param time is the amount of time for advancement.
     */
    virtual int advance_time(sim_time_t time) = 0;

protected:
    ///> Modules provided by this simulator instance. They can be instantiated
    ///> as required. The string key is the name of the module, as defined
    ///> in its interface.
    std::map<const std::string, ModuleInterface>;

    ///> Instances of modules handled by this simulator instance. The string key
    ///> is the name of an instance, not the name of the module.
    std::map<const std::string, ModuleInstance>;

    // TODO maybe one day an interface to call subprograms? surely not for
    // the first release

    // TODO think about debugging interface:
    // code stepping (how to obtain the reference to the currently executed line)
    // internal variables/processes lookup/modification
    // breakpoints
};

#endif /* SIMULATOR_H */
