/******************************************************************************
  Project  : HotWheels Race track
  Compiler : Arduino 1.6.7
  Board    : Arduino Nano
  Shield   : -
  Module   : LCD i2c, Laser dioad, LDR
  Author   : Bavensky :3
  E-Mail   : Aphirak_Sang-ngenchai@hotmail.com
  Date     : 11/03/2016 [dd/mm/yyyy]
*******************************************************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// define button and sensor
#define signal1 A0
#define signal2 A1
#define signal3 A2
#define signal4 A3
#define pin_start 7
#define pin_reset 6
//
#define debounce 20
#define holdTime 2000
int buttonVal = 0;
int buttonLast = 0;
unsigned long btnDnTime;
unsigned long btnUpTime;
boolean ignoreUp = false;
int modepush = 0, modehold = 0;
int displaymanu = 1;
float _speed1, _speed2, _speed3, _speed4;

unsigned long timecount = 0;
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
  pinMode(pin_start, INPUT);
  pinMode(pin_reset, INPUT);
}

void loop() {
  while (displaymode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("HotWheels Race track");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("    by hohm cafe    ");
    lcd.setCursor(0, 3);
    lcd.print("   Ready to Race !  ");

    if (digitalRead(pin_start) == LOW)  {
      startTime1 = micros();
      startTime2 = micros();
      startTime3 = micros();
      startTime4 = micros();

      lcd.setCursor(0, 0);
      lcd.print("HotWheels Race track");
      lcd.setCursor(0, 1);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("    by hohm cafe    ");
      lcd.setCursor(0, 3);
      lcd.print("       Start !      ");
      displaymode = 2;
    }
  }
  while (displaymode == 2) {
    nowTime1 = micros();
    nowTime2 = micros();
    nowTime3 = micros();
    nowTime4 = micros();

    if (analogRead(A0) >= 20 && road1 == false)  {
      time1 = nowTime1 - startTime1;
      roadend += 1;
      order1 = roadend;
      orderup = order1;
      road1 = true;
    }
    if (analogRead(A1) >= 20 && road2 == false)  {
      time2 = nowTime2 - startTime2;
      roadend += 1;
      order2 = roadend;
      orderup = order2;
      road2 = true;
    }
    if (analogRead(A2) >= 20 && road3 == false)  {
      time3 = nowTime3 - startTime3;
      roadend += 1;
      order3 = roadend;
      orderup = order3;
      road3 = true;
    }
    if (analogRead(A3) >= 45 && road4 == false)  {
      time4 = nowTime4 - startTime4;
      roadend += 1;
      order4 = roadend;
      orderup = order4;
      road4 = true;
    }

    //    Serial.print(analogRead(A0)); Serial.print("  ");
    //    Serial.print(analogRead(A1)); Serial.print("  ");
    //    Serial.print(analogRead(A2)); Serial.print("  ");
    //    Serial.println(analogRead(A3));
    //
    //    Serial.print(time1); Serial.print("  ");
    //    Serial.print(time2); Serial.print("  ");
    //    Serial.print(time3); Serial.print("  ");
    //    Serial.println(time4);

    if (road1 == true || road2 == true || road3 == true || road4 == true)  {
      timecount += 1;
      if (timecount >= 5000)  {
        lcd.clear();
        if (order1 == 1) {
          lcd.setCursor(0, 0);
          lcd.print("The winer is :      ");
          lcd.setCursor(0, 1);
          lcd.print("   Number =         ");
          numberone();
        }
        else if (order2 == 1) {
          lcd.setCursor(0, 0);
          lcd.print("The winer is :      ");
          lcd.setCursor(0, 1);
          lcd.print("   Number =         ");
          numbertwo();
        }
        else if (order3 == 1) {
          lcd.setCursor(0, 0);
          lcd.print("The winer is :      ");
          lcd.setCursor(0, 1);
          lcd.print("   Number =         ");
          numberthree();
        }
        else if (order4 == 1) {
          lcd.setCursor(0, 0);
          lcd.print("The winer is :      ");
          lcd.setCursor(0, 1);
          lcd.print("   Number =         ");
          numberfour();
        }
        delay(2000);
        displaymode = 3;
        timecount = 0;
      }
    }

    if (digitalRead(pin_reset) == LOW)  {
      roadend = 0; orderup = 0;
      time1 = 0; road1 = false;
      time2 = 0; road2 = false;
      time3 = 0; road3 = false;
      time4 = 0; road4 = false;
      timecount = 0;
      displaymode = 1;
      lcd.clear();
    }
  }

  while (displaymode == 3) {
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
    displaymode = 4;
    lcd.clear();
  }

  while (displaymode == 4) {
    event1();
    buttonVal = digitalRead(pin_reset);
    if (buttonVal == LOW && buttonLast == HIGH && (millis() - btnUpTime) > long(debounce))
    {
      btnDnTime = millis();
    }

    if (buttonVal == HIGH && buttonLast == LOW && (millis() - btnDnTime) > long(debounce))
    {
      if (ignoreUp == false)  {
        modepush += 1;  
      }
      else ignoreUp = false;
      btnUpTime = millis();
    }

    if (buttonVal == LOW && (millis() - btnDnTime) > long(holdTime))
    {
      event2();
      ignoreUp = true;

      btnDnTime = millis();
    }

    buttonLast = buttonVal;
  }

  while (displaymode == 5) {
    lcd.setCursor(0, 0);
    lcd.print("HotWheels Race track");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("    by hohm cafe    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    if (digitalRead(pin_start) == HIGH)  { //HIGH
      roadend = 0; orderup = 0;
      time1 = 0; road1 = false;
      time2 = 0; road2 = false;
      time3 = 0; road3 = false;
      time4 = 0; road4 = false;
      _speed1 = 0; _speed2 = 0;
      _speed3 = 0; _speed4 = 0;
      timecount = 0;
      modepush = 1;
      lcd.clear();
      displaymode = 1;
    }
  }
} // end loop

// event to display
void event1() {
  if (modepush == 1)  {
    lcd.setCursor(0, order1 - 1);
    if (road1 == true) {
      lcd.print(order1);
      lcd.print(")  T.1  ");
      lcd.print(time1 / 1000000.000 , 4);
      lcd.print(" s. ");
    }
    if (road1 == false) {
      lcd.print(order1);
      lcd.print(")  T.1  -.---- s.");
    }

    lcd.setCursor(0, order2 - 1);
    if (road2 == true) {
      lcd.print(order2);
      lcd.print(")  T.2  ");
      lcd.print(time2 / 1000000.000 , 4);
      lcd.print(" s. ");
    }
    if (road2 == false) {
      lcd.print(order2);
      lcd.print(")  T.2  -.---- s.");
    }

    lcd.setCursor(0, order3 - 1);
    if (road3 == true) {
      lcd.print(order3);
      lcd.print(")  T.3  ");
      lcd.print(time3 / 1000000.000 , 4);
      lcd.print(" s. ");
    }
    if (road3 == false) {
      lcd.print(order3);
      lcd.print(")  T.3  -.---- s.");
    }

    lcd.setCursor(0, order4 - 1);
    if (road4 == true) {
      lcd.print(order4);
      lcd.print(")  T.4  ");
      lcd.print(time4 / 1000000.000 , 4);
      lcd.print(" s. ");
    }
    if (road4 == false) {
      lcd.print(order4);
      lcd.print(")  T.4  -.---- s.");
    }
  }
  if (modepush == 2)  {
    _speed1 = (float)((((12 / (float)(time1 / 1000000.000)) * 3600) / 1000) * 64);
    _speed2 = (float)((((12 / (float)(time2 / 1000000.000)) * 3600) / 1000) * 64);
    _speed3 = (float)((((12 / (float)(time3 / 1000000.000)) * 3600) / 1000) * 64);
    _speed4 = (float)((((12 / (float)(time4 / 1000000.000)) * 3600) / 1000) * 64);

    lcd.setCursor(0, order1 - 1);
    if (road1 == true) {
      lcd.print(order1);
      lcd.print(")  T.1  ");
      lcd.print(_speed1, 0);
      lcd.print(" km/h");
    }
    if (road1 == false) {
      lcd.print(order1);
      lcd.print(")  T.1  --- km/h  ");
    }

    lcd.setCursor(0, order2 - 1);
    if (road2 == true) {
      lcd.print(order2);
      lcd.print(")  T.2  ");
      lcd.print(_speed2, 0);
      lcd.print(" km/h");
    }
    if (road2 == false) {
      lcd.print(order2);
      lcd.print(")  T.2  --- km/h  ");
    }

    lcd.setCursor(0, order3 - 1);
    if (road3 == true) {
      lcd.print(order3);
      lcd.print(")  T.3  ");
      lcd.print(_speed3, 0);
      lcd.print(" km/h");
    }
    if (road3 == false) {
      lcd.print(order3);
      lcd.print(")  T.3  --- km/h  ");
    }

    lcd.setCursor(0, order4 - 1);
    if (road4 == true) {
      lcd.print(order4);
      lcd.print(")  T.4  ");
      lcd.print(_speed4, 0);
      lcd.print(" km/h");
    }
    if (road4 == false) {
      lcd.print(order4);
      lcd.print(")  T.4  --- km/h  ");
    }
    modepush = 0;
  }

//  if (modepush == 3)  {
//    lcd.setCursor(0, order1 - 1);
//    if (road1 == true) {
//      lcd.print(order1);
//      lcd.print(">Lane1= ");
//      lcd.print(time1 / 1000000.000 , 5);
//      lcd.print(" s.");
//    }
//    if (road1 == false) {
//      lcd.print(order1);
//      lcd.print(">Lane1= -.-- s.");
//    }
//
//    lcd.setCursor(0, order2 - 1);
//    if (road2 == true) {
//      lcd.print(order2);
//      lcd.print(">Lane2= ");
//      lcd.print(time2 / 1000000.000 , 5);
//      lcd.print(" s.");
//    }
//    if (road2 == false) {
//      lcd.print(order2);
//      lcd.print(">Lane2= -.-- s.");
//    }
//
//    lcd.setCursor(0, order3 - 1);
//    if (road3 == true) {
//      lcd.print(order3);
//      lcd.print(">Lane3= ");
//      lcd.print(time3 / 1000000.000 , 5);
//      lcd.print(" s.");
//    }
//    if (road3 == false) {
//      lcd.print(order3);
//      lcd.print(">Lane3= -.-- s.");
//    }
//
//    lcd.setCursor(0, order4 - 1);
//    if (road4 == true) {
//      lcd.print(order4);
//      lcd.print(">Lane4= ");
//      lcd.print(time4 / 1000000.000 , 5);
//      lcd.print(" s.");
//    }
//    if (road4 == false) {
//      lcd.print(order4);
//      lcd.print(">Lane4= -.-- s.");
//    }
//    Serial.print("RANG1 = ");
//    Serial.print((float)(time1 - time1) / 1000000.000);
//    Serial.print(" s. && ");
//    Serial.print("RANG2 = ");
//    Serial.print((float)(time2 - time1) / 1000000.000);
//    Serial.println(" s.");
//    modepush = 1;
//  }

} // end event1

void event2() {
  //  if (modehold == 1) {
  Serial.println(" END ");
  //    modehold = 0;
  displaymode = 5;
  //  }
} // end event2

// Create Number Character
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

