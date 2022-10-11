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
  
  Serial.print("I received: ");
  while (Serial.available() > 0) {
      char incomingByte = '0';
      incomingByte = Serial.read();
      Serial.print(incomingByte);
  }
  Serial.println();

  delay(4000);

  String teststr = Serial.readString();
  Serial.println(teststr);

  Serial.flush();

  String test_str = "Hello World";
  String test_str_2 = "Hello";
  String test_str_3 = "asdf";
  String test_str_4 = "asdfgzx";
  String test_str_5 = "Hello World!!";

  Serial.print("Result String Comp 1: ");
  Serial.println(test_str.compareTo(test_str_2));

  Serial.print("Result String Comp 2: ");
  Serial.println(test_str.compareTo(test_str_5));

  Serial.print("Result charAt str_0: ");
  Serial.println(test_str.charAt(0));

  Serial.print("Result concat: ");
  Serial.println(test_str_3.concat(test_str_4));

  auto result_c_str = test_str_3.c_str();

  Serial.print("Result endsWith: ");
  Serial.println(test_str_3.endsWith(test_str_4));

  Serial.print("Result equals: ");
  Serial.println(test_str.equals(test_str_5));

  Serial.print("Result equalsIgnoreCase: ");
  Serial.println(test_str.equalsIgnoreCase(test_str_5));

  byte bytes[test_str.length() + 1];
  test_str.getBytes(bytes, test_str.length() + 1);
  Serial.print("Result getBytes: ");
  for (int i = 0; i < test_str.length(); i++){
    Serial.print((char) bytes[i]);
  }
  Serial.println();

  Serial.print("Result indexOf: ");
  Serial.println(test_str.indexOf("H"));
}