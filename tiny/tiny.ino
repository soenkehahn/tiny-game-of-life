
#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <time.h>

#include "world.h"

TinyScreen display = TinyScreen(TinyScreenPlus);

world* w = newWorld(40, 30);

void setup(void) {
  Wire.begin(); //initialize I2C before we can initialize TinyScreen- not needed for TinyScreen+
  display.begin();
  display.setBrightness(10);
  srand(time(0));
  traverse(w, [] (world* w, int x, int y) {
    setCell(w, x, y, rand() % 2);
  });
}

void drawCell(world* w, int x, int y) {
  if (getCell(w, x, y)) {
    display.drawPixel(x, y, TS_8b_White);
  } else {
    display.drawPixel(x, y, TS_8b_Black);
  }
}

void loop() {
  traverse(w, drawCell);
  delay(1000);
}
