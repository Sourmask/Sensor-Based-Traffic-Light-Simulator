void setup() {
  // === Traffic Light LEDs (Green, Yellow, Red) ===

  // East - Pins 1 (Green), 2 (Yellow), 3 (Red)
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  // West - Pins 4 (Green), 5 (Yellow), 6 (Red)
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  // North - Pins 7 (Green), 8 (Yellow), 9 (Red)
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // South - Pins 10 (Green), 11 (Yellow), 12 (Red)
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  // === IR Sensor Inputs ===

  pinMode(A0, INPUT); // East
  pinMode(A1, INPUT); // West
  pinMode(A2, INPUT); // North
  pinMode(A3, INPUT); // South

  // East Black
  // West Blue
  // North Red
  // South Yellow
}

void loop() {
  bool eastDetected  = digitalRead(A0) == LOW;
  bool westDetected  = digitalRead(A1) == LOW;
  bool northDetected = digitalRead(A2) == LOW;
  bool southDetected = digitalRead(A3) == LOW;

  if (!eastDetected && !westDetected && !northDetected && !southDetected) {
    blinkAllYellow();
  } else {
    if (eastDetected) {
      eastControl(); 
    } else if (westDetected) {
      westControl(); 
    } else if (northDetected) {
      northControl(); 
    } else if (southDetected) {
      southControl();
    }
  }
}

void eastControl(){
  for (int pin = 1; pin <= 12; pin++) {
  digitalWrite(pin, LOW);
  } 

  digitalWrite(1, HIGH); // black go
  digitalWrite(9, HIGH); // red stop
  digitalWrite(4, HIGH); // blue go
  digitalWrite(12, HIGH); // yellow stop
}

void blinkAllYellow() {
  for (int pin = 1; pin <= 12; pin++) {
    digitalWrite(pin, LOW);
  }

  // Blink all yellow pins
  digitalWrite(2, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(11, HIGH);
  delay(500);

  digitalWrite(2, LOW);
  digitalWrite(5, LOW);
  digitalWrite(8, LOW);
  digitalWrite(11, LOW);
  delay(500);
}

// void controlTrafficLights(int greenPin, int yellowPin, int redPin) {

//   // Green on
//   digitalWrite(redPin, LOW);
//   digitalWrite(yellowPin, LOW);
//   digitalWrite(greenPin, HIGH);
//   delay(3000); // green light duration

//   // Yellow on
//   digitalWrite(greenPin, LOW);
//   digitalWrite(yellowPin, HIGH);
//   delay(1000); // yellow light duration

//   // Red on
//   digitalWrite(yellowPin, LOW);
//   digitalWrite(redPin, HIGH);
  
// }
