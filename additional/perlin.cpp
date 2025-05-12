#include "perlin.hpp"
#include <cmath>
#include <random>

double perlin_seed[PERLIN_SIZE_ARRAY];

void init_perlin() {
  std::mt19937 engine{std::random_device{}()};
  std::uniform_real_distribution<double> dist(0, 1);
  for (int i = 0; i < PERLIN_SIZE_ARRAY; i++) {
    perlin_seed[i] = dist(engine);
  }
}

static double g(double a) { return (1 - cos(M_PI * a)) / 2; }

static double cerp(double y1, double y2, double a) {
  return (1 - g(a)) * y1 + g(a) * y2;
}

static double f(double x) {
  int i = (int)x;
  double a = fmod(x, 1);
  if (i + 1 == PERLIN_SIZE_ARRAY)
    return cerp(perlin_seed[i], perlin_seed[0], a);
  return cerp(perlin_seed[i], perlin_seed[i + 1], a);
}

static double noise(double t) { return f(fmod(t, PERLIN_SIZE_ARRAY)); }

double perlin(double t) {
  double value = 0.0;
  double to_normal = 0.0;
  for (int i = 0; i < PERLIN_OCTAVES; i++) {
    value += pow(PERLIN_DECAY, i) * noise(pow(2, i) * t);
    to_normal += pow(PERLIN_DECAY, i);
  }

  return value / to_normal;
}
