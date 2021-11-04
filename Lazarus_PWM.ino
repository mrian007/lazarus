// Funciones del Ultrasonido
long u_tiempo(int trigger_pin, int echo_pin) {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  long microseconds = pulseIn(echo_pin , HIGH);
  return microseconds; }
long u_distancia(int trigger_pin, int echo_pin) {
  long microseconds = u_tiempo(trigger_pin, echo_pin);
  long u_distancia;
  u_distancia = microseconds / 29 / 2;
  if (u_distancia == 0) {
    u_distancia = 999;
  }
  return u_distancia; }
  
// Variables
int ultra_izq = 0;
int ultra_cen = 0;
int ultra_der = 0;
int btSerial = 0;

void setup() {
  pinMode(8, OUTPUT);  //Ultrasonido Izquierdo
  pinMode(9, INPUT);

  pinMode(11, INPUT);  // Ultrasonido Centro
  pinMode(10, OUTPUT);

  pinMode(12, OUTPUT); //Ultrasonido Derecho
  pinMode(13, INPUT);

  pinMode(3, OUTPUT);    //MotorDER
  pinMode(5, OUTPUT);    //MotorCEN
  pinMode(6, OUTPUT);    //MotorIZQ

  pinMode(2, OUTPUT);     //Zumbador
  pinMode(7, OUTPUT);    //Luz
  
  Serial.begin(9600);
}

void loop() {
  // Impresión de la distancia recibida por los sensores Ultrasonido
  ultra_der = u_distancia(12, 13);    //(Trigger, Echo)
  Serial.println("D: ");
  Serial.print(ultra_der);
  ultra_cen = u_distancia(10, 11);
  Serial.print("C: ");
  Serial.print(ultra_cen);
  ultra_izq = u_distancia(8, 9);
  Serial.print("I: ");
  Serial.print(ultra_izq);

  // Funcionamiento de motores usando PWM
  if (ultra_der <= 100) {
    // Si la distancia es menor o igual a 100 centimétros, manda un PWM
    // con una intensidad dependiente de cuan cerca o lejos esté, de lo contrario, apaga el motor
    analogWrite(3, map(ultra_der, 0, 100, 200, 100)); } else { analogWrite(3, LOW); }
  if (ultra_cen <= 100) {
    analogWrite(5, map(ultra_cen, 0, 100, 230, 100)); } else { analogWrite(5, LOW); }
  if (ultra_izq <= 100) {
    analogWrite(6, map(ultra_izq, 0, 100, 200, 100)); } else { analogWrite(6, LOW); }
  
  // Bluetooth
  if (Serial.available() > 0){
    btSerial = Serial.read();
    if (btSerial = 'F') { // Sí se recibe "F" llama a la función btAction
      btAction();
      Serial.println("F has been pressed");
    }
  }
  
  delay(500);
}

// Función que ejecute el bluetooth
void btAction() {
  tone(2, 441, 500);
  tone(2, 441, 500);
  digitalWrite(7, HIGH);
}
