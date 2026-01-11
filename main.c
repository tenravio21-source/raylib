#include "item.h"
#include "player.h"
#include "raylib.h"
#include <stdint.h>

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  int health = 100;
  bool gameOver = false;
  int itemCount = 5;
  Item coins[5];

  InitWindow(screenWidth, screenHeight, "Modular Raylib Game");

  Player player = {.position = {400, 300}, .velocity = {0, 0}, .speed = 3000.0f, .friction = 0.9f};

  int animFrames = 0;
  Image imNext = LoadImageAnim("assets/player.gif", &animFrames);
  Texture2D texPlayer = LoadTextureFromImage(imNext);

  int currentFrame = 0, frameDelay = 8, frameCounter = 0;

  SetTargetFPS(60);

  for (int i = 0; i < itemCount; i++) {
    coins[i] = (Item){
        .position = {(float)GetRandomValue(50, 750), (float)GetRandomValue(50, 400)}, .radius = 10.0f, .active = true};
  }

  while (!WindowShouldClose()) {

    if (!gameOver) {
      // 1. Only update movement if alive
      UpdatePlayer(&player, screenWidth, screenHeight, texPlayer.width, texPlayer.height);

      // 2. Subtract damage (CheckItemCollisions returns 1 if hit)
      int hits = CheckItemCollisions(&player, coins, itemCount);
      if (hits > 0) {
        health -= 20; // Lose 20 health per hit
      }

      // 3. Check for Death
      if (health <= 0) {
        health = 0;
        gameOver = true;
      }

      // ... GIF animation logic ...
      frameCounter++;
      if (frameCounter >= frameDelay) {
        currentFrame = (currentFrame + 1) % animFrames;
        UpdateTexture(texPlayer, (uint8_t *)imNext.data + (currentFrame * imNext.width * imNext.height * 4));
        frameCounter = 0;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!gameOver) {
      DrawItems(coins, itemCount);
      DrawTexture(texPlayer, (int)player.position.x, (int)player.position.y, WHITE);
    } else {
      DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
      DrawText("Press [R] to Restart", screenWidth / 2 - 80, screenHeight / 2 + 30, 20, DARKGRAY);

      if (IsKeyPressed(KEY_R)) {
        // Reset Game
        health = 100;
        gameOver = false;
        player.position = (Vector2){400, 300};
        // Optional: Re-activate items here
      }
    }

    // Health Bar UI
    DrawRectangle(10, 10, 200, 20, LIGHTGRAY);
    DrawRectangle(10, 10, health * 2, 20, RED); // Bar shrinks with health
    DrawText(TextFormat("HP: %d", health), 15, 12, 15, WHITE);

    EndDrawing();
  }
  UnloadTexture(texPlayer);
  UnloadImage(imNext);
  CloseWindow();
  return 0;
}
