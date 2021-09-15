#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int URPWM = 7; // PWM Output 0－25000US，Every 50US represent 1cm
int URTRIG = 8; // PWM trigger pin
unsigned int Distance = 0;
uint8_t EnPwmCmd[4] = {0x44, 0x02, 0xbb, 0x01}; // distance measure command

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  PWM_Mode_Setup();

}

void loop() {

  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH); // reading Pin PWM will output pulses
  unsigned long DistanceMeasured = pulseIn(URPWM, LOW);
  if (DistanceMeasured == 50000) { // the reading is invalid.
    Serial.print("Invalid");
  }
  else {
    Distance = DistanceMeasured / 50; // every 50us low level stands for 1cm
  }

  lcd.setCursor(0, 0);
  lcd.print("Distance = ");
  lcd.setCursor(0, 1);
  lcd.print(Distance);
  lcd.print("       ");
  lcd.setCursor(13, 1);
  lcd.print(" cm");
  delay(10);
}



void PWM_Mode_Setup() {

  pinMode(URTRIG, OUTPUT); // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG, HIGH); // Set to HIGH
  pinMode(URPWM, INPUT); // Sending Enable PWM mode command
  for (int i = 0; i < 4; i++) {
    Serial.write(EnPwmCmd[i]);
  }
}
