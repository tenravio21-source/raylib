#include "raylib.h"

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(200, 150, 400, 100, BLUE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
