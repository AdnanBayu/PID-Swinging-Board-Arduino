#include <Servo.h>
Servo servo;
/* mini servo can only rotate 0-180 degree*/
#define trig 8
#define echo 9

#define kp 1
#define ki 0.02
#define kd 0.001

double priError = 0;
double toError = 0;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(5);
  Serial.begin(9600);
  servo.write(90);

}
void loop() {
  PID();
}

long distance () {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long t = pulseIn(echo, HIGH);
  float cm = (t / 2.0) * 0.0343;
  return cm;
}

void PID() {
  int dis = distance ();

  /*pengkondisian nilai error sensor ultrasonic*/
  //Sensor HC-SR04 lemah ketika menghitung jarak dibawah 5 cm
  if(dis>22){
    dis = 5;
  }

  int setP = 11;
  double error = setP - dis;


  double Pvalue = error * kp;
  double Ivalue = toError * ki;
  double Dvalue = (error - priError) * kd;

  double PIDvalue = Pvalue + Ivalue + Dvalue;
  priError = error;
  toError += error;
  // Serial.println(" ");
  // Serial.println("Nilai PID : ");
  // Serial.print(PIDvalue);

  // Serial.println("Jarak : ");
  Serial.print(dis);
  Serial.println(" ");
  int Fvalue = (int)PIDvalue;


  Fvalue = map(Fvalue, -135, 135, 0, 135);


  if (Fvalue < 0) {
    Fvalue = 0;
  }
  if (Fvalue > 135) {
    Fvalue = 135;
  }

  servo.write(Fvalue);
}