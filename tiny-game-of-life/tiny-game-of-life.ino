
#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <time.h>

#include "world.h"

TinyScreen display = TinyScreen(TinyScreenPlus);

doubleBufferedGrid* sim;

void setup(void) {
  Wire.begin(); //initialize I2C before we can initialize TinyScreen- not needed for TinyScreen+
  display.begin();
  display.setBrightness(10);
  display.drawRect(0, 0, 95, 64, TSRectangleFilled, TS_8b_DarkBlue);

  grid* w = newWorld(96, 64);
  traverse(w, [] (grid* w, int x, int y) {
    setCell(w, x, y, rand() % 2);
  });
  sim = newSimulation(w);
}

void drawCell(grid* w, int x, int y) {
  bool currentCell = getCell(w, x, y);
  if (currentCell != getCell(sim->old, x, y)) {
    if (currentCell) {
      display.drawPixel(x, y, TS_8b_Green);
    } else {
      display.drawPixel(x, y, TS_8b_DarkBlue);
    }
  }
}

void loop() {
  traverse(sim->current, drawCell);
  stepSimulation(sim);
}
