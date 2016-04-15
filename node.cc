#include "node.h"

#include <iostream>
#include <algorithm>

std::ostream& operator<<(std::ostream &out, Node const &node) {
  char  c = '?';
  switch(node.value()) {
  case Node::V0:  c = '0'; break;
  case Node::V1:  c = '1'; break;
  case Node::VX:  c = 'X'; break;
  case Node::VZ:  c = 'Z'; break;
  case Node::VH:  c = 'H'; break;
  case Node::VL:  c = 'L'; break;
  }
  out << c;
  return  out;
}

Bus Bus::slice(unsigned  hi, unsigned  lo) {
  hi = std::min(hi, m_width-1);
  if(hi < lo)  return  Bus();

  Node     *const  src = m_nodes.get();
  unsigned  const  len = hi-lo+1;
  Node     *const  dst = new Node[len];
  std::copy(src+lo, src+hi+1, dst);
  return  Bus(len, dst);
}

Bus Bus::concat(Bus& o) {
  unsigned const  wleft =   m_width;
  unsigned const  wrght = o.m_width;
  Node *const  res = new Node[wleft+wrght];
  for(unsigned  i = 0; i < wrght; i++) res[      i] =       o[i];
  for(unsigned  i = 0; i < wleft; i++) res[wrght+i] = (*this)[i];
  return  Bus(wleft+wrght, res);
}

Net::Net(std::string const& name, unsigned width)
  : Bus(width), m_name(name) {}

Net::Net(std::string const& name, unsigned  width, Node* nodes)
  : Bus(width, nodes), m_name(name) {}

Net::~Net() {}

std::ostream& operator<<(std::ostream &out, Net const &net) {
  out << net.name() << "=\"";
  for(auto  it = net.end(); --it >= net.begin();)  out << *it;
  out << '"';
  return  out;
}
