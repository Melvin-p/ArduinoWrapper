#include <stdint.h>

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

  //Testing Math Functions
  uint8_t abs_value = 10;
  auto abs_result = abs(abs_value);
  Serial.print("Result Abs: ");
  Serial.println(abs_result);

  uint8_t constrain_1 = 10;
  uint8_t constrain_2 = 15;
  uint8_t constrain_3 = 5;
  auto constrain_result = constrain(constrain_1, constrain_3, constrain_2);
  Serial.print("Result Constraint: ");
  Serial.println(constrain_result);

  uint8_t map_1 = 100;
  uint8_t map_2 = 0;
  uint8_t map_3 = 1023;
  uint8_t map_4 = 0;
  uint8_t map_5 = 255;
  auto map_result = map(map_1, map_2, map_3, map_4, map_5);
  Serial.print("Result Map: ");
  Serial.println(map_result);

  uint8_t max_1 = 10;
  uint8_t max_2 = 20;
  auto max_result = max(max_1, max_2);
  Serial.print("Result Max: ");
  Serial.println(max_result);

  uint8_t min_1 = 10;
  uint8_t min_2 = 20;
  auto min_result = min(min_1, min_2);
  Serial.print("Result Min: ");
  Serial.println(min_result);

  uint8_t pow_1 = 2;
  uint8_t pow_2 = 3;
  auto pow_result = pow(pow_1, pow_2);
  Serial.print("Result Pow: ");
  Serial.println(pow_result);

  uint8_t sq_1 = 4;
  auto sq_result = sq(sq_1);
  Serial.print("Result Sq: ");
  Serial.println(sq_result);

  uint8_t sqrt_1 = 4;
  auto sqrt_result = sqrt(sqrt_1);
  Serial.print("Result Sqrt: ");
  Serial.println(sqrt_result);

  uint8_t sin_1 = (PI);
  auto sin_result = sin(sin_1);
  Serial.print("Result Sin: ");
  Serial.println(sin_result);

  uint8_t cos_1 = (PI);
  auto cos_result = sin(cos_1);
  Serial.print("Result Cos: ");
  Serial.println(cos_result);

  uint8_t tan_1 = (HALF_PI);
  auto tan_result = sin(tan_1);
  Serial.print("Result Tan: ");
  Serial.println(tan_result);

  //Testing Random Functions
  randomSeed(934739030);

  auto rand_result = random(10);
  Serial.print("Result rand_result: ");
  Serial.println(rand_result);

  auto rand_r_result = random(5, 15);
  Serial.print("Result rand_r_result: ");
  Serial.println(rand_r_result);

}