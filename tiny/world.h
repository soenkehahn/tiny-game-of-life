
struct world {
  int width;
  int height;
  void* _cells;
};

world* newWorld(int w, int h);

bool getCell(world* w, int x, int y);

void setCell(world* w, int x, int y, bool v);

typedef void (*traversal) (world* w, int x, int y);

void traverse(world* w, traversal f);

int getNeighbors(world* w, int x, int y);

bool lives(bool alive, int n);

void step(world* old, world* next);

struct simulation {
  world* current;
  world* old;
};

simulation* newSimulation(world* w);

void stepSimulation(simulation* sim);
