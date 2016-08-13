
struct grid {
  int width;
  int height;
  bool* _cells;
};

grid* newWorld(int w, int h);

bool getCell(grid* w, int x, int y);

void setCell(grid* w, int x, int y, bool v);

typedef void (*traversal) (grid* w, int x, int y);

void traverse(grid* w, traversal f);

int getNeighbors(grid* w, int x, int y);

bool lives(bool alive, int n);

void step(grid* old, grid* next);

struct doubleBufferedGrid {
  grid* current;
  grid* old;
};

doubleBufferedGrid* newSimulation(grid* w);

void stepSimulation(doubleBufferedGrid* sim);
