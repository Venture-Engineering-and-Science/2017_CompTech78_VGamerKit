
byte block_length;
byte block_pos;
byte last_block_pos;
byte level;
boolean direction;

void ST_init() {
    level = 0;
    block_pos = 0;
    last_block_pos = 0;
    block_length = 6;
}

void ST_draw_block() {
    if (level < 7) {
        for (byte i = 0; i < block_length; i++) {
            gamer.display[block_pos + i][7 - level] = 1;
        }
    } else {
        for (byte i = 0; i < block_length; i++) {
            gamer.display[block_pos + i][level] = 1;
        }
    }
}

void ST_move_block() {
    // move right until hit wall
    if (direction) {
        if (block_pos + block_length <= 7) {
            block_pos++;
            return;
        } else {
            direction = false;
            return;
        }
    }
    // if hit wall, move left
    else {
        if (block_pos > 0) {
            block_pos--;
            return;
        } else {
            direction = true;
            return;
        }
    }
}

void ST_get_keypress() {
    if (gamer.isPressed(UP)) {
        // equal
        if (block_pos == last_block_pos) {
            level++;
        }

        // less than

        // greater than


        gamer.playTone(160);
        delay(100);
    } else {
        gamer.stopTone();
    }
}

