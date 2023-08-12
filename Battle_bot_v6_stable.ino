/* Author : SHEHAN SOORIYAARACHCHI */

#define ch1pin 11
#define ch2pin 10
#define ch10pin 9
#define R_PWM1 A0
#define L_PWM1 A1
#define R_EN1 8
#define L_EN1 7
#define R_PWM2 A2
#define L_PWM2 A3
#define R_EN2 2
#define L_EN2 4
#define mid 2
#define tolerance 35
#define ch4pin 3

int M1speed = 0;
int M2speed = 0;
int CH1 = 0;//left-right
int CH2 = 0; // Forward - Reverse
int CH10 ; //Switch
int CH4 = 0; //left stick hor
float speedfactor1 = 1.0;
float speedfactor2 = 1.0;
int t = 75; // delay for vibration


int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 997, 1980, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch() {
  CH10 = pulseIn(ch10pin, HIGH, 30000);
  if (CH10 >= 1200) {
    return true;
  }
  else {
    return false;
  }
}
bool vibrate() {
  CH4 = readChannel(ch4pin, 0, 100, 0);
  if (CH4 < 40) {
    return true;
  }
  else {
    return false;
  }
}
void setmotor1() {
  pinMode(R_PWM1, OUTPUT);
  pinMode(L_PWM1, OUTPUT);
  pinMode( R_EN1, OUTPUT);
  pinMode(L_EN1, OUTPUT);
  digitalWrite(R_EN1, HIGH);
  digitalWrite(L_EN1, HIGH);
}
void setmotor2() {
  pinMode(R_PWM2, OUTPUT);
  pinMode(L_PWM2, OUTPUT);
  pinMode( R_EN2, OUTPUT);
  pinMode(L_EN2, OUTPUT);
  digitalWrite(R_EN2, HIGH);
  digitalWrite(L_EN2, HIGH);
}

void speedcon() {
  M1speed = abs(CH2);
  M1speed = constrain(M1speed, 150, 255);
  M2speed = abs(CH2);
  M2speed = constrain(M2speed, 150, 255);
  M1speed = map(M1speed, 1, 100, 150, 255);
  M2speed = map(M2speed, 1, 100, 150, 255);
}

void forward(String motor, int mspeed) {
  if (motor == "m1") {
    analogWrite(R_PWM1, mspeed * speedfactor1 );
    analogWrite(L_PWM1, 0);
    Serial.print("m1 going forward");
  }
  else if (motor == "m2") {
    analogWrite(R_PWM2, mspeed * speedfactor2 );
    analogWrite(L_PWM2, 0);
    Serial.print("m2 going forward");
  }
  else {
    analogWrite(R_PWM1, 0 );
    analogWrite(L_PWM1, 0);
    analogWrite(R_PWM2, 0 );
    analogWrite(L_PWM2, 0);
  }


}

void backward(String motor, int mspeed) {
  if (motor == "m1") {
    analogWrite(R_PWM1, 0 );
    analogWrite(L_PWM1, mspeed * speedfactor1);
    Serial.print("m1 going backward");
  }
  else if (motor == "m2") {
    analogWrite(R_PWM2, 0 );
    analogWrite(L_PWM2, mspeed * speedfactor2);
    Serial.print("m2 going backward");
  }
  else {
    analogWrite(R_PWM1, 0 );
    analogWrite(L_PWM1, 0);
    analogWrite(R_PWM2, 0 );
    analogWrite(L_PWM2, 0);
  }
}
void stay(String motor) {
  if (motor == "m1") {
    analogWrite(R_PWM1, 0 );
    analogWrite(L_PWM1, 0);
  }
  else if (motor == "m2") {
    analogWrite(R_PWM2, 0 );
    analogWrite(L_PWM2, 0);
  }
  else {

  }
}

void configuration1() {
  if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    stay("m1");
    stay("m2");
  }
  else if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 < -(-mid + tolerance) ) {
    backward("m1", M1speed);
    backward("m2", M2speed);
  }
  else if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 > (mid + tolerance) ) {
    forward("m1", M1speed);
    forward("m2", M2speed);
  }
  else if (CH1 > (mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    forward("m1", M1speed);
    backward("m2",  M2speed);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    backward("m1", M1speed);
    forward("m2",  M2speed);
  }
  else if (CH1 > (mid + tolerance) && CH2 > (mid + tolerance)) {
    forward("m1", M1speed);
    forward("m2",  0);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 > (mid + tolerance)) {
    forward("m1",  0);
    forward("m2", M2speed);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 < -(-mid + tolerance)) {
    backward("m1",  0);
    backward("m2", M2speed);
  }
  else if (CH1 > (mid + tolerance) && CH2 < -(-mid + tolerance)) {
    backward("m1", M1speed);
    backward("m2",  0);
  }
  else {
    stay("m1");
    stay("m2");
  }
}

void configuration2() {

  if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    stay("m1");
    stay("m2");
  }
  else if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 < -(-mid + tolerance) ) {
    forward("m1", M1speed);
    forward("m2", M2speed); //done
  }
  else if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 > (mid + tolerance) ) {
    backward("m1", M1speed);
    backward("m2", M2speed);
  }
  else if (CH1 > (mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    backward("m2", M1speed);
    forward("m1",  M2speed);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    forward("m2", M1speed);
    backward("m1",  M2speed);
  }
  else if (CH1 > (mid + tolerance) && CH2 > (mid + tolerance)) {
    backward("m2", M1speed);
    backward("m1",  0);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 > (mid + tolerance)) {
    backward("m2",  0);
    backward("m1", M2speed);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 < -(-mid + tolerance)) {
    backward("m2",  0);
    forward("m1", M2speed);
  }
  else if (CH1 > (mid + tolerance) && CH2 < -(-mid + tolerance)) {
    forward("m2", M1speed);
    forward("m1",  0);
  }
  else {
    stay("m1");
    stay("m2");
  }
}
void configuration3() {
  if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    stay("m1");
    stay("m2");
  }
  else if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 < -(-mid + tolerance) ) {
    backward("m1", M1speed);
    backward("m2", M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);

  }
  else if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 > (mid + tolerance) ) {
    forward("m1", M1speed);
    forward("m2", M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 > (mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    forward("m1", M1speed);
    backward("m2",  M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    backward("m1", M1speed);
    forward("m2",  M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 > (mid + tolerance) && CH2 > (mid + tolerance)) {
    forward("m1", M1speed);
    forward("m2",  0);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 > (mid + tolerance)) {
    forward("m1",  0);
    forward("m2", M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 < -(-mid + tolerance)) {
    backward("m1",  0);
    backward("m2", M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 > (mid + tolerance) && CH2 < -(-mid + tolerance)) {
    backward("m1", M1speed);
    backward("m2",  0);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else {
    stay("m1");
    stay("m2");

  }
}
void configuration4() {

  if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    stay("m1");
    stay("m2");

  }
  else if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 < -(-mid + tolerance) ) {
    forward("m1", M1speed);
    forward("m2", M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 <= (mid + tolerance) && CH1 >= -(-mid + tolerance) && CH2 > (mid + tolerance) ) {
    backward("m1", M1speed);
    backward("m2", M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 > (mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    backward("m2", M1speed);
    forward("m1",  M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 <= (mid + tolerance) && CH2 >= -(-mid + tolerance)) {
    forward("m2", M1speed);
    backward("m1",  M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 > (mid + tolerance) && CH2 > (mid + tolerance)) {
    backward("m2", M1speed);
    backward("m1",  0);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 > (mid + tolerance)) {
    backward("m2",  0);
    backward("m1", M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 < -(-mid + tolerance) && CH2 < -(-mid + tolerance)) {
    backward("m2",  0);
    forward("m1", M2speed);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else if (CH1 > (mid + tolerance) && CH2 < -(-mid + tolerance)) {
    forward("m2", M1speed);
    forward("m1",  0);
    delay(t);
    stay("m1");
    stay("m2");
    delay(t);
  }
  else {
    stay("m1");
    stay("m2");
  }
}
void setup()

{

  Serial.begin(115200);
  setmotor1();
  setmotor2();
  speedcon();

}

void loop() {

  //  Serial.println("M1speed:");
  //  Serial.println(M1speed);
  //  Serial.println("M2speed:");
  //  Serial.println(M2speed);
  //  Serial.print("CH2 :");
  //  Serial.println(CH2);
  //  Serial.print("CH1 :");
  //  Serial.println(CH1);
  Serial.print("CH4 :");
  Serial.println(CH4);

  CH1 = readChannel(ch1pin, -100, 100, 0);
  CH2 = readChannel(ch2pin, -100, 100, 0);

  speedcon();
  if (readSwitch()) {
    if (vibrate()) {
      configuration3();
    }
    else {
      configuration1();
    }
  }
  else {
    if (vibrate()) {
      configuration4();
    }
    else {
      configuration2();
    }
  }

}
