#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(16,02);
  lcd.clear();
  lcd.setBacklight(HIGH);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("LCD 1602 I2C");

  lcd.setCursor(0,1);
  lcd.print("hello");

  delay(2000);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("cyka");

  lcd.setCursor(0,1);
  lcd.print("blyat");

  delay(2000);

}
