#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
  Vector2 position;
  Vector2 velocity;
  float speed;
  float friction;
} Player;

// Function prototypes
void UpdatePlayer(Player *p, int screenWidth, int screenHeight, int texWidth, int texHeight);

#endif
