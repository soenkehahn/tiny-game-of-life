
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
  world w = worldInit(10, 10);
  printf("cell: %i\n", getCell(w, 3, 3));
}

void testSetCell() {
  world w = worldInit(10, 10);
  setCell(w, 5, 5, true);
  assertEquals(getCell(w, 5, 5), true);
  setCell(w, 5, 5, false);
  assertEquals(getCell(w, 5, 5), false);
}

void testLoop() {
  world w = worldInit(10, 10);
  for (int x = 0; x < w.width; x++) {
    for (int y = 0; y < w.height; y++) {
      setCell(w, x, y, true);
    }
  }
  for (int x = 0; x < w.width; x++) {
    for (int y = 0; y < w.height; y++) {
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

  world w = worldInit(2, 2);

  traversal f = []
    (world w, int x, int y) {
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
  world w = worldInit(10, 10);
  traverse(w, [] (world w, int x, int y) { setCell(w, x, y, true); });
  assertEquals(getCell(w, -1, -1), 0);
  assertEquals(getCell(w, 3, 5), 1);
  assertEquals(getCell(w, 10, 5), 0);
  assertEquals(getCell(w, 5, 10), 0);
  assertEquals(getCell(w, 12, 12), 0);
}

void testNeighbors() {
  world w = worldInit(10, 10);
  traverse(w, [] (world w, int x, int y) { setCell(w, x, y, false); });
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

int main() {
  testInit();
  testSetCell();
  testLoop();
  testTraverse();
  testGetCell();
  testNeighbors();
  testLives();

  if (fails > 0) {
    printf("Failed: %i\n", fails);
    exit(1);
  }
}
