
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "world.h"

using namespace std;

#include <iostream>

int fails = 0;

void assertEquals(int a, int b) {
  if (a != b) {
    printf("FAILURE: not equal: %i != %i\n", a, b);
    fails++;
  }
}

void assertEqualStrings(char* a, char* b) {
  if (strcmp(a, b)) {
    printf("FAILURE: not equal: %s != %s\n", a, b);
    fails++;
  }
}

void testInit() {
  grid* w = newWorld(10, 10);
  printf("cell: %i\n", getCell(w, 3, 3));
}

void testSetCell() {
  grid* w = newWorld(10, 10);
  setCell(w, 5, 5, true);
  assertEquals(getCell(w, 5, 5), true);
  setCell(w, 5, 5, false);
  assertEquals(getCell(w, 5, 5), false);
}

void testLoop() {
  grid* w = newWorld(10, 10);
  for (int x = 0; x < w->width; x++) {
    for (int y = 0; y < w->height; y++) {
      setCell(w, x, y, true);
    }
  }
  for (int x = 0; x < w->width; x++) {
    for (int y = 0; y < w->height; y++) {
      assertEquals(true, getCell(w, x, y));
    }
  }
}

char* traversalActions[100];
int ta_index = 0;

void testTraverse() {
  for (int i = 0; i < 100; i++) {
    traversalActions[i] = "END";
  }

  grid* w = newWorld(2, 2);

  traversal f = []
    (grid* w, int x, int y) {
      setCell(w, x, y, true);

      char* s = (char*) malloc(100);
      sprintf(s, "%i, %i, %i", x, y, getCell(w, x, y));
      traversalActions[ta_index] = s;
      ta_index++;
    };
  traverse(w, f);

  assertEqualStrings(traversalActions[0], "0, 0, 1");
  assertEqualStrings(traversalActions[1], "1, 0, 1");
  assertEqualStrings(traversalActions[2], "0, 1, 1");
  assertEqualStrings(traversalActions[3], "1, 1, 1");
  assertEqualStrings(traversalActions[4], "END");
}

void testGetCell() {
  grid* w = newWorld(10, 10);
  traverse(w, [] (grid* w, int x, int y) { setCell(w, x, y, true); });
  assertEquals(getCell(w, -1, -1), 0);
  assertEquals(getCell(w, 3, 5), 1);
  assertEquals(getCell(w, 10, 5), 0);
  assertEquals(getCell(w, 5, 10), 0);
  assertEquals(getCell(w, 12, 12), 0);
}

void testNeighbors() {
  grid* w = newWorld(10, 10);
  setCell(w, 0, 0, true);
  setCell(w, 1, 0, true);
  setCell(w, 2, 1, true);
  setCell(w, 2, 2, true);
  assertEquals(getNeighbors(w, 1, 1), 4);
  setCell(w, 1, 1, true);
  assertEquals(getNeighbors(w, 1, 1), 4);
}

void testLives() {
  assertEquals(lives(true, 0), false);
  assertEquals(lives(true, 1), false);
  assertEquals(lives(true, 2), true);
  assertEquals(lives(true, 3), true);
  assertEquals(lives(true, 4), false);
  assertEquals(lives(true, 5), false);
  assertEquals(lives(true, 6), false);
  assertEquals(lives(true, 7), false);
  assertEquals(lives(true, 8), false);

  assertEquals(lives(false, 0), false);
  assertEquals(lives(false, 1), false);
  assertEquals(lives(false, 2), false);
  assertEquals(lives(false, 3), true);
  assertEquals(lives(false, 4), false);
  assertEquals(lives(false, 5), false);
  assertEquals(lives(false, 6), false);
  assertEquals(lives(false, 7), false);
  assertEquals(lives(false, 8), false);
}

void testStep() {
  grid* green = newWorld(5, 5);
  setCell(green, 1, 0, true);
  setCell(green, 0, 1, true);
  setCell(green, 1, 1, true);
  setCell(green, 2, 1, true);
  setCell(green, 1, 2, true);
  grid* blue = newWorld(5, 5);

  step(green, blue);

  assertEquals(getCell(blue, 0, 0), true);
  assertEquals(getCell(blue, 1, 0), true);
  assertEquals(getCell(blue, 1, 1), false);
  assertEquals(getCell(blue, 4, 4), false);
}

void testSimulation() {
  grid* w = newWorld(3, 3);
  setCell(w, 0, 1, true);
  setCell(w, 1, 1, true);
  setCell(w, 2, 1, true);

  doubleBufferedGrid* sim = newSimulation(w);
  stepSimulation(sim);

  assertEquals(getCell(sim->current, 0, 1), false);
  assertEquals(getCell(sim->current, 1, 1), true);
  assertEquals(getCell(sim->current, 1, 0), true);

  stepSimulation(sim);
  assertEquals(getCell(sim->current, 0, 1), true);
  assertEquals(getCell(sim->current, 1, 1), true);
  assertEquals(getCell(sim->current, 1, 0), false);
}

int main() {
  testInit();
  testSetCell();
  testLoop();
  testTraverse();
  testGetCell();
  testNeighbors();
  testLives();
  testStep();
  testSimulation();

  if (fails > 0) {
    printf("Failed: %i\n", fails);
    exit(1);
  }
}
