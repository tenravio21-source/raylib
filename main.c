#include "player.h"
#include "raylib.h"
#include <stdint.h>

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Modular Raylib Game");

  Player player = {.position = {400, 300}, .velocity = {0, 0}, .speed = 3000.0f, .friction = 0.9f};

  int animFrames = 0;
  Image imNext = LoadImageAnim("assets/player.gif", &animFrames);
  Texture2D texPlayer = LoadTextureFromImage(imNext);

  int currentFrame = 0, frameDelay = 8, frameCounter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update
    UpdatePlayer(&player, screenWidth, screenHeight, texPlayer.width, texPlayer.height);

    frameCounter++;
    if (frameCounter >= frameDelay) {
      currentFrame = (currentFrame + 1) % animFrames;
      UpdateTexture(texPlayer, (uint8_t *)imNext.data + (currentFrame * imNext.width * imNext.height * 4));
      frameCounter = 0;
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(texPlayer, (int)player.position.x, (int)player.position.y, WHITE);
    EndDrawing();
  }

  UnloadTexture(texPlayer);
  UnloadImage(imNext);
  CloseWindow();
  return 0;
}
