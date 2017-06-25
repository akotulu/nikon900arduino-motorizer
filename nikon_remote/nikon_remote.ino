
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

//active program loop, every program must set it when appropriate
void fn_null(){}
void (*loop_ptr)()=&fn_null;

//step motor revolution
#define REVStep 200
#define STEPSpeed 60

//initialize stepper library on pins 12 through 9
Stepper stepper(REVStep, 9, 11, 10, 12);

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

//program - RUNMOTOR
int no_turn=0;
int direction=1;
void setup_RUNMOTOR()
{
  stepper.setSpeed(60);
  no_turn=0;
  loop_ptr=&fn_null;
  TRACE("STEPSpeed: "+60);
  TRACE("STEPS: "+400);
}

int irhandle_RUNMOTOR(unsigned long value)
{
  switch(value)
  {
  case 0xFF22DD:
    TRACE("PREV-backwards");
    direction=-1;
    NewTone(TONEPin, 234, 100);
    break;
  case 0xFF02FD:
    TRACE("NEXT-forward");
    direction=+1;
    NewTone(TONEPin, 432, 100);
    break;
  default:
    return 0;
  }
  loop_ptr=&program_RUNMOTOR;
  return 1;
}

void terminate_RUNMOTOR()
{
  loop_ptr=&fn_null;
}

void program_RUNMOTOR()
{
  stepper.step(400*direction);
  TRACE(no_turn=no_turn+direction);
}
//end program


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
  loop_ptr=&program_360_24timelapse;
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
  loop_ptr=&fn_null;
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
enum program{
  SLEEP, //default
  RUNMOTOR,
  TIMELAPSE360_24
};

//program definition
struct program_def{
  void (*setup)();
  int (*irhandle)(unsigned long value);
  void (*terminate)();
  int tone;
};

//defined programs map
program_def programs[]={
  {.setup=fn_null, .irhandle=NULL, .terminate=fn_null, .tone=330},
  {.setup=setup_RUNMOTOR, .irhandle=irhandle_RUNMOTOR, .terminate=terminate_RUNMOTOR, .tone=123},
  {.setup=setup_360_24timelapse, .irhandle=NULL, .terminate=terminate_360_24timelapse, .tone=777},
};

//active program
program cur_program=SLEEP;

// takes action based on IR code received
void translateIR(unsigned long value) 
{
  program_def program=programs[cur_program];
  
  if (program.irhandle!=NULL && program.irhandle(value)) return;

  switch(value)
  {
  case 0xFFA25D:
    TRACE("CH-");
    cur_program=SLEEP;
    break;
  case 0xFF629D:
    TRACE("CH");
    cur_program=SLEEP;
    break;
  case 0xFFE21D:
    TRACE("CH+");
    cur_program=SLEEP;
    break;
  case 0xFF22DD:
    TRACE("PREV");
    cur_program=SLEEP;
    break;
  case 0xFF02FD:
    TRACE("NEXT");
    cur_program=SLEEP;
    break;
  case 0xFFC23D:
    TRACE("PLAY/PAUSE");
    cur_program=SLEEP;
    break;
  case 0xFFE01F:
    TRACE("VOL-");
    cur_program=SLEEP;
    break;
  case 0xFFA857:
    TRACE("VOL+");
    cur_program=SLEEP;
    break;
  case 0xFF906F:
    TRACE("EQ");
    cur_program=SLEEP;
    break;
  case 0xFF6897:
    TRACE("0");
    cur_program=SLEEP;
    break;
  case 0xFF9867:
    TRACE("100+");
    cur_program=SLEEP;
    break;
  case 0xFFB04F:
    TRACE("200+");
    cur_program=SLEEP;
    break;
  case 0xFF30CF:
    TRACE("1-run motor");
    cur_program=RUNMOTOR;
    break;
  case 0xFF18E7:
    TRACE("2-360 24h time lapse");
    cur_program=TIMELAPSE360_24;
    break;
  case 0xFF7A85:
    TRACE("3");
    cur_program=SLEEP;
    break;
  case 0xFF10EF:
    TRACE("4");
    cur_program=SLEEP;
    break;
  case 0xFF38C7:
    TRACE("5");
    cur_program=SLEEP;
    break;
  case 0xFF5AA5:
    TRACE("6");
    cur_program=SLEEP;
    break;
  case 0xFF42BD:
    TRACE("7");
    cur_program=SLEEP;
    break;
  case 0xFF4AB5:
    TRACE("8");
    cur_program=SLEEP;
    break;
  case 0xFF52AD:
    TRACE("9");
    cur_program=SLEEP;
    break;
  default:
    TRACE("other button");
    return; //remote sends other button randomly, need to ignore
  }
  NewTone(TONEPin, program.tone, 100);
    
  program.terminate();
  program=programs[cur_program];
  program.setup();
  delay(1000);
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
