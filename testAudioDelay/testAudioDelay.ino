#include <Mouse.h>

int analogPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Beginning next reaction cycle");
  Mouse.click();
  int start = micros();
  int reads = 0;
  int detections = 0;
  while (detections < 3) {
    reads += 1;
    if (analogRead(analogPin) > 0) {
      detections += 1;
    }
  }
  int finish = micros();
  delay(100);
  Mouse.click();
  int mouseFinish = micros();
  Serial.print("Read port ");
  Serial.print(reads);
  Serial.print(" times in ");
  Serial.print(finish - start);
  Serial.print(" us with mouse click taking ");
  Serial.print(mouseFinish - finish);
  Serial.println(" us");
  Serial.println("Advancing in 2000 ms...");
  Serial.println();
  delay(2000);
}
