

/*
For RGB pins LOW = ON, HIGH = OFF
each segment represents 210 RPM incriments

*/

//RPM Simulation variable PIN
int RPM_PIN = 15;
int RPM = 0;
int setC = 0;
int setA = 0;

//Anodes
int aLen = 2;

int red[] = {2,3,4,0};
int Red1 = 2;
int Red2 = 3;
int Red3 = 4;

int green[] = {10,9,8,0};
int Green1 = 10;
int Green2 = 9;
int Green3 = 8;

int blue[] = {7,6,5,0};
int Blue1 = 7;
int Blue2 = 6;
int Blue3 = 5;

//Cathode Pin setup                         1   -   2   -  3
int C1 = 46;   //C1 - 53            RPM - ..210 - ..420 - ..630
int C2 = 48;   //C2 - 51            RPM - ..840 - .1050 - .1260
int C3 = 49;   //C3 - 49            RPM - .1470 - .1680 - .1890
int C4 = 47;   //C4 - 47            RPM - .2100 - .2310 - .2520
int C5 = 45;   //C5 - 45            RPM - .2730 - .2940 - .3150
int C6 = 43;   //C6 - 43            RPM - .3360 - .3570 - .3780
int C7 = 41;   //C7 - 41            RPM - .3990 - .4200 - .4410
int C8 = 39;   //C8 - 39            RPM - .4620 - .4830 - .5040
int C9 = 37;   //C9 - 23            RPM - .5250 - .5460 - .5670
int C10 = 33;   //C10- 25           RPM - .5880 - .6090 - .6300
int C11 = 35;   //C11- 27           RPM - .6510 - .6720 - .6930
int C12 = 31;   //C12- 29           RPM - .7140 - .7350 - .7560
int C13 = 28;   //C13- 31           RPM - .7770 - .7980 - .8190
int C14 = 26;   //C14- 33           RPM - .8400 - .8610 - .8820
int C15 = 24;   //C15- 35           RPM - .9030 - .9240 - .9450
int C16 = 22;   //C16- 37           RPM - .9660 - .9870 - 10080

int cLen = 16;
int cathode[] = {53,51,49,47,45,43,41,39,37,33,35,31,28,26,24,22,0};

void setup() {
  
  ////////////////////////////////////////////////////////DEBUGGING Stuff
  //Potentiameter input
  pinMode(RPM_PIN,INPUT);

  //  setup serial
  Serial.begin(9600);          
  
  ////////////////////////////////////////////////////////RGB Anode control 
  
  ////////////////////////////////////////////////////////RED
  for (int aPin = 0; aPin < aLen; aPin++) {
    pinMode(red[aPin], OUTPUT);
  }

  ///////////////////////////////////////////////////////Green
  for (int aPin = 0; aPin < aLen; aPin++) {
    pinMode(green[aPin], OUTPUT);
  }
  
  ///////////////////////////////////////////////////////Blue 
  for (int aPin = 0; aPin < aLen; aPin++) {
    pinMode(blue[aPin], OUTPUT);
  }
  
  ///////////////////////////////////////////////////////Cathode Control
    for (int cPin = 0; cPin < cLen; cPin++) {
    pinMode(cathode[cPin], OUTPUT);
  }

  initialize();
}



void loop() {

RPM = analogRead(RPM_PIN);
RPM = RPM*10;

////////////////////////////////////////////////////Initilize Anode




////////////////////////////////////Set RPM Limits

if(RPM >= 210 && RPM <= 630){
  setC = 0;
    Green_LED(1);
}
else if(RPM >= 631 && RPM <= 1260){
  setC = 1;
    Green_LED(1);
}
else if(RPM >= 1261 && RPM <= 1890){
  setC = 2; 
    Green_LED(1);
}
else if(RPM >= 1891 && RPM <= 2520){
  setC = 3; 
    Green_LED(1);
}
else if(RPM >= 2521 && RPM <= 3150){
  setC = 4;
    Green_LED(1);
}
else if(RPM >= 3151 && RPM <= 3780){
  setC = 5;
    Green_LED(1);
}
else if(RPM >= 3781 && RPM <= 4410){
  setC = 6;
    Green_LED(1);
}
else if(RPM >= 4411 && RPM <= 5040){
  setC = 7;
    Green_LED(1);
}
else if(RPM >= 5041 && RPM <= 5670){
  setC = 8;
    Green_LED(1);
}
else if(RPM >= 5671 && RPM <= 6300){
  setC = 9;
    Green_LED(1);
}
else if(RPM >= 6301 && RPM <= 6930){
  setC = 10;
    Green_LED(1);
}
else if(RPM >= 6931 && RPM <= 7560){
  setC = 11;
    Green_LED(1);
}
else if(RPM >= 7561 && RPM <= 8190){ 
  setC = 12;
    Blue_LED(1);
}
else if(RPM >= 8191 && RPM <= 8820){
  setC = 13;
    Blue_LED(1);
}
else if(RPM >= 8821 && RPM <= 9450){
  setC = 14;
    Red_LED(1);
}
else if(RPM >= 9451 && RPM <= 10000){
  setC = 15;
    Red_LED(1);
}
else if(RPM > 10001){
Flash_LED(70,1,'r');       //speed in milliseconds, brightness 0-255, color r = red, g = green, b = blue
}




///////////////////////////////////////////////////Debug Values
Serial.print("Cathode: ");
Serial.println(setC);
Serial.print("Anode: ");
Serial.println(setA);
Serial.print("RPM: ");
Serial.println(RPM);    

/////////////////////////////////////////////////Writing LEDs with color

  section_LED(setC);
  reset();
}



//**************************LED FUNCTIONS****************************************//

///////////////////////////////////////////////////////////LED set color functions
void Red_LED(int bright){
  for(int aRed = 0; aRed <= aLen; aRed++){
        analogWrite(red[aRed],bright);
        analogWrite(red[aRed+1],255);
}
}

void Green_LED(int bright){
  for(int aGreen = 0; aGreen <= aLen; aGreen++){
        analogWrite(green[aGreen],bright);
        analogWrite(green[aGreen+1],255);
}
}

void Blue_LED(int bright){
  for(int aBlue = 0; aBlue <= aLen; aBlue++){
       analogWrite(blue[aBlue],bright); 
       analogWrite(blue[aBlue+1],255);
}
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////LED Cathode section function
void section_LED(int set){
  for(int cath = 0; cath <= set; cath++){
  digitalWrite(cathode[cath],HIGH);

  digitalWrite(cathode[cath+1],LOW);
}
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////FLASH Function (SHIFT FLASH)
void Flash_LED(int Speed, int bright, char color){

if(color == 'r'){    
           for(int c = 0; c<=cLen; c++){
              digitalWrite(cathode[c],HIGH);
           }
              Red_LED(bright);
              delay(Speed);
           for(int c = 0; c <= cLen; c++){
             digitalWrite(cathode[c],LOW);
           }  
              delay(Speed);
              Red_LED(255);
          }  
else if(color == 'b'){  
           for(int c = 0; c<=cLen; c++){
              digitalWrite(cathode[c],HIGH);
           }
              Blue_LED(bright);
              delay(Speed);
           for(int c = 0; c <= cLen; c++){
             digitalWrite(cathode[c],LOW);
           }  
              delay(Speed);
              Blue_LED(255);            
          }
else if(color == 'g'){  
           for(int c = 0; c<=cLen; c++){
              digitalWrite(cathode[c],HIGH);
           }
              Green_LED(bright);
              delay(Speed);
           for(int c = 0; c <= cLen; c++){
             digitalWrite(cathode[c],LOW);
           }  
              delay(Speed);
              Green_LED(255);            
          }          
}
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////INITIALIZE
void initialize(){
    for(int cath = 0; cath <= cLen; cath++){
          digitalWrite(cathode[cath],HIGH);
          delay(100);
          Red_LED(100);
          Blue_LED(1);
          Green_LED(200);
    }
    

  
    for(int cath = 0; cath <= cLen; cath++){
          digitalWrite(cathode[cath],LOW);
          delay(100);

    }
reset();
}

void reset(){
            Red_LED(255);
          Blue_LED(255);
          Green_LED(255);
}

