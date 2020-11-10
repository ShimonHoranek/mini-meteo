//include libraries
#include "U8glib.h"
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

//define pin and type
#define pinDHT 5
#define typeDHT11 DHT11

//initialize sensors
Adafruit_BMP085 bmp180;
U8GLIB_SSD1306_128X32 Display(U8G_I2C_OPT_NONE);
DHT DHTsensor(pinDHT, typeDHT11);

void setup(void) {
  //rotate content by 180 deg
  Display.setRot180();
  //start sensors
  DHTsensor.begin();
  bmp180.begin();
}

void loop() {
  //measure data and corrections
  float temp = (((DHTsensor.readTemperature() + bmp180.readTemperature()) / 2) - 4);
  float hum = DHTsensor.readHumidity() + 5;
  float pres = (bmp180.readPressure() / 100.00);

  Display.firstPage();
  do {
    draw(temp, hum, pres);
  } while (Display.nextPage());
}
void draw(float temp, float hum, float pres) {
  //display content
  Display.setFont(u8g_font_unifont);
  Display.setPrintPos(0, 10);
  Display.print(temp);
  Display.setPrintPos(80, 10);
  Display.print(hum);
  Display.setPrintPos(30, 25);
  Display.print(pres);
}
