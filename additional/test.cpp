#include "perlin.hpp"
#include <iostream>

int main() {
  init_perlin();
  for (int i = 0; i < PERLIN_SIZE_ARRAY; i++) {
    std::cout << perlin(i) << std::endl;
  }

  return 0;
}
