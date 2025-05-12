#include <random>
#include <raylib.h>

#define WIDTH 640
#define HEIGHT 240

#define BLUE_ALPHA                                                             \
  (Color) { 0, 0, 0, 10 }

std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<float> dist(320, 70);

typedef struct {
  int x;
  int y;
} Circle;

Circle my_circle;
RenderTexture2D canvas;

void init() {
  InitWindow(WIDTH, HEIGHT, "Gaussian Distribution");
  my_circle = (Circle){0, 120};
  SetTargetFPS(60);
  canvas = LoadRenderTexture(WIDTH, HEIGHT);

  BeginTextureMode(canvas);
  ClearBackground(RAYWHITE);
  EndTextureMode();
}

void update() {
  int choice = dist(gen);
  my_circle.x = choice;
}

void draw() {
  BeginTextureMode(canvas);
  DrawCircle(my_circle.x, my_circle.y, 16, BLUE_ALPHA);
  EndTextureMode();
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawTextureRec(canvas.texture,
                 (Rectangle){0, 0, (float)WIDTH, (float)-HEIGHT},
                 (Vector2){0, 0}, RAYWHITE);
  EndDrawing();
}

void close() {
  UnloadRenderTexture(canvas);
  CloseWindow();
}

int main() {
  init();

  while (!WindowShouldClose()) {
    update();
    draw();
  }

  close();

  return 0;
}
