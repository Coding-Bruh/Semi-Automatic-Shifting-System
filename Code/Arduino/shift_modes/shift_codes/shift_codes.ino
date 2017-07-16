  const int forwards = 2;
  const int backwards = 4;
  const int up = 0;
  const int down = 1;
  int RPM_Pin = 0;
  bool shiftup = 0;
  bool shiftdown = 0;
  const int ClutchOut = 8;
  const int ClutchIn = 7;
  int RPM;

void setup() {

pinMode(forwards, OUTPUT);//Set relay as an output
pinMode(backwards, OUTPUT);//Set relay as an output
pinMode(ClutchIn, OUTPUT);
pinMode(ClutchOut, OUTPUT);
pinMode(up, INPUT);
pinMode(down, INPUT);
pinMode(RPM_Pin, INPUT);
Serial.begin(19200);

int Time;
//retrackGear(1000);
//moveGearToCenter(100);
Time = micros() - Time;
Serial.println(Time);

}

void loop() 
{
//  RPM = analogRead(RPM_Pin);
//
  int num = analogRead(up);
  int num2 = analogRead(down);
//  Serial.println(num2);
  //digitalWrite(ClutchOut, LOW);
  //digitalWrite(ClutchIn, LOW);
  //digitalWrite(forwards,LOW);
  //digitalWrite(backwards,LOW);
  if(num > 900)
  {
//    digitalWrite(ClutchOut, LOW);
//    digitalWrite(ClutchIn, HIGH);
//    delay(500);
//    digitalWrite(forwards,HIGH);
//    digitalWrite(backwards,LOW);
//    delay(110);
//    digitalWrite(forwards,LOW);
//    digitalWrite(backwards,HIGH);
//    delay(110);
//    digitalWrite(forwards,HIGH);
//    digitalWrite(backwards,HIGH);
//    digitalWrite(ClutchOut, HIGH);
//    digitalWrite(ClutchIn, LOW);
//    delay(500);
//    
  }
//  else
//   digitalWrite(forwards,HIGH);
//   digitalWrite(backwards,HIGH);
//   digitalWrite(ClutchOut, HIGH);
//   digitalWrite(ClutchIn, HIGH);
//  
//  if(num2 > 900)
//  {
//    digitalWrite(ClutchOut, LOW);
//    digitalWrite(ClutchIn, HIGH);
//    delay(500);
//    digitalWrite(forwards,LOW);
//    digitalWrite(backwards,HIGH);
//    delay(110);
//    digitalWrite(forwards,HIGH);
//    digitalWrite(backwards,LOW);
//    delay(110);
//    digitalWrite(forwards,HIGH);
//    digitalWrite(backwards,HIGH);
//    digitalWrite(ClutchOut, HIGH);
//    digitalWrite(ClutchIn, LOW);
//    delay(500);
//  }
//  else 
//   digitalWrite(backwards,HIGH);
//   digitalWrite(forwards,HIGH);
//   digitalWrite(ClutchIn,HIGH);
//   digitalWrite(ClutchOut,HIGH);
}

void initalize()
{
}

void retrackGear(int sec)
{
  digitalWrite(forwards,LOW);
  digitalWrite(backwards,HIGH);
  delay(sec);
}

void moveGearToCenter(int sec)
{
  digitalWrite(forwards,HIGH);
  digitalWrite(backwards,LOW);
  delay(sec);
}

