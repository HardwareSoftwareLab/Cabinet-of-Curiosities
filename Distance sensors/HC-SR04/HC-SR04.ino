#include <SoftwareSerial.h>
SoftwareSerial Serial7Segment(9, 8); //RX pin, TX pin

const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const unsigned int MAX_DIST = 23200;

unsigned long t1;
unsigned long t2;
unsigned long pulse_width;
int mm;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  while ( digitalRead(ECHO_PIN) == 0 );

  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  mm = int(pulse_width / 5.8);

  char tempString[10]; //Used for sprintf
  mm = constrain(mm, 0, 9999);
  sprintf(tempString, "%4d", mm); //Convert deciSecond into a string that is right adjusted
  Serial.println(tempString);

  Serial7Segment.print(tempString); //Send serial string out the soft serial port to the S7S
  delay(10);
}
