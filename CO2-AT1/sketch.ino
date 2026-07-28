#include <LiquidCrystal.h>
#include <Servo.h>

// LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Servo
Servo speedServo;

// Inputs
const int speedPin = A0;
const int fuelPin  = A1;
const int tempPin  = A2;

// Outputs
const int buzzer    = 7;
const int oilLED    = 8;
const int engineLED = 9;
const int fuelLED   = 10;

void setup() {

  lcd.begin(16, 2);

  speedServo.attach(6);

  pinMode(buzzer, OUTPUT);
  pinMode(oilLED, OUTPUT);
  pinMode(engineLED, OUTPUT);
  pinMode(fuelLED, OUTPUT);

  lcd.print("AUTOMOTIVE");
  lcd.setCursor(0,1);
  lcd.print("DASHBOARD");
  delay(2000);
  lcd.clear();
}

void loop() {

  // Read Potentiometers
  int speedValue = analogRead(speedPin);
  int fuelValue  = analogRead(fuelPin);
  int tempValue  = analogRead(tempPin);

  // Convert Values
  int speed = map(speedValue,0,1023,0,180);
  int fuel  = map(fuelValue,0,1023,0,100);
  int temp  = map(tempValue,0,1023,20,120);

  // Servo Speedometer
  speedServo.write(speed);

  // Reset Outputs
  digitalWrite(oilLED, LOW);
  digitalWrite(engineLED, LOW);
  digitalWrite(fuelLED, LOW);
  digitalWrite(buzzer, LOW);

  // Warning Conditions

  // High Speed
  if(speed > 120){
    digitalWrite(buzzer,HIGH);
  }

  // High Temperature
  if(temp > 90){
    digitalWrite(engineLED,HIGH);
    digitalWrite(buzzer,HIGH);
  }

  // Low Fuel
  if(fuel < 20){
    digitalWrite(fuelLED,HIGH);
  }

  // Low Speed (Oil Indicator)
  if(speed < 20){
    digitalWrite(oilLED,HIGH);
  }

  // LCD Display
  lcd.setCursor(0,0);
  lcd.print("S:");
  lcd.print(speed);
  lcd.print("km ");

  lcd.print("F:");
  lcd.print(fuel);
  lcd.print("% ");

  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C ");

  delay(500);
}