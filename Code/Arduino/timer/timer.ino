const int hallPin = 7;     // the number of the hall effect sensor pin
int hallState1 = 0;          // variable for reading the hall sensor status
long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch
bool process_done = false;
void setup() {
Serial.begin(9600);

pinMode(hallPin, INPUT); // initialize the hall effect sensor pin as an input:


}

void loop() {

  
  // read the state of the hall effect sensor:
  hallState1 = digitalRead(hallPin);
  
  if (hallState1 == LOW)
  {     
    // Store the start time
    startTime = micros();
  } 
  else if (hallState1 == HIGH)
  {
    // Store the elapsed time
    elapsedTime = micros() - startTime;
     Serial.print("time_elapsed: ");
  Serial.println(elapsedTime);
  }

 


}
