#define left 4
#define center 3
#define right 2

//motor one
#define ENA 12
#define IN1 8
#define IN2 9

//motor two
#define ENB 13
#define IN3 10
#define IN4 11

 // speed of this robot
int spd= 150;
int spd1=150;
void setup() {
  Serial.begin(9600);
  pinMode(left, INPUT);
  pinMode(center, INPUT);
  pinMode(right, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  bool leftV = digitalRead(left);
  bool centerV = digitalRead(center);
  bool rightV = digitalRead(right);

  Serial.println(rightV);

  if (leftV == 1 && centerV == 0 && rightV == 1) {
    carforward();
    Serial.println("forward");
  } else if (leftV == 0 && centerV == 0 && rightV == 0) {
    carStop();
    Serial.println("stop");
  } else if (leftV == 1 && centerV == 1 && rightV == 1) {
    carStop();
    Serial.println("stop");
  } else if (leftV == 0 && centerV == 0 && rightV == 1) {
    carturnleft();
    Serial.println("sleft");
  } else if (leftV == 1 && centerV == 0 && rightV == 0) {
    carturnright();
    Serial.println("sright");
  } else if (leftV == 0 && centerV == 1 && rightV == 1) {
    carturnleft();
    Serial.println("mleft");
  } else if (leftV == 1 && centerV == 1 && rightV == 0) {
    carturnright();
    Serial.println("mright");
  }
}

void carforward() {
  analogWrite(ENA, spd);
  analogWrite(ENB, spd);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, spd1);
  analogWrite(ENB, spd1);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnright() {
  analogWrite(ENA, spd1);
  analogWrite(ENB, spd1);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}