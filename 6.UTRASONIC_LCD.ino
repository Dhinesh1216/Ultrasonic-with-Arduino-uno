#include <LiquidCrystal.h> // Include the LiquidCrystal library

// Define LCD pins
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define TRIG_PIN  6 // The Arduino UNO R4 pin connected to the ultrasonic sensor's TRIG pin
#define ECHO_PIN  7 // The Arduino UNO R4 pin connected to the ultrasonic sensor's ECHO pin

float duration_us, distance_cm;

void setup() {
  // Begin serial communication
  Serial.begin(9600);

  // Configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // Configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);

  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Display a startup message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Ultrasonic Dist");
  lcd.setCursor(0, 1);
  lcd.print("Measuring...");
  delay(2000); // Wait for 2 seconds to display the message
  lcd.clear(); // Clear the LCD
}

void loop() {
  // Generate a 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in cm
  distance_cm = 0.017 * duration_us;

  // Print the value to the Serial Monitor
  Serial.print("Dist: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Display the distance on the LCD
  lcd.setCursor(0, 0); // Set cursor to the first row
  lcd.print("Distance:"); // Clear previous text
  lcd.setCursor(9, 0); // Move cursor to the appropriate position
  lcd.print(distance_cm);
  lcd.print(" cm");

  delay(500); // Wait for half a second
}
