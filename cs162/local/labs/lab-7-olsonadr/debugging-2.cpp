/*
 * This program allocate and print arrays of the squares up to a specified
 * value n.
 *
 * Once compiled, you can run this program like so (here, we're using n = 7):
 *   ./debugging-2 7
 */

#include <iostream>
#include <cstdlib>

#include "dynarray.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Error: must specify a value for n." << std::endl;
    std::cerr << std::endl;
    std::cerr << "usage: " << argv[0] << " <n>" << std::endl;
    return 1;
  }

  int n = strtol(argv[1], NULL, 0);
  if (n <= 0) {
    std::cerr << "Error: n must be a positive integer value." << std::endl;
    std::cerr << std::endl;
    std::cerr << "usage: " << argv[0] << " <n>" << std::endl;
    return 1;
  }

  Dynarray d1, d2, d3 = d1;

  for (int i = 0; i < n; i++) {
    d1.add(i * i);
  }

  d2 = d1;

  std::cout << "== d1 (size: " << d1.size() << "):" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "   " << d1.get(i) << std::endl;
  }

  std::cout << std::endl << "== d2 (size: " << d2.size() << "):" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "   " << d2.get(i) << std::endl;
  }

  std::cout << std::endl << "== d3 (size: " << d3.size() << "):" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "   " << d3.get(i) << std::endl;
  }
}
