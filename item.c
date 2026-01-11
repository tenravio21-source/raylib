#include "item.h"
#include "player.h"

void DrawItems(Item *items, int count) {
  for (int i = 0; i < count; i++) {
    if (items[i].active) {
      DrawCircleV(items[i].position, items[i].radius, GOLD);
      DrawCircleLinesV(items[i].position, items[i].radius, ORANGE);
    }
  }
}

int CheckItemCollisions(Player *p, Item *items, int count) {
  int collected = 0;
  for (int i = 0; i < count; i++) {
    if (items[i].active) {
      // Treat player as a circle for simple collision
      if (CheckCollisionCircles(p->position, 20, items[i].position, items[i].radius)) {
        items[i].active = false;
        collected++;
      }
    }
  }
  return collected;
}
