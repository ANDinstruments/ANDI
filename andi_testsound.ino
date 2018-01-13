/*
 * ANDI
 * More info about the project at:
 * http://www.andinstruments.com
 * 
 */

#include <SD.h>                      
#define SD_ChipSelectPin 10         
#include <TMRpcm.h>                 
#include <SPI.h>

TMRpcm tmrpcm;  

unsigned long time = 0;


char loops[][8] ={"00.WAV", "01.WAV", "02.WAV", "03.WAV", "04.WAV", "05.WAV", "06.WAV", "07.WAV", "08.WAV", "09.WAV", "10.WAV", "11.WAV", "12.WAV", "13.WAV", "14.WAV", "15.WAV", "16.WAV", "17.WAV", "18.WAV", "19.WAV", "20.WAV", "21.WAV", "22.WAV", "23.WAV", "24.WAV", "25.WAV", "26.WAV", "27.WAV", "28.WAV", "29.WAV", "30.WAV", "31.WAV", "32.WAV", "33.WAV", "34.WAV", "35.WAV", "36.WAV", "37.WAV", "38.WAV", "39.WAV", "40.WAV", "41.WAV", "42.WAV", "43.WAV", "44.WAV", "45.WAV", "46.WAV", "47.WAV", "48.WAV", "49.WAV", "50.WAV", "51.WAV", "52.WAV", "53.WAV", "54.WAV", "55.WAV", "56.WAV", "57.WAV", "58.WAV", "59.WAV"};

int loopChoice = 5;
int instrumentChoice = 0;
int beats[32];
int loopNum;
int oldValue;
float delayTime = 300.0;
int loopLength = 16;

// Push button on rotary encoder
int pushButton = 4;

// Potentiometers
int potPin = A1;
int potVal;
int potPin2 = A2;
int potVal2;
int potPin3 = A3;
int potVal3;

// Rotary encoder
enum PinAssignments {
  encoderPinA = 2,
  encoderPinB = 3,
};

volatile unsigned int encoderPos = 500;
unsigned int lastReportedPos = 1;

boolean A_set = false;
boolean B_set = false;   

void setup(){

  randomSeed(analogRead(A0));
  

  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

for (int i=0; i <32; i++){
  beats[i]=random(0,9);
}
  
//  Uncomment if needed for debugging
//  Serial.begin(9600); 

  // Rotary encoder
  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT); 
  digitalWrite(encoderPinA, HIGH);  // turn on pull-up resistor
  digitalWrite(encoderPinB, HIGH);  // turn on pull-up resistor

// Encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
// encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

// SD-card

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }

}

// Rotary encoder
// Interrupt on A changing state
void doEncoderA(){
  // Test transition
  A_set = digitalRead(encoderPinA) == HIGH;
  // and adjust counter + if A leads B
  encoderPos += (A_set != B_set) ? +1 : -1;
}

// Interrupt on B changing state
void doEncoderB(){
  // Test transitionp
  B_set = digitalRead(encoderPinB) == HIGH;
  // and adjust counter + if B follows A
  encoderPos += (A_set == B_set) ? +1 : -1;
}


void loop(){  


while(true){
  
for (int i=0; i < loopLength; i++){

//Rotary encoder
// Push button on rotary encoder generates new beats


// Reading rotary encoder and choosing sound of instruments


// Potentiometers
// potVal changes length of delay which sets the tempo of the loop

// potVal2 changes the length of loop

potVal2 = 700;
  
  if(potVal2 < 205){
    loopLength = 2;
  }else if((potVal2 > 204) && (potVal2 < 410)){
    loopLength = 4;
  }else if((potVal2 > 409) && (potVal2 < 614)){
    loopLength = 8;
  }else if((potVal2 > 613) && (potVal2 < 819)){
    loopLength = 16;
  }else{
    loopLength = 32;
  }

// potVal3 changes the size of the orchestra

potVal3 = 820;
  
  if(potVal3 < 205){
    loopChoice = 1;
  }else if((potVal3 > 204) && (potVal3 < 410)){
    loopChoice = 2;
  }else if((potVal3 > 409) && (potVal3 < 614)){
    loopChoice = 3;
  }else if((potVal3 > 613) && (potVal3 < 819)){
    loopChoice = 4;
  }else{
    loopChoice = 5;
  }

// Beat calculation and output

loopNum = beats[i] + instrumentChoice;

if(loopChoice == 1){

  if( (beats[i] == 0 || beats[i] == 1 || beats[i] == 2)){
    tmrpcm.play(loops[loopNum]);
  }else{
    tmrpcm.play(loops[0]);
  }
}else if(loopChoice == 2){

  if( (beats[i] == 0 || beats[i] == 1 || beats[i] == 2 || beats[i] == 3)){
    tmrpcm.play(loops[loopNum]);
  }else{
    tmrpcm.play(loops[0]);
  }
}else if(loopChoice == 3){
      

  if( (beats[i] == 0 || beats[i] == 1 || beats[i] == 2 || beats[i] == 3 || beats[i] == 4 || beats[i] == 5)){
    tmrpcm.play(loops[loopNum]);
  }else{
    tmrpcm.play(loops[0]);
  }
}else if(loopChoice == 4){
      

  if( (beats[i] == 0 || beats[i] == 1 || beats[i] == 2 || beats[i] == 3 || beats[i] == 4 || beats[i] == 5|| beats[i] == 6 || beats[i] == 7)){
    tmrpcm.play(loops[loopNum]);
  }else{
    tmrpcm.play(loops[0]);
  }
}else{
    tmrpcm.play(loops[loopNum]);
}

  delay(400);


//  Uncomment if needed for debugging
// Serial print for debugging

/*  Serial.print("potVal: ");
    Serial.print(potVal);
    Serial.print("  potVal2: ");
    Serial.print(potVal2);
    Serial.print("  potVal3: ");
    Serial.print(potVal3);
    Serial.print("  encoderPos: ");
    Serial.print(encoderPos, DEC);
    Serial.print("  loopChoice: ");
    Serial.print(loopChoice);
    Serial.print("  instrumentChoice: ");
    Serial.println(instrumentChoice);
 */
 
}
}
}


