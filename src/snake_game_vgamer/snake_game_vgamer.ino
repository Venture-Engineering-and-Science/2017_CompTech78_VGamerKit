#include <Gamer.h>

typedef enum gamemode_t {
  NAME, PONG, FLAPPY, SNAKE, SPACE_INVADERS, SIMON
} gamemode_t;

Gamer gamer;

int isPlaying;

// Tweaking variables
int snakeGrowthFactor = 1;
boolean passThroughWalls = true;
int snakeSpeed = 100;

/* These two arrays store the snake's X/Y coordinates!
   Our snake has a maximum length of 64. If it were any
   bigger, it wouldn't fit in our screen! */
int snakeX[64];
int snakeY[64];
int snakeDirection;

// Stores the snake's length. This is also the score!
int snakeLength, score;

int appleX;
int appleY;

// Snake data

// Wall - related
int wallThickness = 4;
int gapSize = 3;
int currentWallPosition;
int gapPosition;

// Bird - related
int flyingSpeed = 80;
int birdX = 2;
int birdY;
int gravity = 1;

// game music
int gameStartSongLength = 3;
int gameStartNotes[] = {160, 140, 120};
int gameOverSongLength = 4;
int gameOverNotes[] = {120, 140, 160, 190};
int wallNote = 200;

int pongSpeed = 120;
int spaceInvadersSpeed = 100;


int music[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};

int GAME_MODE = SPACE_INVADERS;

void setup() {
  gamer.begin();
  randomSeed(gamer.ldrValue());
  PORTB |= (1 << 5);
}

void loop() {
  if (isPlaying) {
    switch (GAME_MODE) {
      case SNAKE:
        gamer.clear();
        updateApple();
        drawApple();
        updateDirection();
        moveSnake();
        SdetectCollision();
        drawSnake();
        gamer.updateDisplay();
        delay(snakeSpeed);
        break;
      case FLAPPY:
        gamer.clear();
        moveWall();
        drawWall();
        updateBird();
        FBdetectCollision();
        recordScore();
        drawBird();
        gamer.updateDisplay();
        delay(flyingSpeed);
        break;
      case NAME:
        gamer.clear();
        gamer.printString("Venture VGamerKit");
        delay(500);
        isPlaying = false;
        break;
      case PONG:
        gamer.clear();
        movePaddles();
        moveBall();
        drawPaddles();
        drawBall();
        checkScore();
        gamer.updateDisplay();
        delay(pongSpeed);
        break;
      case SPACE_INVADERS:
        gamer.clear();
        SI_update_missiles();
        SI_update_player_position();
        SI_draw_player();
        SI_draw_missiles();
        gamer.updateDisplay();
        delay(spaceInvadersSpeed);
        break;
      case SIMON:
//        gamer.clear();
//        gamer.updateDisplay();
//        add_to_moves(); // Add a button to the current moves, then play them back
//        playMoves(); // Play back the current game board
//        // Then require the player to repeat the sequence.
//        for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
//        {
//          byte choice = wait_for_button(); // See what button the user presses
//
//          if (choice == 0) return false; // If wait timed out, player loses
//
//          if (choice != gameBoard[currentMove]) return false; // If the choice is incorect, player loses
//        }
//
//        delay(100);
        break;
    }
  }
  else {

    /* draw a logo for each game  */
    showScreen(GAME_MODE);

    /* pressing a buton changes the game to a different one, and updates the logo*/
    if (gamer.isPressed(UP)) {
      GAME_MODE = SNAKE;
      gamer.playTone(wallNote);
      delay(50);
    }
    else if (gamer.isPressed(LEFT)) {
      GAME_MODE = FLAPPY;
      gamer.playTone(wallNote);
      delay(50);
    }
    else if (gamer.isPressed(DOWN)) {
      if (GAME_MODE == NAME) {
        GAME_MODE = SPACE_INVADERS;
      } else {
        GAME_MODE = NAME;
      }
      gamer.playTone(wallNote);
      delay(50);
    }
    else if (gamer.isPressed(RIGHT)) {
      GAME_MODE = PONG;
      gamer.playTone(wallNote);
      delay(50);
    }
    else {
      gamer.stopTone();
    }

    /* pressing START runs the game */
    if (gamer.isPressed(START)) {

      // Play a tune before the game starts.
      for (int i = 0; i < gameStartSongLength; i++) {
        gamer.playTone(gameStartNotes[i]);
        delay(100);
      }

      // Stop the sound!
      gamer.stopTone();

      isPlaying = true;

      switch (GAME_MODE) {
        case FLAPPY:
          generateWall();
          birdY = 2;
          score = 0;
          break;
        case SNAKE:
          snakeDirection = DOWN;
          snakeLength = 1;
          snakeX[0] = 0;
          snakeY[0] = 0;
          generateApple();
          break;
        case PONG:
          score = 0;
          break;
        case SIMON:
        case SPACE_INVADERS:
          break;
        case NAME:
          break;
      }
    }
  }
}

