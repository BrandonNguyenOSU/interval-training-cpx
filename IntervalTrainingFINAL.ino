#include <Adafruit_CircuitPlayground.h>

float midi[127];
int A_four = 440; // a is 440 hz...

// Interrupts
volatile bool switchFlag = false;
volatile int switchState = 0;
volatile bool ButtonFlagA = false;
volatile bool ButtonFlagB = false;

// Game State values
volatile bool startUp = true;
volatile bool levelStart = false;

// Set of intervals from Unison to Octave
int interval_notes[8] = {0, 2, 4, 5, 7, 9, 11, 12};

//Values
volatile int highlight_LED = 1;  // highlight
volatile int correct = 0; // # of correct
volatile int interval_add = 0; // add to make interval

void setup() {

  CircuitPlayground.begin();
  Serial.begin(9600);
  generateMIDI();

  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(4), ButtonA, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), ButtonB, FALLING);
  attachInterrupt(digitalPinToInterrupt(7), Switch, CHANGE);

}

void loop() {
  
  if (switchFlag) {  //Switch Interrupt

    switchState = digitalRead(7);
    //Serial.println(switchState);

    switchFlag = 0;
    //Serial.println(switchFlag);

    if (switchState) {
      startUp = true;
    }
    else {
      CircuitPlayground.clearPixels();
    }

  }

  if (switchState && startUp) {

    correct = 0; // Reset correct

    for(int i = 1; i < 9; i++) {  // Set LEDs Red
      CircuitPlayground.setPixelColor(i,255,0,0);
    }

    levelStart = true;

    startUp = false;

  }

  if (correct == 8) {

    Serial.println("Game End");

    int play = 60;

    for(int i; i < 10; i++) {  //Win Animation
      
      CircuitPlayground.setPixelColor(i,0,255,0);

      CircuitPlayground.playTone(midi[play], 100);
      play += 2;

    }

    CircuitPlayground.clearPixels();

    levelStart = false;
    startUp = true;

    delay(500);

  }
  else if (switchState && levelStart) {

    //Serial.println("Level Start");
  
    for(int i = 1; i < 9; i++) {  // Set all LEDs Red
      CircuitPlayground.setPixelColor(i,255,0,0);
    }

    for(int i = 1; i <= correct; i++) {  // Set LEDs green for correct
      CircuitPlayground.setPixelColor(i,0,255,0);
    }

    // Reset highlighted LED
    highlight_LED = 1;
    CircuitPlayground.setPixelColor(highlight_LED, 255, 255, 255);

    int initial_note = random(48,72);  // Pick note within C3-C5 range
    interval_add = random(0,8);
    int secondary_note = initial_note + interval_notes[interval_add]; // Pick interval

    //Serial.println(initial_note);
    //Serial.println(secondary_note);
    Serial.println(interval_add);

    //Play interval
    CircuitPlayground.playTone(midi[initial_note], 200);
    CircuitPlayground.playTone(midi[secondary_note], 200);

    levelStart = false;

  }

  if (switchState) {  //  Run if board is on

    if(ButtonFlagA) {
      
      CircuitPlayground.clearPixels(); // Prepare animations
      int fix_interval_add = interval_add + 1; // Make usable value for correctness check

      if (fix_interval_add == highlight_LED) {  // Check correctness

        correct ++; // Add to correct

        for(int i = 1; i < 9; i++) {  // Correct Animation
          CircuitPlayground.setPixelColor(i,0,255,0);
          delay(50);
          CircuitPlayground.clearPixels();
        }

      }
      else { // if incorrect
      
        for(int i = 1; i < 9; i++) {  // Incorrect Animation
          CircuitPlayground.setPixelColor(i,255,0,0);
          delay(50);
          CircuitPlayground.clearPixels();
        }

      }

      levelStart = true;
      ButtonFlagA = false;

    }

    if(ButtonFlagB) {      

      for(int i = 1; i < 9; i++) {  // Set all LEDs Red
        CircuitPlayground.setPixelColor(i,255,0,0);
      }

      for(int i = 1; i <= correct; i++) {  // Set LEDs green for correct
        CircuitPlayground.setPixelColor(i,0,255,0);
      }

      // Move Highlighted LED
      highlight_LED ++;
      if (highlight_LED > 8) { // Set LED back to 1 if too high
        highlight_LED = 1;
      }
      CircuitPlayground.setPixelColor(highlight_LED, 255, 255, 255);

      ButtonFlagB = false;

    }

  }

}

void Switch() {
  switchFlag = 1;
  //Serial.println("Switched");
  //Serial.println(switchFlag);
}

void ButtonA() {
  ButtonFlagA = true;
}

void ButtonB() {
  ButtonFlagB = true;
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}
