#include <Mouse.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int frequency = 0;
int threshold = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  Serial.begin(9600);

  while (Serial.available() == 0) {
    frequency = pulseIn(sensorOut, LOW);
    Serial.println(frequency);
    delay(150);
  }
  threshold = Serial.parseInt();
  Serial.print("Setting threshold to: ");
  Serial.println(threshold, DEC);
}

void loop() {
  Serial.println("Beginning next reaction cycle");
  Mouse.click();
  int start = micros();
  int reads = 0;
  int detections = 0;
  while (detections < 3) {
    reads += 1;
    frequency = pulseIn(sensorOut, LOW);
    if (frequency < threshold) {
      detections += 1;
    } else {
      detections = 0;
    }
    
  }
  int finish = micros();
  delay(100);
  Mouse.click();
  int mouseFinish = micros();
  Serial.println(threshold);
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
