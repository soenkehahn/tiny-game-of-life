
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "world.h"

using namespace std;

#include <iostream>

bool fails = false;

void assertEquals(int a, int b) {
  if (a != b) {
    printf("FAILURE: not equal: %i != %i\n", a, b);
    fails = true;
  }
}

void assertEqualStrings(char* a, char* b) {
  if (strcmp(a, b)) {
    printf("FAILURE: not equal: %s != %s\n", a, b);
    fails = true;
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

int main() {
  testInit();
  testSetCell();
  testLoop();
  testTraverse();

  if (fails) {
    printf("Failed!\n");
    exit(1);
  }
}
