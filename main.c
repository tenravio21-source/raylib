#include "raylib.h"

typedef struct Player {
  Vector2 position;
  Vector2 velocity;
  float speed;
  float friction;
} Player;

void UpdatePlayer(Player *p, int screenWidth, int screenHeight, int spriteWidth, int spriteHeight) {
  Vector2 input = {0};

  // Get Keyboard Input
  if (IsKeyDown(KEY_RIGHT))
    input.x += 1.0f;
  if (IsKeyDown(KEY_LEFT))
    input.x -= 1.0f;
  if (IsKeyDown(KEY_DOWN))
    input.y += 1.0f;
  if (IsKeyDown(KEY_UP))
    input.y -= 1.0f;

  // 1. Apply input to velocity
  p->velocity.x += input.x * p->speed;
  p->velocity.y += input.y * p->speed;

  // 2. Apply position update
  p->position.x += p->velocity.x;
  p->position.y += p->velocity.y;

  // 3. Apply friction (so the player doesn't slide forever)
  p->velocity.x *= p->friction;
  p->velocity.y *= p->friction;

  if (p->position.x < 0) {
    p->position.x = 0;
    p->velocity.x = 0; // Stop horizontal momentum
  }
  // Right Wall (Screen Width - Sprite Width)
  if (p->position.x > screenWidth - spriteWidth) {
    p->position.x = screenWidth - spriteWidth;
    p->velocity.x = 0;
  }

  // Top Wall
  if (p->position.y < 0) {
    p->position.y = 0;
    p->velocity.y = 0; // Stop vertical momentum
  }

  // Bottom Wall (Screen Height - Sprite Height)
  if (p->position.y > screenHeight - spriteHeight) {
    p->position.y = screenHeight - spriteHeight;
    p->velocity.y = 0;
  }
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  Player player = {.position = {400, 300}, .velocity = {0, 0}, .speed = 1.5f, .friction = 0.9f};

  Vector2 input = {1.0f, 0.0f};

  InitWindow(screenWidth, screenHeight, "GIF Loading Example");

  int animFrames = 0;
  Image imNext = LoadImageAnim("assets/player.gif", &animFrames);
  Texture2D texPlayer = LoadTextureFromImage(imNext);

  int currentFrame = 0;
  int frameDelay = 8;
  int frameCounter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdatePlayer(&player, screenWidth, screenHeight, texPlayer.width, texPlayer.height);
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

    DrawTexture(texPlayer, (int)player.position.x, (int)player.position.y, WHITE);

    EndDrawing();
  }
  UnloadTexture(texPlayer);
  UnloadImage(imNext);
  CloseWindow();

  return 0;
}
