#ifndef ITEM_H
#define ITEM_H

#include "player.h"
#include "raylib.h"

typedef struct Item {
  Vector2 position;
  float radius;
  bool active;
} Item;

void DrawItems(Item *items, int count);
int CheckItemCollisions(Player *p, Item *items, int count);

#endif
