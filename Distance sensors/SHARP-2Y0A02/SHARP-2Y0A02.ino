/*
   getDistance

   Example of using SharpIR library to calculate the distance beetween the sensor and an obstacle

   Created by Giuseppe Masino, 15 June 2016

   -----------------------------------------------------------------------------------

   Things that you need:
   - Arduino
   - A Sharp IR Sensor


   The circuit:
   - Arduino 5V -> Sensor's pin 1 (Vcc)
   - Arduino GND -> Sensor's pin 2 (GND)
   - Arduino pin A0 -> Sensor's pin 3 (Output)


   See the Sharp sensor datasheet for the pin reference, the pin configuration is the same for all models.
   There is the datasheet for the model GP2Y0A41SK0F:

   http://www.robotstore.it/open2b/var/product-files/78.pdf

*/

//import the library in the sketch
#include <SharpIR.h>

//Create a new instance of the library
//Call the sensor "sensor"
//The model of the sensor is "GP2YA41SK0F"
//The sensor output pin is attached to the pin A0
SharpIR sensor( SharpIR::GP2Y0A02YK0F, A5);


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


void setup()
{
  Serial.begin( 9600 ); //Enable the serial comunication
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
 // delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(2);

  display.setTextColor(SSD1306_WHITE);

}

void loop()
{
  int distance = sensor.getDistance(); //Calculate the distance in centimeters and store the value in a variable

  Serial.println( distance ); //Print the value to the serial monitor
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Distance = ");
  display.print(distance);
  display.println(" CM");
  display.display();
  // Serial.println(analogRead(A0));
}
