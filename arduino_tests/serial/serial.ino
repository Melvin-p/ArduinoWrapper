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
  
}