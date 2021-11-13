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
int pwm_izq=0;
int ultra_cen = 0;
int pwm_cen=0;
int ultra_der = 0;
int pwm_der=0;
int btSerial = 0;

void setup() {
  pinMode(4, OUTPUT);  //Ultrasonido Izquierdo
  pinMode(7, INPUT);

  pinMode(11, INPUT);  // Ultrasonido Centro
  pinMode(10, OUTPUT);

  pinMode(12, OUTPUT); //Ultrasonido Derecho
  pinMode(13, INPUT);

  pinMode(motorDer, OUTPUT);    //MotorDER
  pinMode(motorCen, OUTPUT);    //MotorCEN
  pinMode(motorIzq, OUTPUT);    //MotorIZQ

  pinMode(2, OUTPUT);     //Zumbador
  pinMode(8, OUTPUT);    //Luz
  
  Serial.begin(9600);
}

void loop() {
  ultra_der = u_distancia(12, 13);    //(Trigger, Echo)
  ultra_izq = u_distancia(4, 7);
  ultra_cen = u_distancia(10, 11);
  
    if(ultra_izq>200){ultra_izq=0;}
  Serial.print(" I: ");
  Serial.print(ultra_izq);
  Serial.print(" PWM: ");
  pwm_izq=map(ultra_izq, 0, 200, 1023, -100);
  Serial.print(pwm_izq);
  
  
  // Impresión de la distancia recibida por los sensores Ultrasonido
  
  if(ultra_der>200){ultra_der=0;}
  Serial.print(" D: ");
  Serial.print(ultra_der);
  Serial.print(" PWM: ");
  pwm_der=map(ultra_der, 0, 200, 1023, -100);
  Serial.print(pwm_der);
  

  
  
  if(ultra_cen>200){ultra_cen=0;}
  Serial.print(" C: ");
  Serial.print(ultra_cen);
  Serial.print(" PWM: ");
  pwm_cen=map(ultra_cen, 0, 200, 1023, -100);
  Serial.println(pwm_cen);
  


  // Funcionamiento de motores usando PWM
  if ((ultra_der <= 100) && (ultra_der > 0)) {
    // Si la distancia es menor o igual a 100 centimétros, manda un PWM
    // con una intensidad dependiente de cuan cerca o lejos esté, de lo contrario, apaga el motor
    analogWrite(motorDer, pwm_der); } else { analogWrite(motorDer, LOW); }

  if ((ultra_cen <= 100) && (ultra_cen > 0)) {
    analogWrite(motorCen, pwm_cen); } else { analogWrite(motorCen, LOW); }
  
  if ((ultra_izq <= 100) && (ultra_izq > 0)) {
    analogWrite(motorIzq, pwm_izq); } else { analogWrite(motorIzq, LOW); }
  
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
  digitalWrite(8, HIGH);
}
