// Sensor de ultrasonido
long u_tiempo(int trigger_pin, int echo_pin) {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  long microseconds = pulseIn(echo_pin , HIGH);
  return microseconds;
}

long u_distancia(int trigger_pin, int echo_pin) {
  long microseconds = u_tiempo(trigger_pin, echo_pin);
  long u_distancia;
  u_distancia = microseconds / 29 / 2;
  if (u_distancia == 0) {
    u_distancia = 999;
  }
  return u_distancia;
}
// Variables
int ultra_izq = 0;
int ultra_cen = 0;
int ultra_der = 0;

int blut = 0;

void setup() {
  pinMode(8, OUTPUT);       //SIZQ
  pinMode(9, INPUT);

  pinMode(11, INPUT);     //SCEN
  pinMode(10, OUTPUT);

  pinMode(12, OUTPUT);     //SDER
  pinMode(13, INPUT);

  pinMode(2, OUTPUT);      //MDER
  pinMode(3, OUTPUT);      //MCEN
  pinMode(4, OUTPUT);      //MIZQ

  pinMode(5, OUTPUT);      //Zumbador
  pinMode(6, OUTPUT);      //LUZ
  Serial.begin(9600);
}

void loop() {
  ultra_der = u_distancia(12, 13);    //(Trigger, Echo)
  Serial.print(ultra_der);
  Serial.print("   ");
  ultra_cen = u_distancia(10, 11);
  Serial.print(ultra_cen);
  Serial.print("   ");
  ultra_izq = u_distancia(8, 9);
  Serial.print(ultra_izq);
  Serial.print("   ");
  Serial.println("");

  // Funcionamiento de motores
  if ((ultra_der <= 100) && (ultra_der >= 1)) {
    digitalWrite(2, HIGH);
    Serial.print("Motor 1");
    Serial.print("   ");
  } else { digitalWrite(2, LOW); }
  if ((ultra_cen <= 100) && (ultra_cen >= 1)) {
    digitalWrite(3, HIGH);
    Serial.print("Motor 2");
    Serial.print("   "); 
  } else { digitalWrite(3, LOW); }
  if ((ultra_izq <= 100) && (ultra_izq >= 1)) {
    digitalWrite(4, HIGH);
    Serial.print("Motor 3");
    Serial.print("   ");
  } else { digitalWrite(4, LOW); }
   Serial.println("");
  
  // Bluetooth
  blut = Serial.read();
  if (blut = 'F') {
    bluto();
  }

  delay (500);
}

void bluto() {
  tone(5, 441, 500);
  tone(5, 441, 500);
  digitalWrite(6, HIGH);

}
