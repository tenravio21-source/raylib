#include "raylib.h"

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "GIF Loading Example");
  int animFrames = 0;
  Image imNext = LoadImageAnim("assets/player.gif", &animFrames);
  Texture2D texPlayer = LoadTextureFromImage(imNext);
  int currentFrame = 0;
  int frameDelay = 8;
  int frameCounter = 0;
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    frameCounter++;
    if (frameCounter >= frameDelay) {
      currentFrame++;
      if (currentFrame >= animFrames)
        currentFrame = 0;
      UpdateTexture(texPlayer, imNext.data + (currentFrame * imNext.width * imNext.height * 4));
      frameCounter = 0;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(texPlayer, 100, 100, WHITE);
    EndDrawing();
  }
  UnloadTexture(texPlayer);
  UnloadImage(imNext);
  CloseWindow();
  return 0;
}
