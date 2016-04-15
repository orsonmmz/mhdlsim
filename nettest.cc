#include "node.h"

#include <iostream>

int main(int argc, char*argv[]) {

  // Create an 8-bit net
  Net  a("a", 8);
  std::cout << a << std::endl;

  // Slice out the high half and manipulate a bit in it
  std::cout << "Manipulating a slice ..." << std::endl;
  Bus  b = a(7, 4);
  b[2] = Node::V0;
  std::cout << a << std::endl;

  // Concatenate two duplicates of the slice and give the result a name
  std::cout << "Duplicated slice ..." << std::endl;
  Net  c("c", (b,b));
  std::cout << c << std::endl;
  b[0] = Node::V1;
  std::cout << c << std::endl;
  
  return 0;
}
