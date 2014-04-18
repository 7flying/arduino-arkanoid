#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
const uint8_t left = 5, right = 4; // Buttons
uint8_t ballx = 3, bally = 6; // Current location of the ball
int speedx = -1, speedy = -1; // Ball's speed & direction
uint8_t vaus = 3; // (The thing that we move) Vause's left pixel location
uint8_t board [][8] = {{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1}, // Board 1:brick, 0: no brick
                       {1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}
                      };
uint8_t numBricks = 24; // count of bricks
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
/* Paints the ball in the display*/
void paintBall() {
 matrix.drawPixel(ballx, bally, LED_RED); 
}
/* Checks the collisions*/
void checkCollisions() {
  if(numBricks > 0) {
    // Bottom 
    if(bally == 7) {
      // Check if Vaus is here
      if(ballx == vaus || ballx == vaus + 1) {
        speedy = -1;
	if(ballx == vaus)
	  speedx = -1;
	else speedx = 1;
      } else gameOver();
    }
    // Top
    if(bally == 0){
      if(board[bally][ballx]) {
	board[bally][ballx] = 0;
	numBricks--;
      }
      speedy = 1;
    }
    // Side walls
    if( ballx == 0 || ballx == 7){
      if(board[bally][ballx]) {
        board[bally][ballx] = 0;
	numBricks--;
	speedy = 1;
      }
      speedx = -speedx;
    }
    // Everything else
    if(ballx != 0 && ballx != 7 && bally != 0 && bally != 7){
      if(board[bally][ballx]) {
        board[bally][ballx] = 0;
        numBricks--;
        speedy = 1;
      }
    }
    ballx += speedx;
    bally += speedy;
  } else win();
}
void gameOver() {
  // TODO
}
void win() {
  // TODO
}
void loop() {
   matrix.clear();
   paintBricks();
   paintVaus();
   paintBall();
   matrix.writeDisplay();
   if(!digitalRead(left)){
     if(vaus > 0)
       vaus--; 
   }
   if(!digitalRead(right)){
     if(vaus + 1 < 7)
       vaus++;
   }
   checkCollisions();
   delay(150); 
}

