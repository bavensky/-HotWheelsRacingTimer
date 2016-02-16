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
int order1, order2, order3, order4, orderup = 1;
unsigned long time1, time2, time3, time4;
unsigned long pevTime1 = 0, pevTime2 = 0, pevTime3 = 0, pevTime4 = 0;
unsigned long startTime1 = 0, startTime2 = 0, startTime3 = 0, startTime4 = 0;
unsigned long nowTime1, nowTime2, nowTime3, nowTime4;

boolean road1 = false, road2 = false, road3 = false, road4 = false;
unsigned long previousMillis;

//===============================================================================
byte Charator1[] = {28, 30, 31, 31, 31, 31, 31, 31};
byte Charator2[] = {31, 31, 31, 31, 31, 31, 30, 28};
byte Charator3[] = {31, 31, 31, 31, 31, 31, 15, 7};
byte Charator4[] = {31, 31, 31, 0, 0, 0, 0, 0};
byte Charator5[] = {0, 0, 0, 0, 0, 31, 31, 31};
byte Charator6[] = {31, 31, 31, 0, 0, 0, 31, 31};
byte Charator7[] = {31, 31, 31, 31, 31, 31, 31, 31};
//===============================================================================

void setup() {
  lcd.begin();
  Serial.begin(115200);
  delay(1000);
  lcd.backlight();

  lcd.createChar(0, Charator1);
  lcd.createChar(1, Charator2);
  lcd.createChar(2, Charator3);
  lcd.createChar(3, Charator4);
  lcd.createChar(4, Charator5);
  lcd.createChar(5, Charator6);
  lcd.createChar(6, Charator7);

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
      lcd.print("HotWheels Race track");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("    by hohm cafe    ");
      lcd.setCursor(0, 3);
      lcd.print("   Ready to Race !  ");

      if (digitalRead(pin_start) == HIGH)  {
        startTime1 = micros();
        startTime2 = micros();
        startTime3 = micros();
        startTime4 = micros();
        previousMillis = millis();
        displaymode = 2;
      }
      break;

    case 2:   // Stop watch
      lcd.setCursor(0, 0);
      lcd.print("HotWheels Race track");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("    by hohm cafe    ");
      lcd.setCursor(0, 3);
      lcd.print("       Start !      ");

      nowTime1 = micros();
      nowTime2 = micros();
      nowTime3 = micros();
      nowTime4 = micros();

      if (digitalRead(signal1) == 0 && road1 == false)  {
        time1 = nowTime1 - startTime1;
        roadend += 1;
        order1 = roadend;
        orderup = order1;
        road1 = true;
      }
      if (digitalRead(signal2) == 0 && road2 == false)  {
        time2 = nowTime2 - startTime2;
        roadend += 1;
        order2 = roadend;
        orderup = order2;
        road2 = true;
      }
      if (digitalRead(signal3) == 0 && road3 == false)  {
        time3 = nowTime3 - startTime3;
        roadend += 1;
        order3 = roadend;
        orderup = order3;
        road3 = true;
      }
      if (digitalRead(signal4) == 0 && road4 == false)  {
        time4 = nowTime4 - startTime4;
        roadend += 1;
        order4 = roadend;
        orderup = order4;
        road4 = true;
      }

      Serial.print(time1); Serial.print("  ");
      Serial.print(time2); Serial.print("  ");
      Serial.print(time3); Serial.print("  ");
      Serial.println(time4);

      if (roadend >= 4) {
        lcd.clear();
        displaymode = 3;
      }

      if (road1 == true || road2 == true || road3 == true || road4 == true)  {
        unsigned long countdown = millis();
        if (countdown - previousMillis >= 5000) {
          Serial.print("roadend ");
          Serial.print(roadend); Serial.print("  ");
          Serial.print(time1); Serial.print("  ");
          Serial.print(time2); Serial.print("  ");
          Serial.print(time3); Serial.print("  ");
          Serial.println(time4);
          Serial.print(order1); Serial.print("  ");
          Serial.print(order2); Serial.print("  ");
          Serial.print(order3); Serial.print("  ");
          Serial.print(order4); Serial.print("  ");
          Serial.println(orderup);

          lcd.clear();
          displaymode = 3;
          previousMillis = countdown;
        }
      }

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

    case 3:   // Show car winer
      if (road1 == false)  {
        time1 = 999999999;
        if (orderup < 4)  {
          orderup += 1;
          order1 = orderup;
        }
      }
      if (road2 == false)  {
        time2 = 999999999;
        if (orderup < 4)  {
          orderup += 1;
          order2 = orderup;
        }
      }
      if (road3 == false)  {
        time3 = 999999999;
        if (orderup < 4)  {
          orderup += 1;
          order3 = orderup;
        }
      }
      if (road4 == false)  {
        time4 = 999999999;
        if (orderup < 4)  {
          orderup += 1;
          order4 = orderup;
        }
      }

      Serial.print(time1); Serial.print("  ");
      Serial.print(time2); Serial.print("  ");
      Serial.print(time3); Serial.print("  ");
      Serial.println(time4);
      Serial.print(order1); Serial.print("  ");
      Serial.print(order2); Serial.print("  ");
      Serial.print(order3); Serial.print("  ");
      Serial.print(order4); Serial.print("  ");
      Serial.print(" road");
      Serial.print(road1);
      Serial.print(road2);
      Serial.print(road3);
      Serial.print(road4);

      lcd.setCursor(0, 0);
      lcd.print("The winer is :      ");
      lcd.setCursor(0, 1);
      lcd.print("   Number =         ");

      if (road1 == true && (time1 <= time2 && time1 <= time3 && time1 <= time4))  {
        numberone();
      }
      else if (road2 == true && (time2 <= time1 && time2 <= time3 && time2 <= time4)) {
        numbertwo();
      }
      else if (road3 == true && (time3 <= time1 && time3 <= time2 && time3 <= time4)) {
        numberthree();
      }    
      else if (road4 == true && (time4 <= time1 && time4 <= time2 && time4 <= time3)) {
        numberfour();
      }

      delay(2000);
      displaymode = 4;
      lcd.clear();
      break;

    case 4:   // Show stop watch and order
      //      #1 = Lane3- 3.456 s.
      //      #2 = Lane1- 3.567 s.
      //      #3 = Lane2- 4.123 s.
      //      #4 = Lane4- -.--- s.

      lcd.setCursor(0, order1 - 1);
      if (road1 == true) {
        lcd.print("#");
        lcd.print(order1);
        lcd.print(" = Lane1- ");
        lcd.print(time1 / 1000000.000 , 3);
        lcd.print(" s.");
      }
      if (road1 == false) {
        lcd.print("#");
        lcd.print(order1);
        lcd.print(" = Lane1- -.-- s.");
      }

      lcd.setCursor(0, order2 - 1);
      if (road2 == true) {
        lcd.print("#");
        lcd.print(order2);
        lcd.print(" = Lane2- ");
        lcd.print(time2 / 1000000.000 , 3);
        lcd.print(" s.");
      }
      if (road2 == false) {
        lcd.print("#");
        lcd.print(order2);
        lcd.print(" = Lane2- -.-- s.");
      }

      lcd.setCursor(0, order3 - 1);
      if (road3 == true) {
        lcd.print("#");
        lcd.print(order3);
        lcd.print(" = Lane3- ");
        lcd.print(time3 / 1000000.000 , 3);
        lcd.print(" s.");
      }
      if (road3 == false) {
        lcd.print("#");
        lcd.print(order3);
        lcd.print(" = Lane3- -.-- s.");
      }

      lcd.setCursor(0, order4 - 1);
      if (road4 == true) {
        lcd.print("#");
        lcd.print(order4);
        lcd.print(" = Lane4- ");
        lcd.print(time4 / 1000000.000 , 3);
        lcd.print(" s.");
      }
      if (road4 == false) {
        lcd.print("#");
        lcd.print(order4);
        lcd.print(" = Lane4- -.-- s.");
      }


      if (digitalRead(pin_reset) == LOW) {  // reset all variable
        displaymode = 1;
        roadend = 0; orderup = 0;
        time1 = 0; road1 = false;
        time2 = 0; road2 = false;
        time3 = 0; road3 = false;
        time4 = 0; road4 = false;
        lcd.clear();
      }
      break;
  }
}
void numberone()  {
  lcd.setCursor(15, 0);
  lcd.write(byte(3));
  lcd.setCursor(16, 0);
  lcd.write(byte(3));
  lcd.setCursor(17, 0);
  lcd.write(byte(0));

  lcd.setCursor(17, 1);
  lcd.write(byte(6));

  lcd.setCursor(17, 2);
  lcd.write(byte(6));

  lcd.setCursor(15, 3);
  lcd.write(byte(4));
  lcd.setCursor(16, 3);
  lcd.write(byte(4));
  lcd.setCursor(17, 3);
  lcd.write(byte(6));
  lcd.setCursor(18, 3);
  lcd.write(byte(4));
  lcd.setCursor(19, 3);
  lcd.write(byte(4));
}
void numbertwo()  {
  lcd.setCursor(15, 0);
  lcd.write(byte(3));
  lcd.setCursor(16, 0);
  lcd.write(byte(3));
  lcd.setCursor(17, 0);
  lcd.write(byte(3));
  lcd.setCursor(18, 0);
  lcd.write(byte(0));

  lcd.setCursor(15, 1);
  lcd.write(byte(4));
  lcd.setCursor(16, 1);
  lcd.write(byte(4));
  lcd.setCursor(17, 1);
  lcd.write(byte(4));
  lcd.setCursor(18, 1);
  lcd.write(byte(6));

  lcd.setCursor(15, 2);
  lcd.write(byte(6));

  lcd.setCursor(15, 3);
  lcd.write(byte(2));
  lcd.setCursor(16, 3);
  lcd.write(byte(4));
  lcd.setCursor(17, 3);
  lcd.write(byte(4));
  lcd.setCursor(18, 3);
  lcd.write(byte(4));
}

void numberthree()  {
  lcd.setCursor(15, 0);
  lcd.write(byte(3));
  lcd.setCursor(16, 0);
  lcd.write(byte(3));
  lcd.setCursor(17, 0);
  lcd.write(byte(3));
  lcd.setCursor(18, 0);
  lcd.write(byte(0));

  lcd.setCursor(15, 1);
  lcd.write(byte(4));
  lcd.setCursor(16, 1);
  lcd.write(byte(4));
  lcd.setCursor(17, 1);
  lcd.write(byte(4));
  lcd.setCursor(18, 1);
  lcd.write(byte(6));

  lcd.setCursor(18, 2);
  lcd.write(byte(6));

  lcd.setCursor(15, 3);
  lcd.write(byte(4));
  lcd.setCursor(16, 3);
  lcd.write(byte(4));
  lcd.setCursor(17, 3);
  lcd.write(byte(4));
  lcd.setCursor(18, 3);
  lcd.write(byte(1));
}

void numberfour()  {
  lcd.setCursor(15, 0);
  lcd.write(byte(6));
  lcd.setCursor(18, 0);
  lcd.write(byte(6));

  lcd.setCursor(15, 1);
  lcd.write(byte(6));
  lcd.setCursor(18, 1);
  lcd.write(byte(6));

  lcd.setCursor(15, 2);
  lcd.write(byte(2));
  lcd.setCursor(16, 2);
  lcd.write(byte(4));
  lcd.setCursor(17, 2);
  lcd.write(byte(4));
  lcd.setCursor(18, 2);
  lcd.write(byte(6));

  lcd.setCursor(18, 3);
  lcd.write(byte(6));
}

