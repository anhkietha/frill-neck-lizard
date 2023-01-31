// include library
#include <Servo.h>
#include <Ramp.h>                          
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define FULLY_OPEN_ANGLE 70
#define FULLY_FOLD_ANGLE 170
#define TIME_RESPONSE 3000

#define WAITING_FOR_MOTION_STATE 0
#define OPENNING_THE_FRILL_STATE 1
#define FOLDING_THE_FRILL_STATE 2


ramp myRamp;
Adafruit_MPU6050 mpu;
Servo servo;


// this varible will indicate which state the lizard are in
int state = WAITING_FOR_MOTION_STATE;


// this variable will stand for the time it took for the ramp
// to reach the target motion. Currently it is set to 0.5s to reach the target
int time_run = 500;


// these two variable will record when the frill opens and closes
long int t_start;
long int t_end;

void setup() {
  Serial.begin(115200);

  //all the code below is obtained from the library
  // Connecting the mpu6050
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  //setup motion detection

  mpu.setHighPassFilter(MPU6050_HIGHPASS_1_25_HZ);
  mpu.setMotionDetectionThreshold(5);
  mpu.setMotionDetectionDuration(10);
  mpu.setInterruptPinLatch(true);
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.println("");
  delay(100);

  //Initialize the position of the frill
  servo.attach(3);
  servo.write(FULLY_FOLD_ANGLE);
}

void loop() {
  // the first state is the waiting for the motion
  if (state == WAITING_FOR_MOTION_STATE){
    if(mpu.getMotionInterruptStatus()) {
      //detects motion change the state of the frill
      state = OPENNING_THE_FRILL_STATE;

      // start interpolation to the fully open angle
      myRamp.go(FULLY_OPEN_ANGLE, time_run, CUBIC_OUT);
      double actual = myRamp.update();
      servo.write(actual);

      //store the time that it detected the motion
      t_start = millis();
      
      Serial.println(t_start);
      Serial.println("Motion detected, open the frill");
      Serial.println(t_start);
      
    }
  } else if (state == OPENNING_THE_FRILL_STATE){
    //the state now is oppening the frill

    //get the current value of from the ramp
    //and write it to the servo
    double actual = myRamp.update();
    servo.write(actual);

    //get the current time value
    t_end = millis();

    //if it open the frill longer than time response
    // it will change the state to fold the frill
    if (actual == FULLY_OPEN_ANGLE && t_end - t_start >= TIME_RESPONSE){

      // change the state to fold the frill state
      state = FOLDING_THE_FRILL_STATE;

      //start interpolation to the fully fold angle
      myRamp.go(FULLY_FOLD_ANGLE, time_run, CUBIC_OUT);
      double actual = myRamp.update();
      servo.write(actual);
      Serial.println(t_end);
      Serial.println("More than 3s, close the frill");
    }
    
    
  } else if (state == FOLDING_THE_FRILL_STATE){
    //the state now is folding the frill
    
    //get the current value of the interpolation from the ramp
    //and write it to the servo
    double actual = myRamp.update();
    servo.write(actual);

    if (actual == FULLY_FOLD_ANGLE){
      // if it reach the fully fold angle
      // change the state to waiting for motion state
      state = WAITING_FOR_MOTION_STATE;

      // because when it completely folds back, this makes some vibration due to the motion
      // of the frill. Therefore, make this react as we expected

      delay(500);
    }
    mpu.getMotionInterruptStatus();
    
    
  }

  delay(10);
}
