#include <SoftwareSerial.h>
SoftwareSerial HC06(2, 3);
#define trig 5
#define echo 4
#define vibro 9
#define red 6
#define green 7
#define blue 8

float x;
unsigned char buf;
   String c;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(vibro, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
  HC06.begin(9600);
  HC06.println("Hello!");
  HC06.println("Creator: Pavlov Tikhon");
  HC06.println("_________");
  HC06.println("_________");
  delay(1500);
}

void loop() {
  x = getDistance();

  if (HC06.available() > 0) {
  c = HC06.readString();
  }
  
  if (c == "1") {
    Serial.println("aaaaaaaaaa!");
    HC06.println("Distance: " + String(x) + " cm");
    HC06.println("Distance: " + String(x * 0.39) + " in");
    delay(300);
    if (x >= 10) {
      digitalWrite(green, 1);
      digitalWrite(red, 0);
      digitalWrite(blue, 0);
      digitalWrite(vibro, 0);
    }
    if (x < 10 and x >= 5) {
      digitalWrite(green, 0);
      digitalWrite(red, 0);
      digitalWrite(blue, 1);
      digitalWrite(vibro, 1);
      delay(300);
      digitalWrite(vibro, 0);
      delay(300);
      digitalWrite(vibro, 1);
      delay(300);
      digitalWrite(vibro, 0);
    }
    if (x < 5) {
      digitalWrite(green, 0);
      digitalWrite(red, 1);
      digitalWrite(blue, 0);
      digitalWrite(vibro, 1);
      
    }
  }
  if (c == "0") {
    digitalWrite(green, 0);
    digitalWrite(red, 0);
    digitalWrite(blue, 0);
    digitalWrite(vibro, 0);
    HC06.println("OFF"); 
  }
  
}
int getDistance()
  {
    int duration, cm;
    digitalWrite(trig, 0);
    delayMicroseconds(2);
    digitalWrite(trig, 1);
    delayMicroseconds(10);
    digitalWrite(trig, 0);
    duration = pulseIn(echo, 1);
    cm = duration / 58;
    return cm;
  }
