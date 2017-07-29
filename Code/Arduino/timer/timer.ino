const int hallPin1 = 7;     // the number of the hall effect sensor pin
const int hallPin2 = 8;     // the number of the hall effect sensor pin
int hallState1 = 0;         // variable for reading the hall sensor status
int hallState2 = 0;         // variable for reading the hall sensor status
long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch
void setup() {
Serial.begin(9600);

pinMode(hallPin1, INPUT); // initialize the hall effect sensor pin as an input
pinMode(hallPin2, INPUT); // initialize the hall effect sensor pin as an input


}

void loop() {

  
  // read the state of the hall effect sensor:
  hallState1 = digitalRead(hallPin1);
  hallState2 = digitalRead(hallPin2);
  
  if (hallState1 == LOW)
  {     
    // Store the start time
    startTime = micros();
  } 
  if (hallState2 == LOW)
  {
    // Store the elapsed time
    elapsedTime = micros() - startTime;
     Serial.print("time_elapsed: ");
  Serial.println(elapsedTime);
  }

 


}
