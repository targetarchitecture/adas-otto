//-- Otto DIY+ basic firmware v6 (ottodiy.com)
//-- CC BY SA
//-- 10 September 2017
//-----------------------------------------------------------------
//-- Otto DIY+ with Touch Sensor!
//-----------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>

Otto Otto;  //This is Otto!
//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
           ----/\----     <== Touch Sensor Pin 2
         ---------------
        |     O   O     |
        |---------------|
  YR 3==> |               | <== YL 6
         ---------------
            ||     ||
  RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
#define PIN_YL 6 //servo[2]
#define PIN_YR 3 //servo[3]
#define PIN_RL 4 //servo[4]
#define PIN_RR 5 //servo[5]
const int sensorPin = 2;
///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
//-- Movement parameter

volatile int movement = 1; //https://www.arduino.cc/reference/en/language/variables/variable-scope--qualifiers/volatile/

//---------------------------------------------------------
bool obstacleDetected = false;

//-- Movement parameters
int T = 1000;            //Initial duration of movement
int moveId = 0;          //Number of movement
int modeId = 0;          //Number of mode
int moveSize = 15;       //Asociated with the height of some movements

unsigned long previousMillis = 0;

unsigned long previousTouchMillis = 0;

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup() {

  //Serial communication initialization
  Serial.begin(115200);

  //Set the servo pins
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, -1, 13, 8, 9);
  pinMode(sensorPin, INPUT);
  Otto.home();
  Otto.sing(S_happy); // a happy Otto :)
  Otto.jump(1, 700);

  attachInterrupt(0, touch_handler, RISING  );

  Otto.sing(S_superHappy);

  randomSeed(analogRead(0));
}


void touch_handler() {

  if (millis() - previousTouchMillis <= 800) {
    Serial.println("Double Tap Detected in " + String(millis() - previousTouchMillis) + "ms" );

    movement = 1;
  } else {
    Serial.println("Touch Detectedin " + String(millis() - previousTouchMillis) + "ms");

    movement++; //https://www.arduino.cc/reference/en/language/structure/compound-operators/increment/

    if (movement == 4)
    {
      movement = 1;
    }
  }

  Serial.println("Touch movement " + String(movement));

  previousTouchMillis = millis();

  //long randSing = random(1, 19);

  Otto.sing(S_buttonPushed);

}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  switch (movement) {
    case 1:
      do {
        //Every 40 seconds in this mode, Otto falls asleep
        if (millis() - previousMillis >= 40000) {
          OttoSleeping_withInterrupts(); //ZZzzzzz...
          previousMillis = millis();
        }
      } while (movement == 1);
      break;
    case 2:
      do {
        walkAround();
      } while (movement == 2);
      break;
    case 3:
      do {
        dance();
      } while (movement == 3);
      break;
  }
}

///////////////////////////////////////////////////////////////////
//-- Function to read distance sensor & to actualize obstacleDetected variable
void obstacleDetector() {
  int distance = Otto.getDistance();
  if (distance < 15) {
    obstacleDetected = true;
  } else {
    obstacleDetected = false;
  }
}


void OttoSleeping_withInterrupts() {

  int bedPos_0[4] = {100, 80, 60, 120};

  Otto._moveServos(700, bedPos_0);

  long randSing = random(1, 19);

  Otto.sing(randSing);

  Otto.home();
}



void walkAround() {

  if (obstacleDetected) {
    Otto.sing(S_surprise);
    Otto.jump(5, 500);
    Otto.sing(S_cuddly);

    //Otto takes two steps back
    for (int i = 0; i < 3; i++) {
      Otto.walk(1, 1300, -1);
    }
    delay(100);
    obstacleDetector();
    delay(100);

  } else {

    Otto.walk(1, 1000, 1); //Otto walk straight
    obstacleDetector();
    //  }

  }
}

// TEMPO: 97 BPM
int danceTempo = 620;
int danceHeight = 20;
int danceMovementTime = 1;

void dance() {

  Serial.println("Dance!");
  Otto.home();

  do {

    long randNumber = random(1, 12);

    switch (randNumber) {
      case 1:
        Otto.bend(danceMovementTime, danceTempo, LEFT);
        Otto.bend(danceMovementTime, danceTempo, RIGHT);
        break;
      case 2:
        Otto.shakeLeg (danceMovementTime, danceTempo, LEFT);
        break;
      case 3:
        Otto.shakeLeg (danceMovementTime, danceTempo, RIGHT);
        break;
      case 4:
        Otto.updown (danceMovementTime, danceTempo, danceHeight);
        break;
      case 5:
        Otto.swing (danceMovementTime, danceTempo, danceHeight);
        break;
      case 6:
        Otto.tiptoeSwing (danceMovementTime, danceTempo, danceHeight);
        break;
      case 7:
        Otto.jitter (danceMovementTime, danceTempo, danceHeight);
        break;
      case 8:
        Otto.ascendingTurn (danceMovementTime, danceTempo, danceHeight);
        break;
      case 9:
        Otto.moonwalker (danceMovementTime, danceTempo, danceHeight, LEFT);
        Otto.moonwalker (danceMovementTime, danceTempo, danceHeight, RIGHT);
        break;
      case 10:
        Otto.crusaito (danceMovementTime, danceTempo, danceHeight, LEFT);
        Otto.crusaito (danceMovementTime, danceTempo, danceHeight, RIGHT);
        break;
      case 11:
        Otto.flapping (danceMovementTime, danceTempo, danceHeight, LEFT);
        Otto.flapping (danceMovementTime, danceTempo, danceHeight, RIGHT);
        break;
    }
    delay(100);
  } while (movement == 3);

}
