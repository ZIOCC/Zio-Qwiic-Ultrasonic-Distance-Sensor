// Zio_Ultrasonic_Distance_Sensor_IIC_Test

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SLAVE_BROADCAST_ADDR 0x00  //default address
#define SLAVE_ADDR 0x00       //SLAVE_ADDR 0xA0-0xAF
uint8_t distance_H=0;
uint8_t distance_L=0;
uint16_t distance=0;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  Serial.println("IIC testing......");
  display.clearDisplay();
//  Wire.beginTransmission(SLAVE_BROADCAST_ADDR); // transmit to device SLAVE_BROADCAST_ADDR
//  Wire.write(SLAVE_ADDR);              // Change the SLAVE_ADDR
//  Wire.endTransmission();    // stop transmitting
}



void loop() {
  Wire.beginTransmission(SLAVE_ADDR); // transmit to device #8
  Wire.write(1);              // measure command: 0x01
  Wire.endTransmission();    // stop transmitting 
  
  Wire.requestFrom(SLAVE_ADDR, 2);    // request 6 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
  distance_H = Wire.read(); // receive a byte as character    
  distance_L = Wire.read();  
  distance = (uint16_t)distance_H<<8;
  distance = distance|distance_L; 
  Serial.print(distance);         // print the character
  Serial.println("mm"); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.print(distance);
  display.print("mm");
  display.display();
  delay(1);
  
  delay(100);
 }
}

