#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
const uint8_t left = 5, right = 4; // Buttons
uint8_t ballx, bally; // Current location of the ball
uint8_t vaus = 3; // (The thing that we move) Vause's left pixel location
uint8_t board [][8] = {{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},
                       {1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},
                       {0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0}
                      };

void setup() {
 matrix.begin(0x70);
 pinMode(right, INPUT);
 digitalWrite(right, HIGH);
 pinMode(left, INPUT);
 digitalWrite(left, HIGH);
}
/* Paints the bricks in the display*/
void paintBricks() {
  for(uint8_t i = 0; i<8; i++) {
    for(uint8_t j = 0; j<8; j++){
      if(board[i][j] == 1){
        if(i % 2 == 0)
          matrix.drawPixel(j,i,LED_GREEN); // Consider: hits to break block depending on the colour
        else
          matrix.drawPixel(j,i,LED_YELLOW);
      }
    }
  }
}
/* Paints Vaus in the display*/
void paintVaus() {
  matrix.drawPixel(vaus, 7, LED_RED);
  matrix.drawPixel(vaus + 1,7, LED_RED);
}

void loop() {
   matrix.clear();
   paintBricks();
   paintVaus();
   matrix.writeDisplay();
   if(!digitalRead(left)){
     if(vaus >0)
       vaus--; 
   }
   if(!digitalRead(right)){
     if(vaus + 1 < 7)
       vaus++;
   }
   delay(70);
}

