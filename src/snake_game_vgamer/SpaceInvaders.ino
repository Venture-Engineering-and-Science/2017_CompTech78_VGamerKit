

bool game_over = false;

void SI_add_asteroids() {
  static byte n_ticks = 0;
  static byte level = 0;

  // asteroid reaches wing level, therefore you can't shoot it
  if (asteroid_field[7] > 0) {
    game_over = true;
    return;
  }
  
  if (n_ticks++ > 25) {
    n_ticks = 0;
    level++;

    if (level > 5) {
      level = 0;
      spaceInvadersSpeed -= 10;
      for (int i = 0; i < gameStartSongLength; i++) {
        gamer.playTone(gameStartNotes[i]);
        delay(25);
      }
    } else {
      gamer.stopTone();
    }

    asteroid_field[0] = random(255); // backwards MSB <-> LSB

    for (int i = 7; i > 0; i--) {
      asteroid_field[i] = asteroid_field[i - 1];
    }
  }
}

void SI_check_collision() {
  if (CHECK_BIT(asteroid_field[missile_y], missile_x)) {
    //((asteroid_field[missile_y] & (1 << missile_x)) >> missile_x) == 1) {
    asteroid_field[missile_y] &= ~(1 << missile_x);
    SI_gun_active = true;
    SI_score++;
    gamer.playTone(250);
  } else {
    gamer.stopTone();
  }
}

void SI_draw_asteroids() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (CHECK_BIT(asteroid_field[row], col)) {
        gamer.display[col][row] = 1;
      }
    }
  }
}

void SI_draw_player() {
  gamer.display[SI_player_position][6] = 1;
  gamer.display[(SI_player_position - 1) < 0 ? 0 : SI_player_position - 1][7] = 1;
  gamer.display[SI_player_position][7] = 1;
  gamer.display[(SI_player_position + 1) > 7 ? 7 : SI_player_position + 1][7] = 1;
}

void SI_update_player_position() {
  if (gamer.isPressed(UP)) {
    if (SI_gun_active == true) {
      SI_shoot();
    }
  }
  else if (gamer.isPressed(LEFT)) {
    SI_player_position--;
    SI_player_position = (SI_player_position < 0) ? 0 : SI_player_position;
  }
  else if (gamer.isPressed(RIGHT)) {
    SI_player_position++;
    SI_player_position = (SI_player_position > 7) ? 7 : SI_player_position;
  }
}

void SI_draw_missiles() {
  if (SI_gun_active == false) {
    gamer.display[missile_x][missile_y] = 1;
  }
}

void SI_update_missiles() {
  if (SI_gun_active == false) {
    if (--missile_y == -1) {
      missile_y = 7;
      SI_gun_active = true;
    }
  }
}

void SI_shoot() {
  SI_gun_active = false;
  missile_x = SI_player_position;
  missile_y = 6;
}

void SI_check_game_over() {
  if (CHECK_BIT(asteroid_field[6], SI_player_position)) { // asteroid hits top pod
    game_over = true;
  }
  // asteroid hits left wing
  if (CHECK_BIT(asteroid_field[7], (SI_player_position - 1) < 0 ? 0 : SI_player_position - 1)) {
    game_over = true;
  }
  // asteroid hits right wing
  if (CHECK_BIT(asteroid_field[7], (SI_player_position + 1) > 7 ? 7 : SI_player_position + 1)) {
    game_over = true;
  }

  if (game_over) {
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
    gamer.showScore(SI_score);
    delay(2000);
    isPlaying = false;
  }
}

