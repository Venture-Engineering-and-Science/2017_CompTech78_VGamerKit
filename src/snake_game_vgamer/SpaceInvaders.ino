
int SI_player_position = 3;
bool SI_gun_active = true;
bool SI_charged = true;

int missile_x[6];
int missile_y[6];
int n_missiles = 5;

void SI_draw_player() {
  for (int i = 0; i < n_missiles; i++) {
    gamer.display[0][i] = 1;
  }

  gamer.display[SI_player_position][6] = 1;
  gamer.display[(SI_player_position - 1) < 0 ? 0 : SI_player_position - 1][7] = 1;
  gamer.display[SI_player_position][7] = 1;
  gamer.display[(SI_player_position + 1) > 7 ? 7 : SI_player_position + 1][7] = 1;
}

void SI_update_player_position() {
  if (gamer.isPressed(UP)) {
    if (n_missiles) {
      SI_shoot();
      //gamer.playTone(400);
    }
    //delay(50);
  }
  else if (gamer.isPressed(DOWN)) {
    if (SI_charged) {
      //SI_bomb();
      //SI_charged = false;
      //gamer.playTone(60);
      //delay(50);
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
  else {
    gamer.stopTone();
  }
}

void SI_draw_missiles() {
  for (int i = 0; i < 6; i++) {
    if (missile_x[i] == -1) continue;
    gamer.display[missile_x[i]][missile_y[i]] = 1;
  }
}

void SI_update_missiles() {
  for (int i = 0; i < 6; i++) {
    if (missile_x[i] == -1) {
      continue;
    }
    missile_y[i]--;
    if (missile_y[i] < 0) {
      missile_x[i] = -1;
      n_missiles++;
    }
  }

  if (n_missiles > 1) {
    SI_gun_active = true;
  }
}

void SI_shoot() {
  if (n_missiles) {
    missile_x[n_missiles] = SI_player_position;
    missile_y[n_missiles] = 6;
    n_missiles--;
  }
}

void SI_bomb() {
}

