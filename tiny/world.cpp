
#include <stdlib.h>

#include "world.h"

grid* newWorld(int w, int h) {
  bool* cells = (bool*) malloc(sizeof(bool) * w * h);
  grid* result = (grid*) malloc(sizeof(grid));
  result->width = w;
  result->height = h;
  result->_cells = cells;

  for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			setCell(result, x, y, false);
		}
	}
  return result;
};

bool getCell(grid* w, int x, int y) {
  if (x < 0 || y < 0 || x >= w->width || y >= w->height) {
    return 0;
  } else {
    bool* result = w->_cells + y * w->width + x;
    return *result;
  }
}

void setCell(grid* w, int x, int y, bool v) {
  bool* result = w->_cells + y * w->width + x;
  *result = v;
}

void traverse(grid* w, traversal f) {
  for (int y = 0; y < w->height; y++) {
    for (int x = 0; x < w->width; x++) {
      f(w, x, y);
    }
  }
}

int getNeighbors(grid* w, int x, int y) {
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

grid* __stepOld;

void __stepTraversal(grid* w, int x, int y) {
  bool alive = getCell(__stepOld, x, y);
  setCell(w, x, y, lives(alive, getNeighbors(__stepOld, x, y)));
};

void step(grid* old, grid* next) {
  __stepOld = old;
  traverse(next, __stepTraversal);
}

doubleBufferedGrid* newSimulation(grid* w) {
  doubleBufferedGrid* result = (doubleBufferedGrid*) malloc(sizeof(doubleBufferedGrid));
  result->current = w;
  result->old = newWorld(w->width, w->height);
  return result;
}

void stepSimulation(doubleBufferedGrid* sim) {
  grid* temp = sim->old;
  sim->old = sim->current;
  sim->current = temp;

  step(sim->old, sim->current);
}
