#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial bluetooth(2, 3); // RX, TX

Servo LeftLeg;
Servo LeftFoot;
Servo RightFoot;
Servo RightLeg;

bool walkMode = false;
bool rollMode = false;
int roll_right_forward_speed = 40;
int roll_left_forward_speed = 40;
int roll_right_backward_speed = 40;
int roll_left_backward_speed = 40;
char command = '\0';

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  // Initial positions
  Home();
}

void loop() {
  CheckBluetooth();

  if (command == 'w') {
    SetWalk();
    command = '\0';
  }
  else if (command == 'r') {
    SetRoll();
    command = '\0';
  }
  else if (command == 'h') {
    Home();
    command = '\0';
  }
  else if (command == 'f') {
    if(walkMode) {
      WalkForward();
    } else {
      NinjaRollForward(roll_right_forward_speed, roll_left_forward_speed);
    }
    command = '\0';
  }
  else if (command == 'b') {
    if(walkMode) {
      WalkBackward();
    } else {
      NinjaRollBackward(roll_right_backward_speed, roll_left_backward_speed);
    }
    command = '\0';
  }
  else if (command == 'g') {
    if(walkMode) {
      WalkRight();
    } else {
      NinjaRollRight(roll_right_forward_speed, roll_left_forward_speed);
    }
    command = '\0';
  }
  else if (command == 'l') {
    if(walkMode) {
      WalkLeft();
    } else {
      NinjaRollLeft(roll_right_backward_speed, roll_left_backward_speed);
    }
    command = '\0';
  }
  else if (command == 's') {
    NinjaRollStop();
    command = '\0';
  }

 
}

void CheckBluetooth() {
  if (bluetooth.available()) {
    command = bluetooth.read();
    Serial.println("Received command: " + String(command));
  }
}

void Home() {
  LeftFoot.attach(7);
  RightFoot.attach(8);
  LeftLeg.attach(9);
  RightLeg.attach(10);
  delay(100);

  LeftFoot.write(90);
  RightFoot.write(90);
  LeftLeg.write(60);
  RightLeg.write(120);
  delay(100);
  LeftLeg.detach();
  RightLeg.detach();
}

void SetWalk() {
  walkMode = true;
  rollMode = false;
  LeftLeg.attach(9);
  RightLeg.attach(10);
  LeftLeg.write(60);
  RightLeg.write(120);
  delay(100);
  LeftLeg.detach();
  RightLeg.detach();
}

void SetRoll() {
  walkMode = false;
  rollMode = true;
  LeftLeg.attach(9);
  RightLeg.attach(10);
  LeftLeg.write(170);
  RightLeg.write(10);
  delay(100);
  LeftLeg.detach();
  RightLeg.detach();
}

void TiltToRight() {
  LeftLeg.attach(9);
  RightLeg.attach(10);
  LeftLeg.write(0);
  RightLeg.write(65);
  delay(300);
  LeftLeg.detach();
  RightLeg.detach();
  delay(300);
}

void TiltToLeft() {
  LeftLeg.attach(9);
  RightLeg.attach(10);
  LeftLeg.write(120);
  RightLeg.write(180);
  delay(300);
  LeftLeg.detach();
  RightLeg.detach();
  delay(300);
}

void MoveRightFoot(int s, int t) {
  RightFoot.attach(8);
  RightFoot.write(s);
  delay(t);
  RightFoot.write(90);
  delay(100);
  RightFoot.detach();
  delay(300);
}

void MoveLeftFoot(int s, int t) {
  LeftFoot.attach(7);
  LeftFoot.write(s);
  delay(t);
  LeftFoot.write(90);
  delay(100);
  LeftFoot.detach();
  delay(300);
}

void ReturnFromRight() {
  LeftLeg.attach(9);
  LeftLeg.write(60);
  RightLeg.attach(10);
  for(int count=65;count<=120;count+=2) {
    RightLeg.write(count);
    delay(25);
  }
  delay(300);
  LeftLeg.detach();
  RightLeg.detach();
}

void ReturnFromLeft() {
  RightLeg.attach(10);
  RightLeg.write(120);
  LeftLeg.attach(9);
  for(int count=120;count>=60;count-=2) {
    LeftLeg.write(count);
    delay(25);
  }
  delay(300);
  LeftLeg.detach();
  RightLeg.detach();
}

void WalkForward() {
  TiltToRight();
  delay(100);
  MoveRightFoot(70, 250);
  delay(100);
  ReturnFromRight();
  
  TiltToLeft();
  delay(100);
  MoveLeftFoot(140, 350);
  delay(100);
  ReturnFromLeft();
}

void WalkRight() {
  TiltToRight();
  delay(100);
  MoveRightFoot(70, 350);
  delay(100);
  ReturnFromRight();
}

void WalkBackward() {
  TiltToRight();
  delay(100);
  MoveRightFoot(120, 250);
  delay(100);
  ReturnFromRight();
  
  TiltToLeft();
  delay(100);
  MoveLeftFoot(60, 350);
  delay(100);
  ReturnFromLeft();
}

void WalkLeft() {
  TiltToLeft();
  delay(100);
  MoveLeftFoot(120, 350);
  delay(100);
  ReturnFromLeft();
}

void NinjaRollForward(int speedR, int speedL) {
  LeftFoot.attach(7);
  RightFoot.attach(8);
  LeftFoot.write(90 + speedL);
  RightFoot.write(90 - speedR);
}

void NinjaRollRight(int speedR, int speedL) {
  LeftFoot.attach(7);
  RightFoot.attach(8);
  LeftFoot.write(90 + speedL);
  RightFoot.write(90 + speedR);
}

void NinjaRollLeft(int speedR, int speedL) {
  LeftFoot.attach(7);
  RightFoot.attach(8);
  LeftFoot.write(90 - speedL);
  RightFoot.write(90 - speedR);
}

void NinjaRollBackward(int speedR, int speedL) {
  LeftFoot.attach(7);
  RightFoot.attach(8);
  LeftFoot.write(90 - speedL);
  RightFoot.write(90 + speedR);
}

void NinjaRollStop() {
  LeftFoot.write(90);
  RightFoot.write(90);
  LeftFoot.detach();
  RightFoot.detach();
}


