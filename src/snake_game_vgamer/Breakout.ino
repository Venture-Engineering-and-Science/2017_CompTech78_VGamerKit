
int BO_paddle_width;
int BO_paddle_pos;

int BO_ballX;
int BO_ballY;

int BO_ballX_velocity;
int BO_ballY_velocity;

int BO_score;
int BO_level;

byte hits = 0;

int k;

void BO_init() {
    BO_speed = 160;
    BO_paddle_width = 5;
    BO_paddle_pos = 2;
    BO_ballX = 3;
    BO_ballY = 6;

    BO_ballX_velocity = 1;
    BO_ballY_velocity = -1;

    BO_score = 0;
    BO_level = 2;
    hits = 0;
    for (int i = 0; i < BO_level; i++) {
        BO_bricks[i] = 0xFF;
    }
    for (int i = BO_level; i < 5; i++) {
        BO_bricks[i] = 0;
    }
}

void BO_draw_bricks() {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 8; col++) {
            if (CHECK_BIT(BO_bricks[row], col)) {
                gamer.display[col][row] = 1;
            }
        }
    }
}

void BO_check_hit() {
    // check brick hit
    if (CHECK_BIT(BO_bricks[BO_ballY], BO_ballX)) {
        BO_bricks[BO_ballY] &= ~(1 << BO_ballX);

        if (BO_ballX_velocity == -1) {
            k = random(100);
            if (k > 50) {
                BO_ballX_velocity = 1;
            }
        } else if (BO_ballX_velocity == 1) {
            k = random(100);
            if (k > 50) {
                BO_ballX_velocity = -1;
            }
        }

        if (BO_ballY_velocity == -1) {
            BO_ballY_velocity = 1;
        } else if (BO_ballY_velocity == 1) {
            BO_ballY_velocity = -1;
        }
        gamer.playTone(250);
    } else {
        gamer.stopTone();

    }
}

void BO_check_win() {
    byte sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += BO_bricks[i];
    }

    if (sum == 0) {
        if (++BO_level == 6) {
            BO_GameWin();
            return;
        }

        // level up, reset positions, set paddle width smaller, row advance by one
        for (int i = 0; i < BO_level; i++) {
            BO_bricks[i] = 0xFF;
        }
        for (int i = BO_level; i < 5; i++) {
            BO_bricks[i] = 0;
        }

        BO_paddle_width--;
        BO_paddle_pos = 3;
        BO_ballX = 3;
        BO_ballY = 7;
        BO_ballY_velocity = -1;

        for (int i = 0; i < gameStartSongLength; i++) {
            gamer.playTone(gameStartNotes[i]);
            delay(100);
        }

        gamer.stopTone();
    }
}

void BO_movePaddle() {
    if (gamer.isHeld(LEFT) && BO_paddle_pos > 0) {
        BO_paddle_pos--;
    }
    else if (gamer.isHeld(RIGHT) && BO_paddle_pos < (8 - BO_paddle_width)) {
        BO_paddle_pos++;
    }
}

void BO_moveBall() {
    // move ball in the x direction
    BO_ballX += BO_ballX_velocity;
    // move ball in the y direction
    BO_ballY += BO_ballY_velocity;

    // if ball on edge of wall, reverse its direction
    if (BO_ballX == -1) {
        BO_ballX = 0;
        BO_ballX_velocity = 1;
    } else if (BO_ballX == 8) {
        BO_ballX = 7;
        BO_ballX_velocity = -1;
    }

    // if ball top of screen
    if (BO_ballY == -1) {
        BO_ballY = 0;
        BO_ballY_velocity = 1;
        gamer.playTone(wallNote);
    } // hits a paddle, reverse its direction
    else if ((BO_ballY == 7) &&
            (BO_paddle_pos < BO_ballX) &&
            (BO_ballX < (BO_paddle_pos + BO_paddle_width))) {
        hits++;
        BO_ballY = 6;
        BO_ballY_velocity = -1;
        gamer.playTone(wallNote);
    }
    if (BO_ballY == 8) {
        BO_GameOver();
    }
    gamer.stopTone();
}

void BO_drawPaddle() {
    for (int i = 0; i < BO_paddle_width; i++) {
        if (BO_paddle_pos + i < 8) {
            gamer.display[BO_paddle_pos + i][7] = HIGH;
        }
    }
}

void BO_drawBall() {
    gamer.display[BO_ballX][BO_ballY] = HIGH;
}

// increase the speed of the game for every 10 hits
void BO_checkScore() {
    if (hits > 8) {
        BO_score++;
        hits = 0;
        BO_speed -= 5;
        for (int i = 0; i < gameStartSongLength; i++) {
            gamer.playTone(gameStartNotes[i]);
            delay(25);
        }
        gamer.stopTone();
    }
}

void BO_GameOver() {
    // Play the Game Over tune.
    for (int i = 0; i < gameOverSongLength; i++) {
        gamer.playTone(gameOverNotes[i]);
        delay(100);
    }
    // Turn off sound.
    gamer.stopTone();
    gamer.printString("Game over");
    delay(100);
    gamer.printString("Score");
    delay(500);
    gamer.showScore(BO_score);
    delay(2000);
    isPlaying = false;
}

void BO_GameWin() {
    gamer.playTone(130);
    delay(100);
    gamer.playTone(150);
    delay(150);
    gamer.playTone(125);
    delay(200);
    gamer.stopTone();

    gamer.printString("You win");
    delay(2000);
    isPlaying = false;
}
