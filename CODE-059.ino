//VTM https://www.youtube.com/c/VTMVlogVoThongMinh
#include <LiquidCrystal.h>
#include <DFR_LCD_Keypad.h>
#include <EEPROM.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
DFR_LCD_Keypad keypad(A0, &lcd);
const int stepPin = 2; //clk+
const int dirPin = 3; //cw+
int last_key, key;
int time1 = EEPROM.read(0);
int s = EEPROM.read(1); //distance
///////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("-----RESET-----");
  delay(1000);
  lcd.clear();
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
/////////////////////////////////////////
void loop()
{
  last_key = keypad.get_last_key();
  key      = keypad.read_key();
  if (key != last_key) {
    lcd.clear();

    switch (key) {
      case KEY_RIGHT:
        lcd.setCursor(0, 0);
        lcd.print("Distance:");
        lcd.setCursor(13, 0);
        lcd.print("(r)");
        lcd.setCursor(0, 1);
        lcd.print("Speed:");
        lcd.setCursor(11, 1);
        lcd.print("(r/s)");
        lcd.setCursor(7, 1);
        lcd.print(time1);
        s = s + 1;
        key = keypad.read_key();
        lcd.setCursor(10, 0);
        lcd.print(s);
        break;

      case KEY_UP:
        lcd.setCursor(0, 0);
        lcd.print("Distance:");
        lcd.setCursor(13, 0);
        lcd.print("(r)");
        lcd.setCursor(0, 1);
        lcd.print("Speed:");
        lcd.setCursor(11, 1);
        lcd.print("(r/s)");
        lcd.setCursor(10, 0);
        lcd.print(s);
        time1 = time1 + 1;
        key = keypad.read_key();
        lcd.setCursor(7, 1);
        lcd.print(time1);
        break;

      case KEY_DOWN:
        if (time1 > 0) {
          lcd.setCursor(0, 0);
          lcd.print("Distance:");
          lcd.setCursor(13, 0);
          lcd.print("(r)");
          lcd.setCursor(0, 1);
          lcd.print("Speed:");
          lcd.setCursor(11, 1);
          lcd.print("(r/s)");
          lcd.setCursor(10, 0);
          lcd.print(s);
          time1 = time1 - 1;
          key = keypad.read_key();
          lcd.setCursor(7, 1);
          lcd.print(time1);
        }
        break;

      case KEY_LEFT:
        if (s > 0)
        {
          lcd.setCursor(0, 0);
          lcd.print("Distance:");
          lcd.setCursor(13, 0);
          lcd.print("(r)");
          lcd.setCursor(0, 1);
          lcd.print("Speed:");
          lcd.setCursor(11, 1);
          lcd.print("(r/s)");
          lcd.setCursor(7, 1);
          lcd.print(time1);
          s = s - 1;
          key = keypad.read_key();
          lcd.setCursor(10, 0);
          lcd.print(s);
        }
        break;

      case KEY_NONE:
      default:
        lcd.setCursor(0, 0);
        lcd.print("Distance:");
        lcd.setCursor(13, 0);
        lcd.print("(r)");
        lcd.setCursor(10, 0);
        lcd.print(s);
        lcd.setCursor(0, 1);
        lcd.print("Speed:");
        lcd.setCursor(11, 1);
        lcd.print("(r/s)");
        lcd.setCursor(7, 1);
        lcd.print(time1);
        EEPROM.write(0, time1);
        EEPROM.write(1, s);
        break;
    }
  }
  if (key == KEY_SELECT)
  {
A:
    for (int x = 0; x < s * 400; x++)
    {
      digitalWrite(dirPin, HIGH);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1250 / time1);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1250 / time1);
    }
    delay(800);
    for (int x = 0; x < s * 400; x++)
    {
      digitalWrite(dirPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1250 / time1);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1250 / time1);
    }
    delay(800);
    goto A;
  }
}
