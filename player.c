#include "player.h"
#include "raymath.h"
#include <math.h>

// Static means these are "private" to this file
static Vector2 GetPlayerInput() {
  Vector2 input = {0};
  if (IsKeyDown(KEY_RIGHT))
    input.x += 1.0f;
  if (IsKeyDown(KEY_LEFT))
    input.x -= 1.0f;
  if (IsKeyDown(KEY_DOWN))
    input.y += 1.0f;
  if (IsKeyDown(KEY_UP))
    input.y -= 1.0f;

  if (Vector2Length(input) > 0)
    input = Vector2Normalize(input);
  return input;
}

static void ApplyBoundaries(Player *p, int sw, int sh, int tw, int th) {
  if (p->position.x < 0) {
    p->position.x = 0;
    p->velocity.x *= -0.5f;
  } else if (p->position.x > sw - tw) {
    p->position.x = (float)sw - tw;
    p->velocity.x *= -0.5f;
  }

  if (p->position.y < 0) {
    p->position.y = 0;
    p->velocity.y *= -0.5f;
  } else if (p->position.y > sh - th) {
    p->position.y = (float)sh - th;
    p->velocity.y *= -0.5f;
  }
}

void UpdatePlayer(Player *p, int screenWidth, int screenHeight, int texWidth, int texHeight) {
  float dt = GetFrameTime();
  Vector2 input = GetPlayerInput();

  p->velocity.x += input.x * p->speed * dt;
  p->velocity.y += input.y * p->speed * dt;

  p->position.x += p->velocity.x * dt;
  p->position.y += p->velocity.y * dt;

  float frictionFactor = powf(p->friction, dt * 60.0f);
  p->velocity.x *= frictionFactor;
  p->velocity.y *= frictionFactor;

  ApplyBoundaries(p, screenWidth, screenHeight, texWidth, texHeight);
}
