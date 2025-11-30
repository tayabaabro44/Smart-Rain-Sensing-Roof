#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);  
// 10 = Arduino RX  (connect to HC-05 TX)
// 11 = Arduino TX  (connect to HC-05 RX)

Servo roofServo;

// Pins
int rainAnalogPin = A0;     // AO of rain sensor
int rainDigitalPin = 7;     // DO of rain sensor
int servoPin = 9;

void setup() {,.
  pinMode(rainDigitalPin, INPUT);

  roofServo.attach(servoPin);
  roofServo.write(0);  // Roof open initially

  Serial.begin(9600);
  BT.begin(9600);

  Serial.println("System Started...");
  BT.println("System Started...");
}

void loop() {
  // ***** READ BOTH SENSOR VALUES *****
  int analogValue = analogRead(rainAnalogPin);     // 0–1023
  int digitalValue = digitalRead(rainDigitalPin);  // 0 or 1

  // ***** SEND TO SERIAL + BLUETOOTH *****
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print("   Digital: ");
  Serial.println(digitalValue);

  BT.print("Analog: ");
  BT.print(analogValue);
  BT.print("   Digital: ");
  BT.println(digitalValue);

  // ***** LOGIC FOR ROOF CONTROL (Digital Based) *****
  if (digitalValue == LOW) {  
    // LOW = Rain Detected
    Serial.println("Rain Detected → Closing Roof");
    BT.println("Rain Detected → Closing Roof");

    roofServo.write(90);   // Close roof
  } 
  else {
    Serial.println("No Rain → Opening Roof");
    BT.println("No Rain → Opening Roof");

    roofServo.write(0);    // Open roof
  }

  delay(1000
  
  );
}