#include <stdlib.h>

void setup(){
  Serial.begin(9600);
 
}

void loop(){
  //Testing Time Functions
  delay(1000);
  unsigned long result_milllis = millis();
  Serial.print("Result Millis: ");
  Serial.println(result_milllis);
  delayMicroseconds(1000000);
  unsigned long result_micros = micros();
  Serial.print("Result Micros: ");
  Serial.println(result_micros);
  
  char char_1 = 'a';
  auto isAlpha_result = isAlpha(char_1);
  Serial.print("Result isAlpha: ");
  Serial.println(isAlpha_result);

  char char_2 = 'a';
  auto isAlphaNumeric_result = isAlphaNumeric(char_2);
  Serial.print("Result isAlphaNumeric: ");
  Serial.println(isAlphaNumeric_result);

  char char_3 = 'a';
  auto isAscii_result = isAscii(char_3);
  Serial.print("Result isAscii: ");
  Serial.println(isAscii_result);

  char char_4 = 'a';
  auto isControl_result = isControl(char_4);
  Serial.print("Result isControl: ");
  Serial.println(isControl_result);

  char char_5 = 'a';
  auto isDigit_result = isDigit(char_5);
  Serial.print("Result isDigit: ");
  Serial.println(isDigit_result);

  char char_6 = 'a';
  auto isGraph_result = isGraph(char_6);
  Serial.print("Result isGraph: ");
  Serial.println(isGraph_result);

  char char_7 = 'a';
  auto isHexadecimalDigit_result = isHexadecimalDigit(char_7);
  Serial.print("Result isHexadecimalDigit: ");
  Serial.println(isHexadecimalDigit_result);

  char char_8 = 'a';
  auto isLowerCase_result = isLowerCase(char_8);
  Serial.print("Result isLowerCase: ");
  Serial.println(isLowerCase_result);

  char char_9 = 'a';
  auto isPrintable_result = isPrintable(char_9);
  Serial.print("Result isPrintable: ");
  Serial.println(isPrintable_result);

  char char_10 = 'a';
  auto isPunct_result = isPunct(char_10);
  Serial.print("Result isPunct_result: ");
  Serial.println(isPunct_result);

  char char_11 = 'a';
  auto isSpace_result = isSpace(char_11);
  Serial.print("Result isSpace: ");
  Serial.println(isSpace_result);

  char char_12 = 'a';
  auto isUpperCase_result = isUpperCase(char_12);
  Serial.print("Result isUpperCase: ");
  Serial.println(isUpperCase_result);

  char char_13 = 'a';
  auto isWhitespace_result = isWhitespace(char_13);
  Serial.print("Result isWhitespace: ");
  Serial.println(isWhitespace_result);

  //TODO Strings
  
}
