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
const int motorIzq = 3;
const int motorCen = 5;
const int motorDer = 6;
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

  pinMode(motorDer, OUTPUT);    //MotorDER
  pinMode(motorCen, OUTPUT);    //MotorCEN
  pinMode(motorIzq, OUTPUT);    //MotorIZQ

  pinMode(2, OUTPUT);     //Zumbador
  pinMode(7, OUTPUT);    //Luz
  
  Serial.begin(9600);
}

void loop() {
  // Impresión de la distancia recibida por los sensores Ultrasonido
  ultra_der = u_distancia(12, 13);    //(Trigger, Echo)
  Serial.print("D: ");
  Serial.print(ultra_der);
  ultra_cen = u_distancia(10, 11);
  Serial.print(" C: ");
  Serial.print(ultra_cen);
  Serial.print(" PWM: ");
  Serial.print(map(ultra_cen, 0, 100, 230, 100));
  ultra_izq = u_distancia(8, 9);
  Serial.print(" I: ");
  Serial.print(ultra_izq);
  Serial.print(" PWM: ");
  Serial.println(map(ultra_izq, 0, 100, 200, 100));

  // Funcionamiento de motores usando PWM
  if (ultra_der <= 100) {
    // Si la distancia es menor o igual a 100 centimétros, manda un PWM
    // con una intensidad dependiente de cuan cerca o lejos esté, de lo contrario, apaga el motor
    analogWrite(motorDer, map(ultra_der, 0, 100, 200, 100)); } else { analogWrite(motorDer, LOW); }
  if (ultra_cen <= 100) {
    analogWrite(motorCen, map(ultra_cen, 0, 100, 230, 100)); } else { analogWrite(motorCen, LOW); }
  if (ultra_izq <= 100) {
    analogWrite(motorIzq, map(ultra_izq, 0, 100, 200, 100)); } else { analogWrite(motorIzq, LOW); }
  
  // Bluetooth
  if (Serial.available() > 0){
    btSerial = Serial.read();
    if (btSerial = 'F') { // Sí se recibe "F" llama a la función btAction
      btAction();
      Serial.println("F has been pressed");
    }
  }
  
  //delay(500);
}

// Función que ejecute el bluetooth
void btAction() {
  tone(2, 441, 500);
  tone(2, 441, 500);
  digitalWrite(7, HIGH);
}
