// Definición de pines para los sensores de sonido
#define MIC1_PIN A0 // Adelante (no se usa en esta configuración)
#define MIC2_PIN A1 // Derecha
#define MIC4_PIN A3 // Izquierda

// Definición de pines para el motor
#define PWM1 7
#define Dir1 8

// Definición de pines para el sensor de gas
#define PIN_MQ2 A4
#define LED 9

// Definición de pines para el sensor ultrasónico
#define TRIG_PIN 34
#define ECHO_PIN 35

// Umbrales
int threshold = 500; // Umbral básico para detectar sonido
int gasThreshold = 400;
int stopDistance = 10; // Distancia en cm para detenerse

// Variables de almacenamiento de lecturas previas
int mic2Prev = 0;
int mic4Prev = 0;
int mic2Avg = 0;
int mic4Avg = 0;
int samples = 5; // Número de muestras para calcular el promedio

void setup() {
  // Inicializar comunicación serial y pines
  Serial.begin(9600);
  pinMode(PWM1, OUTPUT);
  pinMode(Dir1, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(PIN_MQ2, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Lecturas de sensores de sonido
  int mic2 = analogRead(MIC2_PIN);
  int mic4 = analogRead(MIC4_PIN);

  // Actualizar promedios móviles
  mic2Avg = (mic2Prev + mic2Avg * (samples - 1)) / samples;
  mic4Avg = (mic4Prev + mic4Avg * (samples - 1)) / samples;

  // Almacenar las lecturas actuales para el siguiente ciclo
  mic2Prev = mic2;
  mic4Prev = mic4;

  // Lectura del sensor de gas
  int gasValue = analogRead(PIN_MQ2);
  
  // Lectura del sensor ultrasónico
  int distance = getDistance();

  // Envía los valores al Serial Monitor para debug
  Serial.print("Derecha: ");
  Serial.print(mic2Avg);
  Serial.print(" | Izquierda: ");
  Serial.print(mic4Avg);
  Serial.print(" | Gas: ");
  Serial.println(gasValue);

  // Procesamiento de sonido con umbral adaptativo
  if (mic2Avg > threshold) {
    Serial.println("Se escucha algo a la derecha");
    // Avanzar
    digitalWrite(Dir1, LOW);
    analogWrite(PWM1, 200);
  } else if (mic4Avg > threshold) {
    Serial.println("Se escucha algo a la izquierda");
    // Retroceder
    digitalWrite(Dir1, HIGH);
    analogWrite(PWM1, 200);
  } else {
    analogWrite(PWM1, 0); // Detener el motor si no hay sonidos detectados
  }

  // Procesamiento de gas
  if (gasValue > gasThreshold) {
    Serial.println("Se ha detectado un gas inusual!");
    digitalWrite(LED, HIGH);
  } else {
    Serial.println("No se detecta gas tóxico");
    digitalWrite(LED, LOW);
  }

  // Procesamiento del sensor ultrasónico
  if (distance <= stopDistance) {
    Serial.println("Objeto detectado a menos de 10 cm, deteniéndose");
    analogWrite(PWM1, 0); // Detener el motor
  }

  delay(100);
}

// Función para medir la distancia con el sensor ultrasónico
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
