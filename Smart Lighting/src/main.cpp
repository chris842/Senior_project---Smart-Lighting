/*---------------------------------
|Project : Smart lighting
|Author : Chrisner Garcesa
|Version 1.0.0
|Updated 5/16/21
|ENGR 498
|WWU
-----------------------------------*/
/*
||Project description||

|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
|The main objective of the project was to be able to control two main aspects of lighting: turning it on/off and dimming the lights.                 |
|The code provided here was to carry out those functions. These could be done automatically, or manually via connecting to a smarthphone via BLE.    |
|The project has reached version 1.0.0 as of 5/16/21, the project has finally incorporated the main objectives I had in mind. Note that there        |
|are still some bugs, mainly the lighting system not immediately responding to the manual features when first initiated. Other than that, the project|
|objectives have been completed. More features will be added to the project in the future.                                                           |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|

||Project comoments||

4/27/21: Testing out BLE. Initial test will start off with simply turning the light on and off. Next test conducted should control light dimming.  
Tested out with the on board LED on the ESP32 and was successfuly able to turn that on and off.

4/29/21: Got device to turn light on/off and dim the lights. Currently working on how to combine the automatic and manual control feature

5/3/21: May have found a way to implement both automatic and manual control. Currently having an issue with one of the functions having too many arguments

5/12/21: Got issues with too many arguments in function. Finalizing on combining automatic and manual control; added terminal for debugging

5/13/21: So far, the automatic and manual control features have been working fine separately, but still having issues actually swithching betweeen both

5/16/21: Successfully got the automatic and manual features implemented together. There are some minor issues, but overall, the code is working as intended
Some of the bugs that were fixed included one where the lights would still turn on even though manual control was activated. Added a couple of if-statements
to some functions so that it would only activate when needed. One major issue currently is the ESP32 disconnects at times, so it'll need to be rebooted again
for it to reconnect.

||Issues||
-ESP32 has some difficulty connecting with smartphone
-Randomly disconnects at times; EN button needs to be activated to reconnect
-Slow responsiveness upon startup; button needs to be pressed for it to start working; works fine afterwards

**Code Completion ETA: 5/28/21 -- Main code function completed 5/16/21**
*/
#include <Arduino.h>
#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include "BluetoothSerial.h"

#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT
#define LED 2

//Authorization
char auth[] = "######################";

//Amount of time (seconds) the light will stay on
#define timeSeconds 300

//Blynk Timer
BlynkTimer timer;

//PWM properties
int freq = 5000;          //PWM Frequency
int channel = 0;
int resolution = 8;       //Signal Resolution
int DutyCycle = 0;

//Initial ADC Value and voltage value
int ADC_VALUE = 0;     //Digital Value -- Holds the calculated ADC Value
double V_m = 0;

//Some constants
const int ADC_Res = 4095;         //ADC Resolution -- 
const int V_s = 3.3;              //Supply voltage to the ESP32

//Assigned pins
const int dimming_pin = 16;       //PWM Output -- Pin 16 -- RX
const int relay_signal = 17;      //Outputs to realy -- Pin 17 -- TX
const int analog_pin = 36;        //Photoresistor input -- Pin 36 -- VP
const int motion_detection = 39;  //PIR sensor input -- Pin 39 -- VN

//Timer Variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

//Variable to select between auto and manual control
int selectMode;

/*---------------------------------
Motion detection function
---------------------------------*/
void IRAM_ATTR detectsMovement(){
  if (selectMode == 0){
    Serial.print("Motion Detected");
    digitalWrite(relay_signal, HIGH);
    startTimer = true;
    lastTrigger = millis();
  }
}

/*-----------------------------------------------
Blynk Terminal -- mainly for debugging purposes
-----------------------------------------------*/
WidgetTerminal terminal(V3);
void autoManualControl();

void setup() {
  // put your setup code here, to run once:

  //BLE Authorization and Initiation
  Serial.begin(115200);
  Serial.println("Waiting for connections...");

  Blynk.setDeviceName("Blynk Test");

  //Setting PWM pins
  ledcAttachPin(dimming_pin, channel);
  ledcSetup(channel, freq, resolution);

  //PWM Functionality
  ledcSetup(channel, freq, resolution);
  
  //GPIO Channel attachment for control
  ledcAttachPin(dimming_pin, channel);

  //LED 2 Control
  pinMode(LED, OUTPUT);

  //PIR Sensor mode INPUT_PULLUP
  pinMode(motion_detection, INPUT_PULLUP);

  //Setting motion_detection as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motion_detection), detectsMovement, RISING);

  //Setting to LOW
  pinMode(relay_signal, OUTPUT);
  digitalWrite(relay_signal, LOW);
  
  Blynk.begin(auth);

  timer.setInterval(1000,autoManualControl);
}

/*--------------------------
Auto-manual control function
--------------------------*/
void autoManualControl(){
  if (selectMode == 1){
    //Manual control if selectMode = 1
    terminal.print("Manual Mode ");
  
  }else{
    //Auto control if selectMode = 0
    terminal.print("Automatic Mode ");
    
    //Current time
    now = millis();

    //Turn off light if no motion is detected after a certain amount of time
    if(startTimer && (now - lastTrigger > (timeSeconds*1000))){
      Serial.print("Motion Stopped");
      digitalWrite(relay_signal, LOW);
      startTimer = false;
    }

    //Blink LED to inidcate program start
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);

    //Voltage Detection
    ADC_VALUE = analogRead(analog_pin);
    Serial.print("ADC Value = ");
    Serial.println(ADC_VALUE);
    delay(100);

    //Voltage Calculation
    V_m = (ADC_VALUE*3.3)/(4095);
    Serial.print("Voltage = ");
    Serial.print(V_m);
    Serial.print("V");
    delay(10);

    //Duty Cycle Calcualtion
    DutyCycle = 255*(V_m/3.3);
    ledcWrite(channel, DutyCycle);
    delay(500);
    Serial.print("Duty Cycle = ");
    Serial.println(DutyCycle);
    delay(100);
  }
}

/*-------------------------------------------------------------
Blynk select button -- Switches between auto and manual control
--------------------------------------------------------------*/
BLYNK_WRITE(V0){
  selectMode = param.asInt();
  autoManualControl;
  terminal.print("Button pressed. ");
}

/*---------------------------------
Blynk slider virtual pin
PWM Controller
---------------------------------*/
BLYNK_WRITE(V1){
  int pwm_value = param.asInt();
  if (selectMode == 1){
    ledcWrite(channel,pwm_value);
  }
}

/*-----------------------------------
Blynk button virtual pin
Manually send signal to relay
------------------------------------*/
BLYNK_WRITE(V2){
  int relay = param.asInt();
  if (selectMode ==1){
    if (relay == 1){
      digitalWrite(relay_signal, HIGH);
    }else{
      digitalWrite(relay_signal, LOW);
    }
  }
}

//loop function
void loop() {
  Blynk.run();
  timer.run();
}
