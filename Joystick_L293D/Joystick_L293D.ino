#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int command = COMMAND_NO;

// MOTOR A
const int motorPin2 = 5;
const int motorPin7 = 6;
const int enableA = 9;    // PWM pin connected to Enable A

// MOTOR B
const int motorPin10 = 10;
const int motorPin15 = 3;
const int enableB = 11;    // PWM pin connected to Enable A


void setup() {
  // put your setup code here, to run once:
  pinMode(enableA, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin7, OUTPUT);

  pinMode(enableB, OUTPUT);
  pinMode(motorPin10, OUTPUT);
  pinMode(motorPin15, OUTPUT);

  digitalWrite(enableA, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin7, LOW);

  digitalWrite(enableB, LOW);
  digitalWrite(motorPin10, LOW);
  digitalWrite(motorPin15, LOW);
  Serial.begin(9600);
}

void loop() {
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  int yAngle = 0; // Initialize yAngle for speed

  // Define the dead zone threshold
  int deadZone = 20;
  int minSpeed = 50;  // Adjust this value based on motor requirements

  // Forward movement mapping (outside dead zone)
  if (yValue > 512 + deadZone) {
      yAngle = map(yValue, 512 + deadZone, 1023, minSpeed, 255); // Map upward movement to 0 to 255
  } 
  // Backward movement mapping (outside dead zone)
  else if (yValue < 512 - deadZone) {
      yAngle = map(yValue, 512 - deadZone, 0, -minSpeed, -255); // Map downward movement to 0 to -255
  }
  // Within dead zone, set speed to zero (no movement)
  else {
      yAngle = 0;
  }

  if (yAngle > 0) {
    // Forward movement
    Serial.println(yAngle);
    // analogWrite(motorPin2, yAngle); // Set speed proportional to yAngle
    digitalWrite(motorPin2, HIGH);   // Direction for forward
    digitalWrite(motorPin7, LOW);   // Direction for forward
    analogWrite(enableA, yAngle);

    digitalWrite(motorPin10, HIGH);   // Direction for forward
    digitalWrite(motorPin15, LOW);   // Direction for forward
    analogWrite(enableB, yAngle);

  } else if (yAngle < 0) {
      // Backward movement
      Serial.println(yAngle);
      // analogWrite(motorPin2, abs(yAngle)); // Set speed proportional to abs(yAngle)
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin7, HIGH);       // Direction for backward
      analogWrite(enableA, abs(yAngle));

      digitalWrite(motorPin10, LOW);
      digitalWrite(motorPin15, HIGH);       // Direction for backward
      analogWrite(enableB, abs(yAngle));
  } else {
      // Stop motors
      Serial.println(yAngle);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin7, LOW);
      digitalWrite(enableA, LOW);

      digitalWrite(motorPin10, LOW);
      digitalWrite(motorPin15, LOW);
      digitalWrite(enableB, LOW);
  }


  // // converts the analog value to commands
  // // reset commands
  // command = COMMAND_NO;

  // // check up/down commands
  // if (yValue < UP_THRESHOLD)
  //   command = command | COMMAND_UP;
  // else if (yValue > DOWN_THRESHOLD)
  //   command = command | COMMAND_DOWN;

  // // check left/right commands
  // if (xValue < LEFT_THRESHOLD)
  //   command = command | COMMAND_LEFT;
  // else if (xValue > RIGHT_THRESHOLD)
  //   command = command | COMMAND_RIGHT;

  // // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS

  // // print command to serial and process command
  // if (command == COMMAND_NO) {
  //   Serial.println("COMMAND_NO");
  //   digitalWrite(motorPin2, LOW);
  //   digitalWrite(motorPin7, LOW);
  // }

  // if (command & COMMAND_UP) {
  //   Serial.println("COMMAND UP");
  //   digitalWrite(motorPin2, HIGH);
  //   digitalWrite(motorPin7, LOW);
  // }

  // if (command & COMMAND_DOWN) {
  //   Serial.println("COMMAND DOWN");
  //   digitalWrite(motorPin2, LOW);
  //   digitalWrite(motorPin7, HIGH);
  // }

  // if (command & COMMAND_LEFT) {
  //   Serial.println("COMMAND LEFT");
  //   // TODO: add your task here
  // }

  // if (command & COMMAND_RIGHT) {
  //   Serial.println("COMMAND RIGHT");
  //   // TODO: add your task here
  // }
}
