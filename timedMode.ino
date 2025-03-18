#define EAST  0
#define WEST  1
#define NORTH 2
#define SOUTH 3

const int NUM_DIRECTIONS = 4;
const unsigned long QUEUE_TIMEOUT_MS = 10000;     // Clear queue after 10s of no detection
const unsigned long YELLOW_GRACE_PERIOD = 10000;  // Blink yellow after 10s of no cars

// Traffic light pins: [Green, Yellow, Red]
int trafficPins[NUM_DIRECTIONS][3] = {
  {1, 2, 3},     // East
  {4, 5, 6},     // West
  {7, 8, 9},     // North
  {10, 11, 12}   // South
};

// IR sensor pins
int sensorPins[NUM_DIRECTIONS] = {A0, A1, A2, A3};

// Traffic queue tracking
bool queued[NUM_DIRECTIONS] = {false, false, false, false};
unsigned long arrivalTime[NUM_DIRECTIONS] = {0, 0, 0, 0};

// Last time any car was seen (for yellow blinking grace)
unsigned long lastDetectionTime = 0;

void setup() {
  // === Traffic Light LEDs (Green, Yellow, Red) ===

  // East
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  // West
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  // North
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // South
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  // === IR Sensors ===

  pinMode(A0, INPUT); // East (Black)
  pinMode(A1, INPUT); // West (Blue)
  pinMode(A2, INPUT); // North (Red)
  pinMode(A3, INPUT); // South (Yellow)
}

void loop() {
  unsigned long now = millis();
  bool anyQueued = false;

  // Check all directions
  for (int i = 0; i < NUM_DIRECTIONS; i++) {
    bool detected = digitalRead(sensorPins[i]) == LOW;

    if (detected) {
      lastDetectionTime = now; // Reset blinking grace timer

      if (!queued[i]) {
        queued[i] = true;
        arrivalTime[i] = now;
      }
    } else {
      if (queued[i] && (now - arrivalTime[i] >= QUEUE_TIMEOUT_MS)) {
        queued[i] = false;
        arrivalTime[i] = 0;
      }
    }

    if (queued[i]) {
      anyQueued = true;
    }
  }

  // No cars, check for yellow blinking grace period
  if (!anyQueued) {
    if (now - lastDetectionTime >= YELLOW_GRACE_PERIOD) {
      blinkAllYellow();
    }
    return; // Wait until grace period ends or new detection happens
  }

  // Find next direction to serve (oldest in queue)
  int nextDir = -1;
  unsigned long oldestTime = now;

  for (int i = 0; i < NUM_DIRECTIONS; i++) {
    if (queued[i] && arrivalTime[i] <= oldestTime) {
      oldestTime = arrivalTime[i];
      nextDir = i;
    }
  }

  // Serve traffic
  if (nextDir != -1) {
    controlTrafficDirection(nextDir);
    queued[nextDir] = false;
    arrivalTime[nextDir] = 0;
  }
}

void controlTrafficDirection(int dir) {
  // Turn off all traffic lights
  for (int pin = 1; pin <= 12; pin++) {
    digitalWrite(pin, LOW);
  }

  // Green on
  digitalWrite(trafficPins[dir][0], HIGH);
  delay(3000);

  // Yellow on
  digitalWrite(trafficPins[dir][0], LOW);
  digitalWrite(trafficPins[dir][1], HIGH);
  delay(1000);

  // Red on
  digitalWrite(trafficPins[dir][1], LOW);
  digitalWrite(trafficPins[dir][2], HIGH);
  delay(1000);
}

void blinkAllYellow() {
  // Turn off all lights
  for (int pin = 1; pin <= 12; pin++) {
    digitalWrite(pin, LOW);
  }

  // Blink yellow LEDs
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