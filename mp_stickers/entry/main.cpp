#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image waldo;  waldo.readFromFile("../waldo.png");
  Image notWaldo; notWaldo.readFromFile("../notWaldo.png");
  Image background; background.readFromFile("../background.png");
  Image alma; alma.readFromFile("../alma.png");

  StickerSheet sheet(alma, 6);
  sheet.addSticker(notWaldo, 50, 700);
  sheet.addSticker(notWaldo, 900, 400);
  sheet.addSticker(notWaldo, 600, 100);
  sheet.addSticker(notWaldo, 100, 100);
  sheet.addSticker(notWaldo, 50, 300);
  sheet.addSticker(waldo, 500, 600);
  sheet.render().writeToFile("../myImage.png");
  return 0;
}
