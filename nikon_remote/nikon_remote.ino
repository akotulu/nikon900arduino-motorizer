
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

//arduino was ment to be programmed in plain C, but some experts decided it's ok to
//write libraries in c++ so they wont fit to smaller boards; this wont fit to Micro, replace virtuals
//whole concept is to learn how to write optimized asm in your head, not c++
//you will think twice when using other languages

#define SERIAL_PORT_SPEED 4800 

#define TONEPin  5
#define IRPin    6
#define LEDPin   3
#define STEPPin1 9
#define STEPPin2 11
#define STEPPin3 10
#define STEPPin4 12

//production code should be clean of any excess processing
#define xDEBUG
#ifdef xDEBUG
  #define TRACE0(x)   Serial.print(x)
  #define TRACE1(x)   Serial.println(x)
  #define TRACE2(x,y) Serial.print(x); Serial.println(y)
  #define TRACE3(x,y) Serial.print(x,y)
  #define TRACE4(x,y) Serial.println(x,y)
#else
  #define TRACE0(x)
  #define TRACE1(x)
  #define TRACE2(x,y)
  #define TRACE3(x,y)
  #define TRACE4(x,y)
#endif /* xDEBUG */

#include <Wire.h>
#include <Stepper.h>
#include <IRremote.h>
#include <NewTone.h>
#include <I2Cdev.h>
#include <RTIMUSettings.h>
#include <RTIMU.h>
#include <RTFusionRTQF.h>

#define tone(x) NewTone(TONEPin, x, 100)

//MPU9150
RTIMU *imu;               // IMU object
RTFusionRTQF fusion;      // fusion object  

//step motor revolution
#define REVStep    200
#define STEPSpeed  60
//initialize stepper library on pins 9 through 12
Stepper stepper(REVStep, STEPPin1, STEPPin2, STEPPin3, STEPPin4);

//IR remote
IRrecv irrecv(IRPin);

//IR led
#define FREQ     38400  // IR frequence
#define DELAYMS  3000   // Camera processing delay in ms
#define DELAYSEC 3

//mills elapsed from previous loop
unsigned long cur_millis;

//heading magnetic
float heading;
 
//shutter sequence (on,off,on,off ... in microsecond)
unsigned long sequence[] = {2000,27830,390,1580,410,3580,400,63200,2000,27830,390,1580,410,3580,400,0};
int seq_l;
 
//oscd is a delay in microsecond used at each oscillation.
int oscd;
   
void oscillate(int pin, unsigned long n, byte shine) 
{
  byte ir_status=0;
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
  for (i=0; i<seq_l; i++){
    oscillate(LEDPin, sequence[i], i%2==0);
  }
  digitalWrite(LEDPin,  0);
  TRACE1("snap");
}

//PROGRAMS
//
class Program {
 public:
  const short toneHz;
  Program(short toneHz): toneHz(toneHz) {}
  virtual ~Program() {}
  virtual void setup() {};
  virtual void terminate() {};
  virtual void loop() {};
  virtual bool irhandle(unsigned long /*value*/) {return false;}
};

class Idle: public Program {
 public:
  Idle(): Program(330) {};
};

//const class variables 
//take up memory
#define TONEBack 234
#define TONEForw 432
#define RunMotorSpeed 60
#define RunMotorSteps 400
class RunMotor: public Program {
  byte direction = 0;

  unsigned long tick;
  unsigned long turn_millis;
    
 public:
  RunMotor(): Program(123) {}

  void setup()
  { 
    stepper.setSpeed(RunMotorSpeed);
    
    tick = 0;
    direction = 0;
    
    TRACE2("STEPSpeed: ", RunMotorSpeed);
    TRACE2("STEPS: ", RunMotorSteps);
  }

  void loop()
  {
    if (!direction) return;
    //IMU wont get any attention otherwise
    if (cur_millis-turn_millis < 100) return;
    
    stepper.step(RunMotorSteps*direction);
    turn_millis = millis();
    TRACE2("millis: ", turn_millis);
    TRACE2("heading: ", heading);
    TRACE2("tick: ", tick=tick+direction);
  }

  bool irhandle(unsigned long value)
  {
    switch(value)
    {
    case 0xFF22DD:
      TRACE1("backwards");
      direction=-1;
      tone(TONEBack);
      return true;
    case 0xFF02FD:
      TRACE1("forward");
      direction=+1;
      tone(TONEForw);
      return true;
    default:
      return false;
    }
  }
};

class TakePicture: public Program {
  unsigned long shot_millis = 0;
  unsigned int delay_millis = 0;
  
 public:
  TakePicture(): Program(666) {}

  void loop()
  {
    if (!delay_millis) return;
    if (cur_millis-shot_millis < delay_millis) return;

    shot_millis = cur_millis;
    snap();
  }

  bool irhandle(unsigned long value)
  {
    switch(value)
    {
    case 0xFF30CF:
      TRACE1(1000);
      delay_millis+=1000;
      break;
    case 0xFF18E7:
      TRACE1(2000);
      delay_millis+=2000;
      break;
    case 0xFF7A85:
      TRACE1(3000);
      delay_millis+=3000;
      break;
    case 0xFF10EF:
      TRACE1(4000);
      delay_millis+=4000;
      break;
    case 0xFF38C7:
      TRACE1(5000);
      delay_millis+=5000;
      break;
    case 0xFF5AA5:
      TRACE1(6000);
      delay_millis+=6000;
      break;
    case 0xFF42BD:
      TRACE1(7000);
      delay_millis+=7000;
      break;
    case 0xFF4AB5:
      TRACE1(8000);
      delay_millis+=8000;
      break;
    case 0xFF52AD:
      TRACE1(9000);
      delay_millis+=9000;
      break;
    default:
      return false;
    }
    tone(delay_millis/432);
    return true;
  }
};

#define REVPerLap 45200
class TimeLapse24h360: public Program {  
  unsigned long shot_millis;
  unsigned long shts_per_rotation;
  unsigned long shts_tkn;
  unsigned long laps_traveled;
  
  float correction_heading;

 public:
  TimeLapse24h360(): Program(777) {}

  void setup()
  { 
    //400*113=45200 steps*turns -> total revolutions (measured)
    //24*3600=86400 hours*seconds -> seconds in 24h
    //86400/DELAYSEC totalseconds/delay in seconds -> shots taken in 24h
    //360/shots taken -> degrees to move every shot
    
    stepper.setSpeed(STEPSpeed);
  
    correction_heading = heading;
    shts_per_rotation = 86400/DELAYSEC;
    laps_traveled = 0;
    shot_millis=0;
    shts_tkn=0;

    TRACE2("HEADING: ", heading);
    TRACE2("STEPSpeed: ", STEPSpeed);
    TRACE2("DELAY(s): ", DELAYMS);
    TRACE2("SHOTS: ", shts_per_rotation);
  }

  void loop()
  {
    if (cur_millis-shot_millis < DELAYMS) 
      return;
      
    shot_millis = cur_millis;
    snap();
    ++shts_tkn;

    //check if shots taken is equal or greater from total shots taken, if so increase laps completed
    //laps start from zero, adding one will eliminate checking with zero
    if (shts_tkn >= shts_per_rotation*(1+laps_traveled)) laps_traveled++;
    //substract from total shots multiplication of traveled laps and shots per lap
    int shots_remaining = shts_tkn - shts_per_rotation*laps_traveled;
    //multiply one 360th of a degree to shots taken this lap 
    float cur_degree = (360.0f/shts_per_rotation)*(shts_tkn - shts_per_rotation*laps_traveled);
    //subtract from whole circle, traveled degree and divide it with remaining shots to take
    float deg_to_rotate = (360.0f-cur_degree)/(shts_per_rotation-shots_remaining);
    //every 3s x 20 equals one minute times 30, half an hour modulated from sum of seconds program has run,
    //two number modulation will result to divisor without remainder (zero) or remainder itself
    if ((shts_tkn*DELAYSEC) % 1800 == 0) {
      //check if magnetic heading has changed in past 30 minutes atleast 7 degrees, if not correct degrees to rotate
      if (max(heading, correction_heading) - min(correction_heading, heading) <= 7) {
        deg_to_rotate += 0.1f;
        TRACE1("warn, heading correction");
      }
      correction_heading = heading;
    }
    
    //revolution steps increse by % to deg_to_rotate 
    //45200*0.3/360=37,666
    //45200*0.9/360=113
    //revolutions motor travels per lap multiplied with fraction we want to rotate from whole circle
    int steps = -abs(REVPerLap * deg_to_rotate/360.0f);
    //locking motor to 100 steps, otherwise will block the microcontroller and device stops responding
    if (steps < -100) steps = -100;
    stepper.step(steps);

    TRACE2("heading: ", heading);
    TRACE2("cur_deg: ", cur_degree);
    TRACE2("millis: ", shot_millis);
    TRACE2("laps: ", laps_traveled);
    TRACE2("shts_tkn: ", shts_tkn);
    TRACE2("steps: ", steps);
    TRACE2("rotated: ", deg_to_rotate);
    TRACE1("-------");
  }
};
//end PROGRAMS

//program pointers
Program *cur_program = new Idle();
Program *new_program = NULL;

//takes action based on IR code received
void translateIR(unsigned long value) 
{  
  if (cur_program->irhandle(value)) return;
  
  new_program = new Idle();

  TRACE0("received IR: ");
  switch(value)
  {
  case 0xFFA25D:
  case 0xFF629D:
  case 0xFFE21D:
  case 0xFF22DD:
  case 0xFF02FD:
  case 0xFFC23D:
  case 0xFFE01F:
  case 0xFFA857:
  case 0xFF906F:
  case 0xFF6897:
  case 0xFF9867:
  case 0xFFB04F:
    TRACE1("unused");
    break;
  case 0xFF30CF:
    TRACE1("motor");
    new_program = new RunMotor();
    break;
  case 0xFF18E7:
    TRACE1("time lapse");
    new_program = new TimeLapse24h360();
    break;
  case 0xFF7A85:
    TRACE1("picture");
    new_program = new TakePicture();
    break;
  case 0xFF10EF:
  case 0xFF38C7:
  case 0xFF5AA5:
  case 0xFF42BD:
  case 0xFF4AB5:
  case 0xFF52AD:
    TRACE1("unused");
    break;
  default:
    TRACE1("unknown");
    return; //remote sends other unknown oscillations randomly, ignore
  }
  tone(new_program->toneHz);
  
  cur_program->terminate();
  delete cur_program;
  cur_program=new_program;
  cur_program->setup();
  delay(1000);
}
   
void setup() 
{
  #ifdef xDEBUG
    Serial.begin(SERIAL_PORT_SPEED);
  #endif
  TRACE1("starting");
  Wire.begin();
  RTIMUSettings settings;
  imu = RTIMU::createIMU(&settings);
  TRACE2("using device ", imu->IMUName());
  
  int errcode = imu->IMUInit();
  if (errcode < 0) TRACE2("error, failed to init IMU: ", errcode);
  if (!imu->getCalibrationValid()) TRACE1("error, compass isn't calibrated");
  
  //slerp power controls the fusion and can be between 0 and 1
  //0 means that only gyros are used, 1 means that only accels/compass are used
  //In-between gives the fusion mix.
  fusion.setSlerpPower(0.02);
  //use of sensors in the fusion algorithm can be controlled here
  fusion.setGyroEnable(false);
  fusion.setAccelEnable(false);
  fusion.setCompassEnable(true);

  TRACE1("setting stepper & enabeling IR");
  stepper.setSpeed(STEPSpeed);
  irrecv.enableIRIn();

  TRACE1("measuring oscd");
  int min=1, max=100, i;
  int last_oscd=0;
  unsigned long before, intervalle=0;
  oscd=max;
 
  seq_l = sizeof(sequence)/sizeof(unsigned long);
 
  pinMode(LEDPin, OUTPUT);
 
  //this "while" will process the best "oscd"
  while (last_oscd != oscd) {
    last_oscd=oscd;
    oscd=(min+max)>>1; //another puzzle
 
    before = millis();
    oscillate(LEDPin, FREQ, 1);
    intervalle = millis()-before;
 
    if (intervalle >= 1000) max=oscd;
    else min=oscd;
  }
 
  //rewrite the sequence array, we replace all values in microsecond by the number of oscillation
  for (i=0; i<seq_l; i++) {
    sequence[i] = (sequence[i] * FREQ) / (intervalle * 1000);
  }
  //ready to receive
  tone(137);
  TRACE1("ready, to kick some ass"); //roddy piper-they live (sadly noone remembers this event)
}

void loop() 
{
  cur_millis=millis();
  decode_results ir_results;
  if (irrecv.decode(&ir_results)) {
    translateIR(ir_results.value);
    irrecv.resume();
  }
  if (imu->IMURead()) 
  {
    fusion.newIMUData(imu->getGyro(), imu->getAccel(), imu->getCompass(), imu->getTimestamp());
    RTVector3 pose = fusion.getFusionPose();
     
    float d = 180.0f/PI;     //radians to degrees
    float yaw = pose.z()*d;  //0 yaw = 270 magnetic, this gives left or right up to 180 degrees
    heading = yaw-90;        //converts yaw to heading magnetic
    
    if (yaw<90 && yaw>=-179.99) heading = yaw+270;
  }  
  cur_program->loop();
}
