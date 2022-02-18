#include "src/utils/Arduboy2Ext.h"
#include "src/images/Images.h"
#include "src/utils/Enums.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void drawSplash_Loop() {

  uint8_t counter = 0;

  while (gameState == GameState::SplashScreen) {

    if (!(arduboy.nextFrame())) { delay(5); };
    arduboy.pollButtons();
      
    auto justPressed = arduboy.justPressedButtons();
      

    if (justPressed > 0 && counter > 0) {

      counter = 124;

    }

    if (justPressed > 0 && counter == 0) {

  #ifdef SOUNDS    
      sound.tone(NOTE_A2, 30);
      sound.tone(NOTE_F1, 30);
  #endif

      counter = 1;

    }

    if (counter > 0) {

      if (arduboy.everyXFrames(2)) {
        counter++;
        if (counter == 125) gameState = GameState::TitleScreen; 
      }

    }


    // -------------------------------------------------------------------------------------------------------------

    Sprites::drawOverwrite(32, 17, Images::PPOT, 0);

    uint8_t y = 17; // Default pixel position 1 is hidden in the top line of the image
    switch (arduboy.getFrameCount(48)) {

        case 12 ... 23:
            y = 30; // Move pixel down to position 2
            /*-fallthrough*/
        case 0 ... 11:
            Sprites::drawOverwrite(91, 25, Images::PPOT_Arrow, 0); // Flash 'Play' arrow
            break;

        case 24 ... 35:
            y = 31; // Move pixel down to position 3
            break;

        default: // 36 ... 47:
            y = 32; // Move pixel down to position 4
            break;

    }

    arduboy.drawPixel(52, y, WHITE); // Falling pixel represents the tape spooling
    if (y % 2 == 0) { // On even steps of pixel movement, update the spindle image
        Sprites::drawOverwrite(45, 28, Images::PPOT_Spindle, 0);
    }

    arduboy.display(true);

  }

}
