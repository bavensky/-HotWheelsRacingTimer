
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define signal1 2 // int.3
#define signal2 3 // int.1
#define signal3 4 // int.0
#define signal4 5 // int.4
#define pin_start 6
#define pin_reset 7

int roadend = 0, displaymode = 1;
int order1, order2, order3, order4;
unsigned long time1, time2, time3, time4;
unsigned long pevTime1 = 0, pevTime2 = 0, pevTime3 = 0, pevTime4 = 0;
unsigned long startTime1 = 0, startTime2 = 0, startTime3 = 0, startTime4 = 0;
unsigned long nowTime1, nowTime2, nowTime3, nowTime4;

boolean road1 = false, road2 = false, road3 = false, road4 = false;

void setup() {
  lcd.begin();
  Serial.begin(9600);
  delay(1000);
  lcd.backlight();

  pinMode(signal1, INPUT);
  pinMode(signal2, INPUT);
  pinMode(signal3, INPUT);
  pinMode(signal4, INPUT);
  pinMode(pin_start, INPUT_PULLUP);
  pinMode(pin_reset, INPUT_PULLUP);
}

void loop() {

  switch (displaymode) {
    case 1:    // Main Display
      lcd.setCursor(0, 0);
      lcd.print("  Hot Wheels track  ");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("Let's Start to race~");

      if (digitalRead(pin_start) == HIGH)  {
        lcd.clear();
        startTime1 = micros();
        startTime2 = micros();
        startTime3 = micros();
        startTime4 = micros();
        displaymode = 2;
      }
      break;

    case 2:   // Stop watch
      nowTime1 = micros();
      nowTime2 = micros();
      nowTime3 = micros();
      nowTime4 = micros();

      if (digitalRead(signal1) == 0 && road1 == false)  {
        time1 = nowTime1 - startTime1;
        roadend++;
        order1 = roadend;
        road1 = true;
      }
      if (digitalRead(signal2) == 0 && road2 == false)  {
        time2 = nowTime2 - startTime2;
        roadend++;
        order2 = roadend;
        road2 = true;
      }
      if (digitalRead(signal3) == 0 && road3 == false)  {
        time3 = nowTime3 - startTime3;
        roadend++;
        order3 = roadend;
        road3 = true;
      }
      if (digitalRead(signal4) == 0 && road4 == false)  {
        time4 = nowTime4 - startTime4;
        roadend++;
        order4 = roadend;
        road4 = true;
      }

      lcd.setCursor(0, 0);
      lcd.print("Lane 1 : ");
      lcd.print(time1 / 1000000.0 , 6);
      lcd.setCursor(0, 1);
      lcd.print("Lane 2 : ");
      lcd.print(time2 / 1000000.0 , 6);
      lcd.setCursor(0, 2);
      lcd.print("Lane 3 : ");
      lcd.print(time3 / 1000000.0 , 6);
      lcd.setCursor(0, 3);
      lcd.print("Lane 4 : ");
      lcd.print(time4 / 1000000.0 , 6);
      
      if (digitalRead(pin_reset) == LOW) {  // reset all variable
        displaymode = 1;
        roadend = 0;
        time1 = 0; road1 = false;
        time2 = 0; road2 = false;
        time3 = 0; road3 = false;
        time4 = 0; road4 = false;
        lcd.clear();
      }
      
      if (roadend >= 4) {
        delay(2000);
        lcd.clear();
        displaymode = 3;
      }
      break;

    case 3:   // Show car winer
      lcd.setCursor(0, 0);
      lcd.print("The winer is :      ");
      lcd.setCursor(0, 1);
      lcd.print("   Number =  ");
      lcd.setCursor(0, 2);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      delay(2000);
      displaymode = 4;
      lcd.clear();
      break;

    case 4:   // Show stop watch and order
      lcd.setCursor(0, order1 - 1);
      lcd.print(order1);
      lcd.print(")");
      lcd.print("Lane1 = ");
      lcd.print(time1 / 1000000.0 , 6);
      lcd.print("s");

      lcd.setCursor(0, order2 - 1);
      lcd.print(order2);
      lcd.print(")");
      lcd.print("Lane2 = ");
      lcd.print(time2 / 1000000.0 , 6);
      lcd.print("s");

      lcd.setCursor(0, order3 - 1);
      lcd.print(order3);
      lcd.print(")");
      lcd.print("Lane3 = ");
      lcd.print(time3 / 1000000.0 , 6);
      lcd.print("s");

      lcd.setCursor(0, order4 - 1);
      lcd.print(order4);
      lcd.print(")");
      lcd.print("Lane4 = ");
      lcd.print(time4 / 1000000.0 , 6);
      lcd.print("s");

      if (digitalRead(pin_reset) == LOW) {  // reset all variable
        displaymode = 1;
        roadend = 0;
        time1 = 0; road1 = false;
        time2 = 0; road2 = false;
        time3 = 0; road3 = false;
        time4 = 0; road4 = false;
        lcd.clear();
      }
      break;
  }
}

