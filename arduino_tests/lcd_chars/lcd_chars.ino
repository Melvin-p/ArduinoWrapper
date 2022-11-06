#include <Adafruit_RGBLCDShield.h>

#define OFF 0x0
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

uint8_t numb = 0;

void func0() {
  lcd.clear();
  lcd.setBacklight(VIOLET);
  for (uint8_t i = 0; i < 80; ++i) {
    lcd.print((char)i);
    Serial.print((char)i);
    Serial.print(" ");
    Serial.print(i);
    Serial.print("\n");
  }
}

void func1() {
  lcd.clear();
  lcd.setBacklight(GREEN);
  for (uint8_t i = 80; i < 160; ++i) {
    lcd.print((char)i);
    Serial.print((char)i);
    Serial.print(" ");
    Serial.print(i);
    Serial.print("\n");
  }
}

void func2() {
  lcd.clear();
  lcd.setBacklight(RED);
  for (uint8_t i = 160; i < 240; ++i) {
    lcd.print((char)i);
    Serial.print((char)i);
    Serial.print(" ");
    Serial.print(i);
    Serial.print("\n");
  }
}

void func3() {
  lcd.clear();
  lcd.setBacklight(WHITE);
  for (uint8_t i = 240; i < 256; ++i) {
    lcd.print((char)i);
    Serial.print((char)i);
    Serial.print(" ");
    Serial.print(i);
    Serial.print("\n");
    if (i == 255) {
      break;
    }
  }
}

void update() {
  switch (numb) {
    case 0:
      func0();
      break;
    case 1:
      func1();
      break;
    case 2:
      func2();
      break;
    case 3:
      func3();
      break;
  }
}

void setup() {
  //debuging
  Serial.begin(9600);

  //lcd columns and rows
  lcd.begin(16, 2);

  lcd.blink();
  lcd.cursor();

  func0();
}



void buttons() {
  uint8_t buttons = lcd.readButtons();

  if (buttons & BUTTON_RIGHT) {
    lcd.scrollDisplayRight();
  }

  if (buttons & BUTTON_LEFT) {
    lcd.scrollDisplayLeft();
  }

  if (buttons & BUTTON_UP) {
    numb = ((numb + 1) % 4);
    update();
  }

  if (buttons & BUTTON_DOWN) {
    numb = ((numb - 1) % 4);
    update();
  }
}


void loop() {

  if ((millis() % 100) == 0) {
    buttons();
  }
}