
#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <time.h>

#include "world.h"

TinyScreen display = TinyScreen(TinyScreenPlus);

simulation* sim;

void setup(void) {
  Wire.begin(); //initialize I2C before we can initialize TinyScreen- not needed for TinyScreen+
  display.begin();
  display.setBrightness(10);

  world* w = newWorld(96, 64);
  traverse(w, [] (world* w, int x, int y) {
    setCell(w, x, y, rand() % 2);
  });
  sim = newSimulation(w);
}

void drawCell(world* w, int x, int y) {
  if (getCell(w, x, y)) {
    display.drawPixel(x, y, TS_8b_Green);
  } else {
    display.drawPixel(x, y, TS_8b_DarkBlue);
  }
}

void loop() {
  traverse(sim->current, drawCell);
  stepSimulation(sim);
}
