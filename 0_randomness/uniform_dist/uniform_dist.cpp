#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <raylib.h>

#define WIDTH 1000
#define HEIGHT 400
#define TOTAL 100

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(0, TOTAL - 1);
std::normal_distribution<float> normal(TOTAL / 2., TOTAL / 6.);

int random_counts[TOTAL];

void init() {
  InitWindow(WIDTH, HEIGHT, "Uniform distrubution");
  for (int i = 0; i < TOTAL; i++) {
    random_counts[i] = 0;
  }

  std::srand(std::time(nullptr));

  SetTargetFPS(180);
}

void set_array_uniform() {
  int index = dist(gen);
  random_counts[index]++;
}

void set_array_normal() {
  int index = (int)normal(gen);
  if (index >= 0 && index < TOTAL) {
    random_counts[index]++;
  }
}

void set_array_c() {
  int index = std::rand() % TOTAL;
  random_counts[index]++;
}

int accept_reject() {
  while (true) {
    int r1 = dist(gen);
    int probability = std::sin(r1 / 4) * 5 + 10;
    int r2 = dist(gen);

    if (r2 < probability) {
      return r1;
    }
  }
}

void set_array_accept_reject() {
  int index = accept_reject();
  random_counts[index]++;
}

void update() { set_array_accept_reject(); }

void draw_rectangle_filled(int pos_x, int pos_y, int width, int height,
                           Color border_color, Color fill_color) {
  DrawRectangle(pos_x, pos_y, width, height, border_color);

  int inner_x = pos_x + 2;
  int inner_y = pos_y + 2;

  int inner_width = width - 4;
  int inner_heigth = height - 4;
  if (inner_width > 0 && inner_heigth > 0) {
    DrawRectangle(inner_x, inner_y, inner_width, inner_heigth, fill_color);
  }
}

void draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  int w = WIDTH / TOTAL;
  for (int x = 0; x < TOTAL; x++) {
    draw_rectangle_filled(x * w, HEIGHT - random_counts[x], w - 1,
                          random_counts[x], BLACK, BLUE);
  }

  EndDrawing();
}

void close() { CloseWindow(); }

int main() {
  init();

  while (!WindowShouldClose()) {
    update();
    draw();
  }

  close();
  return 0;
}
