#define ROUNDS_TO_WIN 15
#define CHOICE_LEFT  (1 << 0)
#define CHOICE_DOWN  (1 << 1)
#define CHOICE_UP (1 << 2)
#define CHOICE_RIGHT (1 << 3)
#define CHOICE_NONE (0)

#define ENTRY_TIME_LIMIT 3000

byte UP_ARROW[8] = {
    B00000000,
    B00011000,
    B00111100,
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00000000};

byte DOWN_ARROW[8] = {
    B00000000,
    B00011000,
    B00011000,
    B00011000,
    B01111110,
    B00111100,
    B00011000,
    B00000000};

byte LEFT_ARROW[8] = {
    B00000000,
    B00010000,
    B00110000,
    B01111110,
    B01111110,
    B00110000,
    B00010000,
    B00000000};

byte RIGHT_ARROW[8] = {
    B00000000,
    B00001000,
    B00001100,
    B01111110,
    B01111110,
    B00001100,
    B00001000,
    B00000000};

void play_memory(void) {
    while (gameRound < ROUNDS_TO_WIN) {
        add_to_moves();
        playMoves();

        for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
        {
            byte choice = wait_for_button(); // See what button the user presses

            // If wait timed out, player loses*/
            // If the choice is incorect, player loses
            if ((choice != gameBoard[currentMove]) || (choice == CHOICE_NONE)) {
                Simon_game_over();
                return;
            }
        }

        gamer.updateDisplay();
        delay(1000); // Player was correct, delay before playing moves
    }

    Simon_win_game();
}

void add_to_moves(void)
{
    byte newButton = random(0, 4); //min (included), max (excluded)

    // We have to convert this number, 0 to 3, to CHOICEs
    if (newButton == 0) newButton = CHOICE_LEFT;
    else if (newButton == 1) newButton = CHOICE_RIGHT;
    else if (newButton == 2) newButton = CHOICE_UP;
    else if (newButton == 3) newButton = CHOICE_DOWN;

    gameBoard[gameRound++] = newButton; // Add this new button to the game array
}

void playMoves(void)
{
    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
        showMove(gameBoard[currentMove]);

        // Wait some amount of time between button playback
        // Shorten this to make game harder
        delay(300); // 150 works well. 75 gets fast.
    }
}

void showMove(byte which)
{
    //Play the sound associated with the given LED
    switch (which)
    {
        case CHOICE_LEFT:
            gamer.printImage(LEFT_ARROW);
            gamer.playTone(150);
            break;
        case CHOICE_RIGHT:
            gamer.printImage(RIGHT_ARROW);
            gamer.playTone(175);
            break;
        case CHOICE_UP:
            gamer.printImage(UP_ARROW);
            gamer.playTone(200);
            break;
        case CHOICE_DOWN:
            gamer.printImage(DOWN_ARROW);
            gamer.playTone(225);
            break;
    }

    delay(100);
    gamer.stopTone();
}

byte wait_for_button(void) {
    long startTime = millis(); // Remember the time we started the this loop

    while ( (millis() - startTime) < ENTRY_TIME_LIMIT) // Loop until too much time has passed
    {
        byte button = checkButton();

        if (button != CHOICE_NONE) {
            showMove(button); // Play the button the user just pressed

            while(checkButton() != CHOICE_NONE) ;  // Now let's wait for user to release button

            delay(10); // This helps with debouncing and accidental double taps

            return button;
        }

    }

    return CHOICE_NONE; // If we get here, we've timed out!
}

byte checkButton(void) {
    if (gamer.isPressed(DOWN))       return(CHOICE_DOWN);
    else if (gamer.isPressed(UP))    return(CHOICE_UP);
    else if (gamer.isPressed(LEFT))  return(CHOICE_LEFT);
    else if (gamer.isPressed(RIGHT)) return(CHOICE_RIGHT);

    return(CHOICE_NONE); // If no button is pressed, return none
}


void Simon_game_over() {
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
  gamer.showScore(gameRound - 1);
  delay(2000);
  isPlaying = false;
}

void Simon_win_game() {
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
