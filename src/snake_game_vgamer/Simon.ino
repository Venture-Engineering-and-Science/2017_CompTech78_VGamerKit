#define ROUNDS_TO_WIN 15
#define CHOICE_LEFT  (1 << 0)
#define CHOICE_DOWN  (1 << 1)
#define CHOICE_UP (1 << 2)
#define CHOICE_RIGHT (1 << 3)
#define CHOICE_NONE (1 << 4)

#define ENTRY_TIME_LIMIT 3000

int gameRound;
byte gameBoard[32];

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



boolean play_memory(void)
{
  randomSeed(millis()); // Seed the random generator with random amount of millis()

  gameRound = 0; // Reset the game to the beginning

  while (gameRound < ROUNDS_TO_WIN)
  {
    add_to_moves(); // Add a button to the current moves, then play them back

    playMoves(); // Play back the current game board

    // Then require the player to repeat the sequence.
    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
      byte choice = wait_for_button(); // See what button the user presses

      if (choice == 0) return false; // If wait timed out, player loses

      if (choice != gameBoard[currentMove]) return false; // If the choice is incorect, player loses
    }

    delay(1000); // Player was correct, delay before playing moves
  }

  return true; // Player made it through all the rounds to win!
}

void add_to_moves(void)
{
  byte newButton = random(0, 4); //min (included), max (exluded)

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
    toner(gameBoard[currentMove], 150);

    // Wait some amount of time between button playback
    // Shorten this to make game harder
    delay(150); // 150 works well. 75 gets fast.
  }
  gamer.stopTone();
}

void toner(byte which, int buzz_length_ms)
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
      gamer.playTone(200);
      break;
    case CHOICE_UP:
      gamer.printImage(UP_ARROW);
      gamer.playTone(250);
      break;
    case CHOICE_DOWN:
      gamer.printImage(DOWN_ARROW);
      gamer.playTone(300);
      break;
  }
  gamer.stopTone();
}
byte wait_for_button(void)
{
  long startTime = millis(); // Remember the time we started the this loop

  while ( (millis() - startTime) < ENTRY_TIME_LIMIT) // Loop until too much time has passed
  {
    byte button = checkButton();

    if (button != CHOICE_NONE)
    { 
      toner(button, 150); // Play the button the user just pressed
      
      while(checkButton() != CHOICE_NONE) ;  // Now let's wait for user to release button
      
      delay(10); // This helps with debouncing and accidental double taps

      return button;
    }

  }

  return CHOICE_NONE; // If we get here, we've timed out!
}

byte checkButton(void)
{
  if (gamer.isPressed(DOWN)) return(CHOICE_DOWN); 
  else if (gamer.isPressed(UP)) return(CHOICE_UP);
  else if (gamer.isPressed(LEFT)) return(CHOICE_LEFT); 
  else if (gamer.isPressed(RIGHT)) return(CHOICE_RIGHT);
  
  return(CHOICE_NONE); // If no button is pressed, return none
}


