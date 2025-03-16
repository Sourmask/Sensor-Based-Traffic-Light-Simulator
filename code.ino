void setup() {
    // East Black
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
  
    // West Blue
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
  
    // North Red
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
  
    // South Yellow
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
  
    // Input
    pinMode(A0, INPUT); // black
    pinMode(A1, INPUT); // blue
    pinMode(A2, INPUT); // red
    pinMode(A3, INPUT); // yellow
  }
  
  void loop() {
    digitalWrite(1, HIGH);
    delay(1000);
    digitalWrite(1, LOW); 
    delay(1000);
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
  }