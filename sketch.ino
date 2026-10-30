#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 11;
const int relayPin = 12;
const int ledPin = 13;

long duration;
int distance;

const int threshold = 20;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(relayPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Distance System");
  delay(1500);
  lcd.clear();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    lcd.setCursor(0, 0);
    lcd.print("No object found ");
    lcd.setCursor(0, 1);
    lcd.print("Check sensor    ");

    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
    delay(300);
    return;
  }

  distance = duration * 0.0343 / 2;

  lcd.setCursor(0, 0);
  lcd.print("Distance:       ");
  lcd.setCursor(10, 0);
  lcd.print(distance);
  lcd.print(" cm");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= threshold) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Object Detected ");
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Area is Clear   ");
  }

  delay(300);
}