#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <Hx711.h>
Hx711 scale(A2, A3);

#include <Servo.h>
Servo myservo;

const int LED = A1;
const int butMove = 6;
const int butSel = 7;
int butMoveState = 0;
int prevbutMove = 0;
int butSelState = 0;
int prevbutSel = 0;
int weight = 0;
bool coarse = false;
const int coarseTime = 5000;
bool fine = false;
const int fineTime = 10000;
bool flag = true;
bool flag2 = false;
bool flag3 = false;

void setup() {
  myservo.attach(A0);
  lcd.begin(16, 2);
  pinMode(butMove, INPUT);
  pinMode(butSel, INPUT);
  pinMode(LED, OUTPUT);

}

void loop() {
  lcd.clear();
  lcd.print("Fine *");

  lcd.setCursor(0, 1);
  lcd.print("Coarse");
  while (flag) {

    butMoveState = digitalRead(butMove);
    butSelState = digitalRead(butSel);
    delay(200);

    if (butSelState != prevbutSel) {
      coarse = true;
      lcd.clear();
      lcd.print(weight);
      lcd.setCursor(2, 0);
      lcd.print("g");


      flag = false;
      flag2 = true;

    } else if (butMoveState != prevbutMove) {
      lcd.clear();
      lcd.print("Fine");

      lcd.setCursor(0, 1);
      lcd.print("Coarse *");
      flag = false;
      flag3 = true;

    }
  }
  while (flag3) {

    butMoveState = digitalRead(butMove);
    butSelState = digitalRead(butSel);
    delay(200);

    if (butSelState != prevbutSel) {
      flag3 = false;
      flag2 = true;
      fine = true;
      lcd.clear();
      lcd.print(weight);
      lcd.setCursor(2, 0);
      lcd.print("g");

    }
  }
  delay(1000);

  while (flag2) {
    butMoveState = digitalRead(butMove);
    delay(200);

    if (butMoveState != prevbutMove) {
      weight++;
      lcd.clear();
      lcd.print(weight);
      lcd.setCursor(2, 0);
      lcd.print("g");

    }
    butSelState = digitalRead(butSel);
    delay(200);

    if (butSelState != prevbutSel) {
      flag2 = false;

    }

  }
  if (weight != 0) {
    lcd.clear();
    lcd.print("load beans");
    flag2 = true;
  }

  while (flag2) {
    butMoveState = digitalRead(butMove);
    butSelState = digitalRead(butSel);
    delay(200);

    if (scale.getGram() >= weight) {

      digitalWrite(LED, HIGH);

    }
    if (butSelState != prevbutSel) {
      digitalWrite(LED, LOW);
      flag2 = false;
    }
  }


  if (weight != 0) {

    myservo.write(180);
    delay(15);

  }

  if (coarse) {
    delay(coarseTime);
  } else if (fine) {
    delay(fineTime);
  }
  if (weight != 0) {

    myservo.write(90);
    delay(15);

  }
  weight = 0;
  flag = true;
  flag2 = false;
  flag3 = false;
  coarse = false;
  fine = false;
  prevbutMove = butMoveState = 0;
  prevbutSel = butSelState = 0;

}
