#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

float value = 0;
float rev = 0;
int rpm;
int oldtime = 0;
int time;

void isr() {
  rev++;
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  attachInterrupt(0, isr, RISING);
}

void loop() {
  delay(1000);
  detachInterrupt(0);
  time = millis() - oldtime;
  rpm = (rev / time) * 60000 / 4;
  oldtime = millis();
  rev = 0;
  float velocity = (rpm*2*3.14/60)*0.11;
  Serial.print("RPM:");
  Serial.print(rpm);
  Serial.println();
  Serial.print("Velocity:");
  Serial.print(velocity);
  Serial.print(" m/s");
  Serial.println(); 

  // lcd.setCursor(0, 0);
  // lcd.print("Speed: ");
  // lcd.print(velocity);
  // lcd.print("  m/s");
  // Serial.println(velocity);
  
  // lcd.clear();
  
  attachInterrupt(0, isr, RISING);
}
