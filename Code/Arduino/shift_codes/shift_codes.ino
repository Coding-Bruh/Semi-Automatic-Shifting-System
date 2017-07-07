  const int forwards = 12;
  const int backwards = 4;
  const int up = 0;
  const int down = 1;
  int RPM_Pin = 0;
  bool shiftup = 0;
  bool shiftdown = 0;
  const int ClutchOutsert = 8;
  const int ClutchInsert = 7;
  const int Position = 2;
  int POS;
  int RPM;

void setup() {

pinMode(forwards, OUTPUT);//Set relay as an output
pinMode(backwards, OUTPUT);//Set relay as an output
pinMode(ClutchInsert, OUTPUT);
pinMode(ClutchOutsert, OUTPUT);
pinMode(up, INPUT);
pinMode(down, INPUT);
pinMode(RPM_Pin, INPUT);
pinMode(Position, INPUT);
Serial.begin(19200);

}

void loop() 
{
  RPM = analogRead(RPM_Pin);
  POS = analogRead(Position);

  int num = analogRead(up);
  int num2 = analogRead(down);
  Serial.println(POS);
  if(num > 900)
  {
    digitalWrite(ClutchOutsert, LOW);
    digitalWrite(ClutchInsert, HIGH);
    POS = analogRead(Position);
    Serial.println(POS);
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
    Serial.println(POS);
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
    POS = analogRead(Position);
    Serial.println(POS);
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
    POS = analogRead(Position);
    Serial.println(POS);
    delay(500);
  }
  else 
   digitalWrite(backwards,HIGH);
   digitalWrite(forwards,HIGH);
   digitalWrite(ClutchInsert,HIGH);
   digitalWrite(ClutchOutsert,HIGH);
}
 

