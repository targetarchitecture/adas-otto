//----------------------------------------------------------------
//-- Otto Dance single ladies by Beyonce
//-- Released under a GPL licencse (http://ottodiy.com)
//-- Author: brico3d.blogspot.com
//-----------------------------------------------------------------
#include <Oscillator.h>
#include <EEPROM.h>

#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//#include <math.h>
//#include <stdio.h>
//#include <stdint.h>
//#include <avr/io.h>


#define N_SERVOS 4
#define EEPROM_TRIM false //Activate for calibration

#define TRIM_RR 18
#define TRIM_RL 18
#define TRIM_YR 26
#define TRIM_YL 18

#define PIN_YL 6 //servo[2]
#define PIN_YR 3 //servo[3]
#define PIN_RL 4 //servo[4]
#define PIN_RR 5 //servo[5]

#define INTERVALTIME 10.0



class singleLadies
{
  public:

    void init ();
    void dance ();

  private:

    void drunk (int tempo);
    void kickLeft(int tempo);
    void kickRight(int tempo);
    void pasitos(int steps, int tempo);
    void patada ( int tempo);
    void run(int steps, int T = 500);
    void walk(int steps, int T = 1000);
    void backyard(int steps, int T = 3000);
    void moonWalkLeft(int steps, int T = 1000);
    void moonWalkRight(int steps, int T = 1000);
    void crusaito(int steps, int T = 1000);
    void swing(int steps, int T = 1000);
    void upDown(int steps, int tempo);
    void flapping(int steps, int T = 1000);
    void twist(int steps, int tempo);
    void saludo(int steps, int tempo);
    void reverencia1 (int steps, int tempo);
    void reverencia2 (int steps, int tempo);
    void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]);
    void moveNServos(int time, int  newPosition[]);
void lateral_fuerte(boolean side, int tempo);
};
