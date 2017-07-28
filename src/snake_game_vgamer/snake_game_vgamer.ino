#include <Gamer.h>

#define CHECK_BIT(X, Y) (((X) >> (Y)) & 1 == 1)


typedef enum gamemode_t {
    NAME, PONG, FLAPPY, SNAKE, SPACE_INVADERS, SIMON, BREAKOUT
} gamemode_t;

gamemode_t game_modes[] = {
    NAME, PONG, FLAPPY, SNAKE, SPACE_INVADERS, SIMON, BREAKOUT
};

Gamer gamer;

int isPlaying;
byte game_pos = 0;

// Tweaking variables
int snakeGrowthFactor = 2;
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

//Simon Says data
int gameRound;
byte gameBoard[15];

// Wall - related
int wallThickness = 4;
int gapSize = 3;
int currentWallPosition;
int gapPosition;

// Bird - related
int flyingSpeed = 120;
int birdX = 2;
int birdY;
int gravity = 1;

// Space Invaders
int SI_player_position = 3;
bool SI_gun_active = true;
byte SI_score = 0;
int missile_x;
int missile_y;
byte asteroid_field[8] = {0};

// Breakout
byte BO_bricks[8];
int BO_speed = 160;

// game music
int gameStartSongLength = 3;
int gameStartNotes[] = {160, 140, 120};
int gameOverSongLength = 4;
int gameOverNotes[] = {120, 140, 160, 190};
int wallNote = 200;

int pongSpeed = 120;
int spaceInvadersSpeed = 120;

int music[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};

int GAME_MODE = NAME;

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
                SI_add_asteroids();
                SI_update_missiles();
                SI_update_player_position();
                SI_check_collision();
                SI_draw_player();
                SI_draw_missiles();
                SI_draw_asteroids();
                SI_check_game_over();
                gamer.updateDisplay();
                delay(spaceInvadersSpeed);
                break;
            case SIMON:
                gamer.clear();
                play_memory();
                // play_memory has its own game loop
                break;
            case BREAKOUT:
                gamer.clear();
                BO_movePaddle();
                BO_moveBall();
                BO_check_hit();
                BO_drawPaddle();
                BO_drawBall();
                BO_draw_bricks();
                BO_checkScore();
                BO_check_win();
                gamer.updateDisplay();
                delay(BO_speed);
                break;
        }
    }
    else {
        /* draw a logo for each game  */
        showScreen(GAME_MODE);

        /* pressing a buton changes the game to a different one, and updates the logo*/
        if (gamer.isPressed(LEFT)) {
            game_pos = (((game_pos - 1) < 0) ? 6 : game_pos - 1);
            GAME_MODE = game_modes[game_pos];

            gamer.playTone(wallNote);
            delay(50);
        }
        else if (gamer.isPressed(RIGHT)) {
            game_pos = (((game_pos + 1) > 6 ) ? 0 : game_pos + 1);
            GAME_MODE = game_modes[game_pos];
            gamer.playTone(wallNote);
            delay(50);
        }
        else {
            gamer.stopTone();
        }

        /* pressing START runs the game */
        if (gamer.isPressed(START)) {
            for (int i = 0; i < gameStartSongLength; i++) {
                gamer.playTone(gameStartNotes[i]);
                delay(100);
            }
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
                    gameRound = 0;
                    break;
                case SPACE_INVADERS:
                    SI_player_position = 3;
                    SI_gun_active = true;
                    SI_score = 0;
                    missile_x = 0;
                    missile_y = 0;
                    for (int i = 0; i < 8; i++) {
                        asteroid_field[i] = 0;
                    }
                    break;
                case BREAKOUT:
                    BO_init();
                    break;
                case NAME:
                    break;
            }
        }
    }
}

