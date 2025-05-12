#ifndef PERLIN_H
#define PERLIN_H

#ifndef PERLIN_SIZE_ARRAY
#define PERLIN_SIZE_ARRAY 9999
#endif

#ifndef PERLIN_DECAY
#define PERLIN_DECAY 0.5
#endif

#ifndef PERLIN_OCTAVES
#define PERLIN_OCTAVES 3
#endif

void init_perlin();

double perlin(double t);

#endif
