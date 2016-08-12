
#include <stdlib.h>

#include "world.h"

world worldInit(int w, int h) {
  void* cells = malloc(sizeof(bool) * w * h);
  world result = {w, h, cells};

  for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			setCell(result, x, y, false);
		}
	}
  return result;
};

void setCell(world w, int x, int y, bool v) {
  bool* result = (bool*) w._cells + y * w.width + x;
  *result = v;
}

bool getCell(world w, int x, int y) {
  if (x < 0 || y < 0 || x >= w.width || y >= w.height) {
    return 0;
  } else {
    bool* result = (bool*) w._cells + y * w.width + x;
    return *result;
  }
}

void traverse(world w, traversal f) {
  for (int y = 0; y < w.height; y++) {
    for (int x = 0; x < w.width; x++) {
      f(w, x, y);
    }
  }
}

int getNeighbors(world w, int x, int y) {
  int result = 0;
  for (int sy = -1; sy <= 1; sy++) {
    for (int sx = -1; sx <= 1; sx++) {
      if (sx != 0 || sy != 0) {
        result = result + getCell(w, x + sx, y + sy);
      }
    }
  }
  return result;
};

bool lives(bool alive, int n) {
  if (alive) {
    if (n < 2) {
      return false;
    } else if (n > 3) {
      return false;
    } else {
      return true;
    }
  } else {
    if (n == 3) {
      return true;
    } else {
      return false;
    }
  }
}
