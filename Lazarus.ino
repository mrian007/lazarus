//sensor de ultrasonido
long u_tiempo(int trigger_pin, int echo_pin) {
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);
    long microseconds = pulseIn(echo_pin ,HIGH);
    return microseconds;
}

long u_distancia(int trigger_pin, int echo_pin) {
    long microseconds = u_tiempo(trigger_pin, echo_pin);
    long u_distancia;
    u_distancia = microseconds/29/2;
    if (u_distancia == 0){
        u_distancia = 999;
    }
    return u_distancia;
}

int ultra_izq=0;
int ultra_cen=0;
int ultra_der=0;

int bluto=0;
void setup() {
  pinMode(8,OUTPUT);        //SIZQ
  pinMode(9,INPUT);

  pinMode(10,INPUT);      //SCEN
  pinMode(11,OUTPUT);

  pinMode(12,OUTPUT);      //SDER
  pinMode(13,INPUT);

pinMode(2,OUTPUT);       //MDER
pinMode(3,OUTPUT);       //MCEN
pinMode(4,OUTPUT);       //MIZQ

pinMode(5,OUTPUT);       //PIP
pinMode(6,OUTPUT);       //LUZ
Serial.begin(9600);
}

void loop() {
    ultra_der = u_distancia(12,13);
    ultra_cen = u_distancia(11,10);
    ultra_izq = u_distancia(8,9);

if ((ultra_der <= 50) && (ultra_der >= 1)){
  digitalWrite(2,HIGH);
  }
  if ((ultra_cen <= 50) && (ultra_cen >= 1)){
  digitalWrite(3,HIGH);
  }
  if ((ultra_izq <= 50) && (ultra_izq >= 1)){
  digitalWrite(4,HIGH);
  }

bluto=Serial.read();
if (bluto='P'){
tone(5,178,1000);
digitalWrite(6,HIGH);
}

delay (500);
}
