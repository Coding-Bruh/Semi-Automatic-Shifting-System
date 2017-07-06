  const int forwards = 2;
  const int backwards = 4;
  const int up = 0;
  const int down = 1;
  int RPM_Pin = 0;
  bool shiftup = 0;
  bool shiftdown = 0;
  const int ClutchOutsert = 8;
  const int ClutchInsert = 7;
  int RPM;

void setup() {

pinMode(forwards, OUTPUT);//Set relay as an output
pinMode(backwards, OUTPUT);//Set relay as an output
pinMode(ClutchInsert, OUTPUT);
pinMode(ClutchOutsert, OUTPUT);
pinMode(up, INPUT);
pinMode(down, INPUT);
pinMode(RPM_Pin, INPUT);
Serial.begin(19200);

}

void loop() 
{
  RPM = analogRead(RPM_Pin);

  int num = analogRead(up);
  int num2 = analogRead(down);
  Serial.println(num2);
  if(num > 900)
  {
    digitalWrite(ClutchOutsert, LOW);
    digitalWrite(ClutchInsert, HIGH);
    delay(500);
    digitalWrite(forwards,HIGH);
    digitalWrite(backwards,LOW);
    delay(110);
    digitalWrite(forwards,LOW);
    digitalWrite(backwards,HIGH);
    delay(110);
    digitalWrite(forwards,HIGH);
    digitalWrite(backwards,HIGH);
    digitalWrite(ClutchOutsert, HIGH);
    digitalWrite(ClutchInsert, LOW);
    delay(500);
    
  }
  else
   digitalWrite(forwards,HIGH);
   digitalWrite(backwards,HIGH);
   digitalWrite(ClutchOutsert, HIGH);
   digitalWrite(ClutchInsert, HIGH);
  
  if(num2 > 900)
  {
    digitalWrite(ClutchOutsert, LOW);
    digitalWrite(ClutchInsert, HIGH);
    delay(500);
    digitalWrite(forwards,LOW);
    digitalWrite(backwards,HIGH);
    delay(110);
    digitalWrite(forwards,HIGH);
    digitalWrite(backwards,LOW);
    delay(110);
    digitalWrite(forwards,HIGH);
    digitalWrite(backwards,HIGH);
    digitalWrite(ClutchOutsert, HIGH);
    digitalWrite(ClutchInsert, LOW);
    delay(500);
  }
  else 
   digitalWrite(backwards,HIGH);
   digitalWrite(forwards,HIGH);
   digitalWrite(ClutchInsert,HIGH);
   digitalWrite(ClutchOutsert,HIGH);
}
 

