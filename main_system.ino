#include <Servo.h>
// Pin Definitions
#define LDRpin A2        // LDR Sensor Pin
#define MQ2pin A4        // MQ-2 Gas Sensor Pin
#define TEMPpin A0       // Temperature Sensor (KY-028) Pin
const int TRIG_PIN = 3;  // Ultrasonic Sensor TRIG pin
const int ECHO_PIN = 13; // Ultrasonic Sensor ECHO pin
const int SERVO_PIN = 11; // Servo Motor pin
const int BUZZER_PIN = 7; // Buzzer pin
const int LED_PIN = 10;  // LED pin

// Thresholds
const int DISTANCE_THRESHOLD = 10; // Ultrasonic Distance Threshold in cm
const int TEMP_THRESHOLD = 50;    // Temperature Threshold (raw value)
const int GAS_THRESHOLD = 200;    // Gas Threshold (raw value)
const int LDR_THRESHOLD = 100;    // LDR Threshold (raw value)

// Global Variables
Servo servo;          // Servo Motor Object
float distance_cm;    // Ultrasonic Sensor Value
float tempValue;      // Temperature Sensor Value
float gasValue;       // MQ-2 Gas Sensor Value
int LDRValue;         // LDR Sensor Value

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  
  // Pin Modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDRpin, INPUT);
  pinMode(MQ2pin, INPUT);
  pinMode(TEMPpin, INPUT);
  
  servo.attach(SERVO_PIN);
  servo.write(90); // Initial state: Servo closed
  
  // Ensure initial states
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void updateUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  float duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;
  if (distance_cm <= 0 || distance_cm > 400) {
    distance_cm = 400; // Out of range
  }
}

void updateSensorValues() {
  tempValue = analogRead(TEMPpin);
  gasValue = analogRead(MQ2pin);
}

bool isAlarmConditionActive() {
  return (tempValue < TEMP_THRESHOLD || gasValue > GAS_THRESHOLD);
}

void playAlarm() {
  while (true) {
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
    Serial.println("Alarm is active!");
    
    // Check sensor values before each pattern
    updateSensorValues();
    if (!isAlarmConditionActive()) {
      Serial.println("Conditions returned to normal - stopping alarm");
      stopAlarm();
      break;
    }
    
    // Pattern 1
    for (int i = 0; i < 80; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(1);
      digitalWrite(BUZZER_PIN, LOW);
      delay(1);
      
      // Check every few iterations to make the response more immediate
      if (i % 20 == 0) {
        updateSensorValues();
        if (!isAlarmConditionActive()) {
          Serial.println("Conditions returned to normal - stopping alarm");
          stopAlarm();
          return;
        }
      }
    }
    
    // Pattern 2
    for (int i = 0; i < 100; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(2);
      digitalWrite(BUZZER_PIN, LOW);
      delay(2);
      
      // Check every few iterations to make the response more immediate
      if (i % 25 == 0) {
        updateSensorValues();
        if (!isAlarmConditionActive()) {
          Serial.println("Conditions returned to normal - stopping alarm");
          stopAlarm();
          return;
        }
      }
    }
  }
}

void stopAlarm() {
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Alarm stopped.");
}

void loop() {
  // Update Sensor Values
  updateUltrasonic();
  LDRValue = analogRead(LDRpin);
  updateSensorValues();
  
  // Log Sensor Values to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  Serial.print("LDR Value: ");
  Serial.println(LDRValue);
  Serial.print("Temperature Value (Raw): ");
  Serial.println(tempValue);
  Serial.print("Gas Value (Raw): ");
  Serial.println(gasValue);
  
  // Conditional Logic
  if (isAlarmConditionActive()) {
    Serial.println("Condition met for alarm: Temp < 50 or Gas > 200");
    servo.write(90); // Close the servo
    playAlarm();     // Activate alarm
  } 
  else if (LDRValue > LDR_THRESHOLD && distance_cm <= DISTANCE_THRESHOLD) {
    Serial.println("Condition met for servo open: LDR > 100 and Distance <= 10 cm");
    servo.write(0);  // Open the servo
    stopAlarm();     // Deactivate alarm
  } 
  else {
    Serial.println("No conditions met for alarm, servo closed.");
    servo.write(90); // Close the servo
    stopAlarm();     // Deactivate alarm
  }
  
  delay(500); // Delay for stability
}
