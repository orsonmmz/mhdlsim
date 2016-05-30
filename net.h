#ifndef NET_H
#define NET_H

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

#include <vector>
#include <cassert>

/**
 * @brief Class that represents a connection between modules.
 */
class Net {
public:
    Net( const std::string& name,
         const std::string& instance_name,
         unsigned width = 1 )
       : val_(width),
         name_(name),
         instance_name_(instance_name) {};
    virtual ~Net() {};

    ///> Possible net values
    enum value_t { V0, V1, VX, VZ, VH, VL };
    typedef std::vector<value_t> value_vec_t;

    // TODO should it be possible only for the Manager?
    virtual void set_value(const value_vec_t& v) { assert(v.size() == width()); val_ = v; }
    const std::string& name() const { return name_; }
    const std::string& instance_name() const { return instance_name_; }
    virtual const value_vec_t& value() const { return val_; }
    unsigned width() const { return val_.size(); }

    // TODO do we need other net types? in fact everything in the end is
    // just a bunch of bits, so probably could be represented using this class as well

protected:
    value_vec_t val_;
    const std::string name_;
    const std::string instance_name_;
};

/**
 * @brief Class that represents a part select from a net (e.g. net_name[4:2]).
 */
class NetSelect : public Net {
public:
    NetSelect(Net& parent, int msb, int lsb);
    ~NetSelect();

    // TODO update appropriate bits in the parent net
    //void set_value(const value_vec_t& v) { assert(v.size() == width()); val_ = v; }
    // TODO get appropriate bits from val and store them in local val_, then return val_
    //const value_vec_t& value() const { return val_; }

private:
    Net& parent_;
};

#endif /* NET_H */
