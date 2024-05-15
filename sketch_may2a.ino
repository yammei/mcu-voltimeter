// Voltimeter
const int aoPin = A0;
const float voltage = (5.0 / 1023.0);

// Pulse Sensor
const int trigPin = 2;
const int echoPin = 3;
long duration;
int distance;

// Step Motor
const int in1Pin = 46;
const int in2Pin = 48;
const int in3Pin = 50;
const int in4Pin = 52;

// 3461BS-1 Display
const int segments[] = {43, 45, 47, 49, 51, 53, 55};
const int digits[] = {40, 38, 36, 34};
const int digitPatterns[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 0, 0, 1, 1}  // 9
};

// Custom Keys
const int key1Pin = A13;
const int key2Pin = A14;
const int key3Pin = A15;


void setup() {
  // Voltimeter
  pinMode(aoPin, INPUT);

  // Pulse Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Step Motor
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // 3461BS-1 Display
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digits[i], OUTPUT);
  }

  // Custom Keys
  pinMode(key1Pin, INPUT);
  pinMode(key1Pin, INPUT);
  pinMode(key3Pin, INPUT);

  // Serial Init
  Serial.begin(9600); 
}

void loop() {
  runVoltimeter();
  // runDisplay(voltimeterResponse);
  // runPulseSensor();
  // runStepMotorCW();
  // runStepMotorCCW();
  runCustomKeys();
  delay(100);
}

float runVoltimeter() {
  int sensorResponse = analogRead(aoPin);
  float voltageConverted = sensorResponse * (voltage);

  Serial.print("Voltage: ");
  Serial.print(voltageConverted);
  Serial.println("V.");

  return voltageConverted;
}

void runPulseSensor() { 
  // Pulse Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
}

void runStepMotorCW() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  delay(1000);
}

void runStepMotorCCW() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(1000);
}

void runDisplay(float number) {
  int integerPart = (int)voltage;
  int decimalPart = (int)(voltage * 1000) % 1000;
  
  displayDigit(integerPart / 10, 0);
  displayDigit(integerPart % 10, 1);
  displayDigit(decimalPart / 100, 2);
  displayDigit(decimalPart / 10 % 10, 3);
}

void displayDigit(int digit, int position) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], digitPatterns[digit][i]);
  }

  digitalWrite(digits[position], HIGH);
}

void runCustomKeys() {
  int keyStatuses[3];

  keyStatuses[0] = analogRead(key1Pin);
  keyStatuses[1] = analogRead(key2Pin);
  keyStatuses[2] = analogRead(key3Pin);

  for(int i=0; i<3; i++) {
    // Serial.println(key1Status);
    if (keyStatuses[i] >= 500) {
      Serial.print("Key Pressed: ");
      Serial.print(i + 1);
      Serial.println(".");
    }
  }
}