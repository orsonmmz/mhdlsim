#ifndef MODULE_H
#define MODULE_H

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

#include <string>
#include <deque>
#include <map>
#include <cassert>
#include <iostream>

class Net;

class Port {
   public:
      enum direction_t { UNKNOWN, IN, OUT, INOUT };
      Port(const std::string& name, unsigned width = 0, direction_t dir = UNKNOWN) :
         name_(name),
         dir_(dir),
         width_(width) {};
      virtual ~Port() {};

      const std::string& name() const { return name_; }
      direction_t direction() const { return dir_; }
      unsigned width() const { return width_; }
      friend std::ostream& operator<<(std::ostream& os, const Port&);
      inline bool operator==(const Port& other) {
         return name_ == other.name_ &&
            dir_ == other.dir_ &&
            width_ == other.width_;
      }
      inline bool operator!=(const Port& other) {
         return !(*this == other);
      }

   private:
      const std::string name_;
      const direction_t dir_;
      const unsigned width_;
};

inline std::ostream& operator<<(std::ostream& os, const Port::direction_t& el) {
   switch( el ) {
      case Port::UNKNOWN:
         os << "unknown";
         break;
      case Port::IN:
         os << "in";
         break;
      case Port::OUT:
         os << "out";
         break;
      case Port::INOUT:
         os << "inout";
         break;
   }
   return os;
}

inline std::ostream& operator<<(std::ostream& os, const Port& el) {
   os << "name " << el.name_ << " "
      << "width " << el.width_ << " "
      << "direction " << el.dir_;
   return os;
}

class ModuleInterface {
   public:
      ModuleInterface( const std::string& name ) :
         name_(name) {};
      virtual ~ModuleInterface() {};

      void make_port( std::string& name, unsigned width = 0, Port::direction_t dir = Port::UNKNOWN ) {
         assert( !name.empty() );
         for( auto it = ports_.begin(); it != ports_.end(); ++it )
            if( (*it)->name() == name )
               assert(false);
         ports_.push_back(new Port(name, width, dir));
      }
      const std::string& name() const { return name_; }
      std::deque<Port*>::size_type size() const { return ports_.size(); }
      friend std::ostream& operator<<(std::ostream& os, const ModuleInterface&);
      // TODO get_default_generic/param(const std::string& ?)const

      // TODO accessors for variables? constants? internal signals?

   protected:
      ///> Name of the component/module.
      const std::string name_;

      ///> Interconnecting ports.
      std::deque<Port*> ports_;
};

inline std::ostream& operator<<(std::ostream& os, const ModuleInterface& el) {
   os << "Interface name " << el.name_ << ".";
   if( el.ports_.size() )
      os << " Ports are:";
   for( auto it = el.ports_.begin(); it != el.ports_.end(); it++ ) {
      os << std::endl << **it;
   }
   return os;
}

class ModuleSpec : public ModuleInterface {
   public:
      ModuleSpec( const std::string& name1, const std::string& name2 ) :
         ModuleInterface( name1 ), instance_name_(name2) {};
      virtual ~ModuleSpec() {};

      void add(Port* val) { assert(val); ports_.push_back(val); }
      std::deque<Port*>& ports() { return ports_; }
      Port* port(unsigned idx) { assert(idx < ports_.size()); return ports_[idx]; }
      // TODO get_generic/param
      // TODO set_generic/param
      const std::string& instance_name() const { return instance_name_; }
      ///> Name of the instance.
      const std::string instance_name_;
};

class ModuleInstance {
   public:
      ModuleInstance(ModuleSpec* iface) :
         iface_(iface) {};
      virtual ~ModuleInstance() {};

      ModuleSpec* iface() const {
         assert(iface_);
         return iface_;
      }
      std::map<const Port, Net*> connections() const {
         return connections_;
      }
      friend std::ostream& operator<<(std::ostream& os, const ModuleInstance&);

      // TODO pick either of the following, the first one may be better
      // as it is possible to assign port using named expressions, like
      // test_module(.clk(clk), .data(data))
      //
      //const Net& net(const Port& port);
      //void connect(const Port&, Net& net);
      //
      //const Net& net(int idx);
      //connect(int idx, Net& net);

      // TODO get_generic/param

   private:
      ///> Associated component/module interface.
      ModuleSpec* iface_;

      // TODO this could be also map<int, Net>
      // TODO if we keep such map, then we have to define comparison functions
      // for Port class
      std::map<const Port, Net*> connections_;

      // TODO const std::map<???> generics_; // aka parameters

};

inline std::ostream& operator<<(std::ostream& os, const ModuleInstance& el) {
   os << "Instance with values: " << std::endl << *el.iface_;
   return os;
}

#endif /* MODULE_H */
