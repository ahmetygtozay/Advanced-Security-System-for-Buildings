#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include "icons.h"
#define NOTE_C6 1047
#define NOTE_D6 1175
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_G6 1568
#define NOTE_A6 1760
#define NOTE_B6 1976
#define NOTE_C7 2093
int j = 10000;
const int LED = 2;
const int SERVO_PIN = 6;
const int SERVO_UNLOCK_POS = 0;
const int SERVO_LOCK_POS = 90;
const int BUTTON_PIN = 13;
const int BUZZER_PIN = A4;
int maz = 0;
const int PIR_PIN = 1;
int enteredPassword;
bool look = false;
const int PASSWORD = 1721;
int PirRead;
Servo lockServo;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {5, 4, 3, A5};
byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

void lock() {
  lockServo.write(SERVO_LOCK_POS);

}

void unlock() {
  lockServo.write(SERVO_UNLOCK_POS);
}

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  lcd.begin(16, 2);
  init_icons(lcd);
  lockServo.attach(SERVO_PIN);
  Serial.begin(9600);
  unlock();
  tone(BUZZER_PIN,300,30);
  showStartupMessage();
  if (look == true) {
    lock();
  } else {
    unlock();
  }
}

void loop() {
  if (look == true) 
  {
    safeLockedLogic();
  } 
  else 
  {
    safeUnlockedLogic();
  }
}

void showStartupMessage() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  delay(1000);
  lcd.setCursor(0, 2);
  String message = "Security System";
  for (byte i = 0; i < message.length(); i++) {
    lcd.print(message[i]);
    delay(100);
  }
  delay(500);
}
void safeLockedLogic() {
  look = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(ICON_LOCKED_CHAR);
  lcd.print(" Safe Locked! ");
  lcd.write(ICON_LOCKED_CHAR);
  String input = inputSecretCode();
  enteredPassword = input.toInt();
  showWaitScreen(200);
  if (enteredPassword == PASSWORD || maz == 1) 
  {
    showUnlockMessage();
    unlock();
    successful();
     maz = 0;
    delay(3000);
    lock();
  } 
  else if(maz == 3)
  {
    j = 10000;
    wrong();
  }
  else 
  {
      wrong();
  }
}
void safeUnlockedLogic() {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.write(ICON_UNLOCKED_CHAR);
    lcd.print(" ");
    lcd.write(ICON_RIGHT_ARROW);
    lcd.print(" ");
    lcd.write(ICON_LOCKED_CHAR);
    look = true;
    lock();
    digitalWrite(LED,LOW);
    showWaitScreen(100);
  
}
String inputSecretCode() {
  lcd.setCursor(5, 1);
  lcd.print("[____]");
  lcd.setCursor(6, 1);
  String result = ""; 
  while (result.length() < 4 ) 
  {
    PirRead = digitalRead(PIR_PIN);
    if(PirRead == HIGH)
    {
      maz = 3;
      break;
    }
    if(digitalRead(BUTTON_PIN)==HIGH)
    {
    maz = 1;
    break;
    
    }
    char key = keypad.getKey();
    if (key >= '0' && key <= '9') {
      lcd.print('*');
      result += key;
    }
  }
  return result;
}

void showWaitScreen(int delayMillis) 
{
  lcd.setCursor(2, 1);
  lcd.print("[..........]");
  lcd.setCursor(3, 1);
  for (byte i = 0; i < 10; i++) {
    delay(delayMillis);
    lcd.print("=");
    delay(100);
  }
}
void showUnlockMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(ICON_UNLOCKED_CHAR);
  lcd.setCursor(4, 0);
  lcd.print("Unlocked!");
  lcd.setCursor(15, 0);
  lcd.write(ICON_UNLOCKED_CHAR);
  delay(1000);
}
void successful() {
  tone(BUZZER_PIN, NOTE_C6);
  delay(200);
  tone(BUZZER_PIN, NOTE_D6);
  delay(200);
  tone(BUZZER_PIN, NOTE_E6);
  delay(200);
  tone(BUZZER_PIN, NOTE_F6);
  delay(200);
  tone(BUZZER_PIN, NOTE_G6);
  delay(200);
  tone(BUZZER_PIN, NOTE_A6);
  delay(200);
  tone(BUZZER_PIN, NOTE_B6);
  delay(200);
  tone(BUZZER_PIN, NOTE_C7);
  delay(200);
  noTone(BUZZER_PIN);
}
void wrong()
{
    digitalWrite(LED,HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied!");
    tone(BUZZER_PIN,3000,j);
    showWaitScreen(1000);
}