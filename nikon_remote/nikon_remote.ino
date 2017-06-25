
// ----- C -------
/**
 * arduino Nikon IR remote
 * @license Creative commons:Attribution-Noncommercial-Share Alike 3.0 (http://creativecommons.org/licenses/by-nc-sa/3.0/)
 * @author Aurelien ANTOINE
 * version 1
 * date 20081217
       *
       *
       * This version modified by Steve Hoefer September 12, 2011
       * Changes:
       *    - Removed status light
       *    - Added pushbutton trigger
       *    Shared back to the community per the BY-NC-SA license.
       *    Retains the original BY-NC-SA License above.
**/
// Solve the puzzle
// https://en.wikipedia.org/wiki/Antoine_equation

// Compile issues
// https://github.com/z3t0/Arduino-IRremote/issues/98
// https://forum.arduino.cc/index.php?topic=143940.0

#include <Stepper.h>
#include <IRremote.h>
#include <NewTone.h>

#define xDEBUG

#ifdef xDEBUG
#define TRACE(x) Serial.println(x)
#else
#define TRACE(x)
#endif /* xDEBUG */

//step motor revolution
#define REVStep 200
#define STEPSpeed 60

//initialize stepper library on pins 12 through 9
Stepper stepper(REVStep, 12, 11, 10, 9);

//speaker
#define TONEPin 5

//IR remote
IRrecv irrecv(6);
decode_results ir_results;

//IR led
#define LEDPin 3
#define FREQ 38400  // IR frequence
#define DELAY 3000  // Camera processing delay in ms

//mills elapsed from previous shot
unsigned long cur_millis;
unsigned long shot_millis;
 
//shutter sequence (on,off,on,off ... in microsecond)
unsigned long sequence[] = {2000,27830,390,1580,410,3580,400,63200,2000,27830,390,1580,410,3580,400,0};
int seq_l;
 
//oscd is a delay in microsecond used at each oscillation.
int oscd;
   
void oscillate(int pin, unsigned long n, int shine) 
{
  int ir_status=0;
  while(n>0){
    n--;
    delayMicroseconds(oscd);
    ir_status  =  !ir_status;
    digitalWrite(pin,  ir_status && shine); 
  }
}
   
void snap() 
{
  int i;
  for(i=0;i<seq_l;i++){
    oscillate(LEDPin, sequence[i], i%2==0);
  }
  digitalWrite(LEDPin,  0);
  TRACE("snap");
}

//program - testmotor
int no_turn = 0;
void setup_testmotor()
{
  stepper.setSpeed(60);
  no_turn=0;
  TRACE("STEPSpeed: " + 60);
  TRACE("STEPS: " + 400);
}

void terminate_testmotor()
{
}

void program_testmotor()
{
  stepper.step(400);
  TRACE(++no_turn);
}
//end program

//
//program - 360 24h time lapse
//400*113=45200 steps*turns -> total revolutions
//24*3600=86400 hours*seconds -> seconds in 24h
//86400/(DELAY/1000) totalseconds/delay in seconds -> shots taken in 24h
//steps total/shots to take -> revolutions per shot
#define REV_360_24 45200
int rev_360_24=0;
int shts_tkn=0;
void setup_360_24timelapse()
{
  stepper.setSpeed(STEPSpeed);
  rev_360_24=REV_360_24/(86400/(DELAY/1000));
  shot_millis=0;
  shts_tkn=0;
  TRACE("REV_360_24: " + REV_360_24);
  TRACE("rev_360_24: " + rev_360_24);
  TRACE("STEPSpeed: " + STEPSpeed);
  TRACE("DELAY (s): " + (DELAY/1000));
}

void terminate_360_24timelapse()
{
}

void program_360_24timelapse()
{
  if(cur_millis-shot_millis < DELAY) return;
  
  snap();
  shot_millis=cur_millis;
 
  stepper.step(rev_360_24);
  TRACE("shts_tkn: " + shts_tkn);
  TRACE("stepper.step: " + rev_360_24*shts_tkn);
}
//end program

//programs
enum program {
  SLEEP, //default
  TESTMOTOR, 
  TIMELAPSE360_24
};

//programs map keys
enum map_keys {
  SETUP,
  LOOP,
  TERMINATE,
  TONE
};

//defined programs map
void fn_null(){}
static void (*programs[][4])()={
//setup                     loop                        terminate                     tone
  {fn_null,                 fn_null,                    fn_null,                      (void (*)())330}, // why so many warining checks, learn plain JS      
  {setup_testmotor,         program_testmotor,          terminate_testmotor,          (void (*)())123}, // and understand the freedom
  {setup_360_24timelapse,   program_360_24timelapse,    terminate_360_24timelapse,    (void (*)())777}, // of thought
};
//active program
program cur_program=SLEEP;
//active program loop
void (*loop_ptr)()=&fn_null;

// takes action based on IR code received
void translateIR(unsigned long value) 
{
  programs[cur_program][TERMINATE]();
  cur_program=SLEEP;
  
  switch(value)
  {
  case 0xFFA25D:
    TRACE("CH-");
    break;
  case 0xFF629D:
    TRACE("CH");
    break;
  case 0xFFE21D:
    TRACE("CH+");
    break;
  case 0xFF22DD:
    TRACE("PREV");
    break;
  case 0xFF02FD:
    TRACE("NEXT");
    break;
  case 0xFFC23D:
    TRACE("PLAY/PAUSE");
    break;
  case 0xFFE01F:
    TRACE("VOL-");
    break;
  case 0xFFA857:
    TRACE("VOL+");
    break;
  case 0xFF906F:
    TRACE("EQ");
    break;
  case 0xFF6897:
    TRACE("0");
    break;
  case 0xFF9867:
    TRACE("100+");
    break;
  case 0xFFB04F:
    TRACE("200+");
    break;
  case 0xFF30CF:
    TRACE("1-test motor");
    cur_program=TESTMOTOR;
    break;
  case 0xFF18E7:
    TRACE("2-360 24h time lapse");
    cur_program=TIMELAPSE360_24;
    break;
  case 0xFF7A85:
    TRACE("3");
    break;
  case 0xFF10EF:
    TRACE("4");
    break;
  case 0xFF38C7:
    TRACE("5");
    break;
  case 0xFF5AA5:
    TRACE("6");
    break;
  case 0xFF42BD:
    TRACE("7");
    break;
  case 0xFF4AB5:
    TRACE("8");
    break;
  case 0xFF52AD:
    TRACE("9");
    break;
  default:
    TRACE("other button");
  }
  void (**program)()=programs[cur_program];
  program[SETUP]();
  loop_ptr=program[LOOP];
  NewTone(TONEPin, (int)program[TONE], 100);
  delay(100);
}
   
void setup() 
{
  #ifdef xDEBUG
    Serial.begin(9600);
  #endif
  
  stepper.setSpeed(STEPSpeed);
  irrecv.enableIRIn();
  
  int min=1, max=100, i;
  int last_oscd=0;
  unsigned long before, intervalle=0;
  oscd=max;
 
  seq_l = sizeof(sequence)/sizeof(unsigned long);
 
  pinMode(LEDPin, OUTPUT);
 
  //this "while" will process the best "oscd"
  while(last_oscd!=oscd){
    last_oscd=oscd;
    oscd=(min+max)>>1;// another puzzle
 
    before=millis();
    oscillate(LEDPin, FREQ, 1);
    intervalle=millis()-before;
 
    if(intervalle >= 1000) max=oscd;
    else min=oscd;
  }
 
  //rewrite the sequence array, we replace all values in microsecond by the number of oscillation
  for(i=0;i<seq_l;i++){
    sequence[i] = (sequence[i] * FREQ) / (intervalle * 1000);
  }
  //ready to receive
  NewTone(TONEPin, 137, 100);
  TRACE("nikon remote ready");
}
   
void loop() 
{
  cur_millis=millis();
  if(irrecv.decode(&ir_results)){
    translateIR(ir_results.value);
    irrecv.resume();
  }
  loop_ptr();
}
