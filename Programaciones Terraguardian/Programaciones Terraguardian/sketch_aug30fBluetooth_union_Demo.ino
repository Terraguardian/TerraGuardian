#define MIC1_PIN A0  // Adelante
#define MIC2_PIN A1  // Derecha
#define MIC3_PIN A2  // Atrás
#define MIC4_PIN A3  // Izquierda
#define PIN_MQ2   A4  // Sensor de gas MQ2
#define LED       9   // LED indicador
#define PWM1      7   // Pin PWM del motor
#define Dir1      8   // Pin de dirección del motor

int threshold = 500; 
int instru = 0;
int gasValue;
bool gasDetected = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(PIN_MQ2, INPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(Dir1, OUTPUT);
  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
    Serial1.begin(9600); // Inicia la comunicación serial para Bluetooth en placas con más de un puerto serial
  #endif
}

void loop() {
  // Lectura de los sensores de sonido
  int mic1 = analogRead(MIC1_PIN);
  int mic2 = analogRead(MIC2_PIN);
  int mic3 = analogRead(MIC3_PIN);
  int mic4 = analogRead(MIC4_PIN);
  gasValue = analogRead(PIN_MQ2);  // Lectura del sensor de gas MQ2

  // Detección de dirección del sonido más fuerte
  if (mic1 > mic2 && mic1 > mic3 && mic1 > mic4) {
    Serial.println("Se escucha algo adelante");
  } else if (mic2 > mic1 && mic2 > mic3 && mic2 > mic4) {
    Serial.println("Se escucha algo a la derecha");
  } else if (mic3 > mic1 && mic3 > mic2 && mic3 > mic4) {
    Serial.println("Se escucha algo atrás");
  } else {
    Serial.println("Se escucha algo a la izquierda");
  }
  delay (2000);
  // Envía los valores al Serial Plotter
  Serial.print("\tAdelante:");
  Serial.print(mic1);
  Serial.print("\tDerecha:");
  Serial.print(mic2);
  Serial.print("\tAtras:");
  Serial.print(mic3);
  Serial.print("\tIzquierda:");
  Serial.println(mic4);

  // Detección de gas
  if (gasValue > 400) { 
    if (!gasDetected) {  // Solo envía el mensaje si el estado de detección de gas ha cambiado
      Serial.println("Se ha detectado un gas dañino para los valores del  ICA!");
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
        Serial1.println("Se ha detectado un gas dañino para los valores del ICA!");  // Envía un mensaje por Bluetooth
      #endif
      gasDetected = true;  // Cambia el estado de detección de gas
    }
    digitalWrite(LED, HIGH);  // Enciende el LED si se detecta gas
  } else { 
    if (gasDetected) {  // Solo envía el mensaje si el estado de detección de gas ha cambiado
      Serial.println("El ambiente se encuentra libre de gases toxico.");
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
        Serial1.println("El ambiente se encuentra libre de gases toxicos.");  // Envía un mensaje por Bluetooth
      #endif
      gasDetected = false;  // Cambia el estado de detección de gas
    }
    digitalWrite(LED, LOW);   // Apaga el LED si no se detecta gas
  }

  // Control de motores basado en la entrada serial
  if (Serial.available()) {
    instru = Serial.read();
    switch (instru) {
      case '1':  // Si se recibe '1' (Avanzar)
        Serial.println("Avanzando hacia adelante");
        digitalWrite(Dir1, LOW);   // Dirección adelante
        analogWrite(PWM1, 200);    // Velocidad del motor
        break;
      case '2':  // Si se recibe '2' (Detener)
        Serial.println("Deteniendo");
        analogWrite(PWM1, 0);      // Detiene el motor
        break;
      case '3':  // Si se recibe '3' (Retroceder)
        Serial.println("Avanzando hacia atrás");
        digitalWrite(Dir1, HIGH);  // Dirección atrás
        analogWrite(PWM1, 200);    // Velocidad del motor
        break;
      default:  // Cualquier otra entrada
        Serial.println("Instrucción no reconocida, apagando motores");
        analogWrite(PWM1, 0);      // Apaga el motor
    }
  }

  delay(200);  // Pausa antes de la siguiente iteración
}
