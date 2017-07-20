#include "Arduino.h"

void updateBird() {
  /* 
   If the UP button is pressed, move the bird up. Otherwise, 
   move it down with gravity. Remember, the X axis' 0 is on the top
   of the screen. Therefore, when we move the bird up, we REDUCE birdY. 
   When gravity brings it down, away from the axis' origin, 
   we INCREASE birdY.
   */
  if(gamer.isPressed(UP)) {
    birdY--;
  }
  else {
    birdY = birdY + gravity;
  }

  // Detect if the bird is on the floor.
  if(birdY == 7) FlappyOver();
}

/* ---------------------------------------------------------------
 Draws the bird. Wherever it might be!
 */
void drawBird() {
  // Make sure the bird isn't off the screen.
  birdY = constrain(birdY, 0, 7);
  // Display the bird dot.
  gamer.display[birdX][birdY] = 1;
}

/* ---------------------------------------------------------------
 Moves the walls from right to left on the screen, with a constant
 speed. 
 */
void moveWall() {
  // If the wall is at the end of the screen, get a new wall going!
  if(currentWallPosition == 0 - wallThickness) {
    generateWall();
  }
  // Otherwise, move the wall. 
  else {
    currentWallPosition--;
  }
}

/* ---------------------------------------------------------------
 Places a new wall on the edge of the screen, ready to be moved.
 */
void generateWall() {
  // Set the wall to the right of the screen.
  currentWallPosition = 8;
  // Get a random gap in the wall.
  gapPosition = random(1, 7-gapSize);
}

/* ---------------------------------------------------------------
 Draws the walls at their current position
 */
void drawWall() {
  // Draw multiple walls, if we need to.
  for(int j=0; j<wallThickness; j++) {
    if(currentWallPosition+j >= 0 && currentWallPosition+j <= 7) {
      for(int i=0; i<8; i++) {
        // Draw the wall, but miss out the gap. 
        if(i > gapPosition + gapSize - 1 || i < gapPosition) {
          gamer.display[currentWallPosition+j][i] = 1;
        }
      }
    }
  }
}

/* ---------------------------------------------------------------
 Checks if the bird is on a wall. If there's a pixel on the 
 same position as the bird, it's game over!
 */
void FBdetectCollision() {
  if(gamer.display[birdX][birdY] == 1) {
    FlappyOver();
  }
}

/* ---------------------------------------------------------------
 Keeps track of the score. If the bird is flying through a wall, 
 add one to the score, and make a sound!
 */
void recordScore() {
  if(birdX == currentWallPosition + wallThickness) {
    score++;
    gamer.playTone(wallNote);
  }
  else gamer.stopTone();
}

/* ---------------------------------------------------------------
 Shows Game over, followed by the score. 
 */
void FlappyOver() {
  
  // Play the Game Over tune.
  for(int i=0; i<gameOverSongLength; i++) {
    gamer.playTone(gameOverNotes[i]);
    delay(100);
  }
  
  // Turn off sound.
  gamer.stopTone();
  
  // Display Game Over followed by the score.
  gamer.printString("Game over");
  delay(100);
  gamer.printString("Score");
  delay(500);
  gamer.showScore(score);
  delay(500);
  isPlaying = false;
}


