/*
 * Copyright (c) 2016 CERN
 * @author Thomas B. Preusser <thomas.preusser@utexas.edu>
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

#ifndef NODE_H
#define NODE_H

#include <memory>
#include <iostream>

/**
 * This header defines classes representing the electrical wiring of
 * modules:
 *
 * Node:
 *  A single physical wire that carries one value at each point in time.
 *  The possible values are defined by the type Node::value_t. They
 *  comprise the subset ('0', '1', 'X', 'Z', 'H', 'L') of the VHDL
 *  std_logic type.
 *
 * Bus:
 *  A collection of Nodes for the purpose of making bulk connections.
 *  Nodes exist on their own right and are not required to be part of a
 *  Bus. On the other hand, a Node may be named in multiple Busses and, in
 *  fact, appear multiple times in the same Bus. Electrically, all
 *  appearances of a Node are indistinguishable.
 *
 * Net:
 *  A Bus with a name. This class may become obsolete by using maps
 *  mapping a name to a Bus in different places of the circuit
 *  according to the corresponding perspective. The same Bus may be addressed
 *  through different names, e.g., within an instantiated module and within
 *  the surrounding instantiating module.
 */

/**
 * @brief Represents a single physical wire and its current value.
 *
 * This class is a thin wrapper around a canonical internal representative
 * of an electrical node.
 */
class Node {

 public:
  /** The supported Node values. */
  enum value_t { V0, V1, VX, VZ, VH, VL };

 private:
  /**
   * The actual canonical representative of the electrical Node.
   * This will be the proper place to attach value change listeners,
   * event lists and similar things.
   */
  class Box {
    friend class Node;
    value_t  m_val;
  public:
    Box(value_t val) : m_val(val) {}
    ~Box() {}  
  };
  std::shared_ptr<Box>  m_canon;

 public:
  Node(value_t  val = value_t::VX) : m_canon(std::make_shared<Box>(val)) {}
  Node(Node const &o) : m_canon(o.m_canon) {}
  ~Node() {}

 public:
  value_t  value()   const { return  m_canon->m_val; }
  operator value_t() const { return  value(); }

  Node& operator=(value_t  val) {
    m_canon->m_val = val;
    return *this;
  }
};
// class Node

std::ostream& operator<<(std::ostream &out, Node const &node);

/**
 * @brief Represents a list of Nodes.
 */
class Bus {
  unsigned               m_width;
  std::shared_ptr<Node>  m_nodes;

 public:
  Bus(unsigned  width = 0) : Bus(width, new Node[width]) {}
  Bus(unsigned  width, Node *nodes)
    : m_width(width), m_nodes(nodes, [](Node *nodes) { delete [] nodes; }) {
  }
  ~Bus() {}

  //+ Container of Nodes +++++++++++++++++++++++++++++++++++++++++++++++++++++
 public:
  unsigned    width()  const { return  m_width; }
  unsigned    size()   const { return  m_width; }
  Node*       begin()        { return  m_nodes.get(); }
  Node const* begin()  const { return  m_nodes.get(); }
  Node*       end()          { return  m_nodes.get()+m_width; }
  Node const* end()    const { return  m_nodes.get()+m_width; }

  Node&       operator[](unsigned  idx)       { return  m_nodes.get()[idx]; }
  Node const& operator[](unsigned  idx) const { return  m_nodes.get()[idx]; }

  Bus slice(unsigned  hi, unsigned  lo);
  Bus operator()(unsigned  hi, unsigned  lo) { return  slice(hi, lo); }

  Bus concat(Bus& o);
  Bus operator,(Bus& o) { return  concat(o); }
};
// class Bus

/**
 * @brief Represent a named Bus.
 */
class Net : public Bus {
  std::string  m_name;
  
 public:
  Net(std::string const& name, unsigned  width = 1);
  Net(std::string const& name, unsigned  width, Node* nodes);
  Net(std::string const& name, Bus const &o) : Bus(o), m_name(name) {}
  ~Net();

 public:
  std::string const& name() const { return  m_name; }
};
// class Net

std::ostream& operator<<(std::ostream &out, Net const &net);
#endif
