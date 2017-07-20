
int p1_width = 4;
int p2_width = 4;

int p1_pos = 0;
int p2_pos = 0;

int ballX = 5;
int ballY = 5;

int ballX_velocity = 1;
int ballY_velocity = -1;

int life_count = 5;
int pong_score = 0;

void movePaddles() {
    if (gamer.isHeld(LEFT) && p1_pos > 0) {
        p1_pos--;
    }
    else if (gamer.isHeld(DOWN) && p1_pos < (8 - p1_width)) {
        p1_pos++;
    }
    if (gamer.isHeld(UP) && p2_pos > 0) {
        p2_pos--;
    }
    else if (gamer.isHeld(RIGHT) && p2_pos < (8 - p2_width)) {
        p2_pos++;
    }
}

void moveBall() {
    // move ball in the x direction
    ballX += ballX_velocity;
    // move ball in the y direction
    ballY += ballY_velocity;

    // if ball on edge of wall, reverse its direction
    if (ballX == -1) {
        ballX = 0;
        ballX_velocity = 1;
    } else if (ballX == 8) {
        ballX = 7;
        ballX_velocity = -1;
    }

    // if ball hits a paddle, reverse its direction
    if (ballY == 0) {
        if ((p2_pos <= ballX) && (ballX <= p2_pos + p2_width)) {
            ballY = 1;
            ballY_velocity = 1;
            score++;
            gamer.playTone(wallNote);
        }
        else {
            reset();
        }
    } else if (ballY == 7) {
        if ((p1_pos <= ballX) && (ballX <= p1_pos + p1_width)) {
            ballY = 6;
            ballY_velocity = -1;
            score++;
            gamer.playTone(wallNote);
        }
        else {
            reset();
        }
    }
    gamer.stopTone();
}

void drawPaddles() {
    for (int i = 0; i < p1_width; i++) {
        if (p1_pos + i < 8) {
            gamer.display[p1_pos + i][7] = HIGH;
        }
    }

    for (int i = 0; i < p2_width; i++) {
        if (p2_pos + i < 8) {
            gamer.display[p2_pos + i][0] = HIGH;
        }
    }
}

void drawBall() {
    gamer.display[ballX][ballY] = HIGH;
}

void reset() {
    if (life_count-- == 0) {
        PongOver();
    } else {
        ballX = random(3, 6);
        ballY = random(4, 6);

        int r = random(2);
        if (r == 0) {
            r = -1;
        }
        ballX_velocity = r;

        r = random(2);
        if (r == 0) {
            r = -1;
        }
        ballY_velocity = r;
    }
}

// increase the speed of the game for every 10 hits
void checkScore() {
    if (score > 5) {
        pongSpeed -= 10;
        score = 0;
        for(int i=0; i<gameStartSongLength; i++) {
            gamer.playTone(gameStartNotes[i]);
            delay(25);
        }
        gamer.stopTone();
        pong_score += 5;
    }
}

void PongOver() {
  // Play the Game Over tune.
  for(int i=0; i<gameOverSongLength; i++) {
    gamer.playTone(gameOverNotes[i]);
    delay(100);
  }
  // Turn off sound.
  gamer.stopTone();
  gamer.printString("Game over");
  delay(100);
  gamer.printString("Score");
  delay(500);
  gamer.showScore(pong_score);
  delay(100);
  isPlaying = false;
}
