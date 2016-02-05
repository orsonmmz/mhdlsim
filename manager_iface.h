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

#ifndef MANAGER_IFACE_H
#define MANAGER_IFACE_H

/**
 * @brief Interface for Simulator objects to interact with the Manager class.
 */
class ManagerInterface {
public:
    virtual ~ManagerInterface() = 0;

    /**
     * @brief Asks the Manager to create an instance of a specific module and
     * connect given nets.
     * // TODO when connecting, should it check if we connect e.g.
     * two outputs together? or if net sizes are correct?
     */
    virtual int require(const std::string& module, std::map<const std::string, Net*> connections) = 0;
    virtual int require(const std::string& module, std::deque<Net*> connections) = 0;

    /**
     * @brief Sets a new value for a specific net and notifies all connected
     * modules.
     */
    // TODO delayed assignments? or should the simulator take care of delays by
    // putting appropriate events in the queue?
    virtual set_net_value(Net*net, Net::value_t v);

    /**
     * @brief Notifies the Manager that all events in this time cycle have been
     * executed. It is time to allow other simulators to react to the changes.
     * Note that there the caller event queue may still contain events, and they
     * will be executed in the same time step.
     */
    virtual void yield() = 0;
}

#endif /* MANAGER_IFACE_H */
