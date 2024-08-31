#define PIN_SOUND_SENSOR_1 A0  // Definir el pin del primer sensor de sonido (adelante)
#define PIN_SOUND_SENSOR_2 A1  // Definir el pin del segundo sensor de sonido (derecha)
#define PIN_SOUND_SENSOR_3 A2  // Definir el pin del tercer sensor de sonido (atrás)
#define PIN_SOUND_SENSOR_4 A3  // Definir el pin del cuarto sensor de sonido (izquierda)
#define LED                 9  // Definir el pin del LED

int value1, value2, value3, value4;

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serial para el monitor serie
  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
    Serial1.begin(9600); // Inicia la comunicación serial para Bluetooth en placas con más de un puerto serial
  #endif
  pinMode(LED, OUTPUT);
  pinMode(PIN_SOUND_SENSOR_1, INPUT);
  pinMode(PIN_SOUND_SENSOR_2, INPUT);
  pinMode(PIN_SOUND_SENSOR_3, INPUT);
  pinMode(PIN_SOUND_SENSOR_4, INPUT);
}

void loop() {
   value1 = analogRead(PIN_SOUND_SENSOR_1);  // Lee el valor del primer sensor de sonido (adelante)
   value2 = analogRead(PIN_SOUND_SENSOR_2);  // Lee el valor del segundo sensor de sonido (derecha)
   value3 = analogRead(PIN_SOUND_SENSOR_3);  // Lee el valor del tercer sensor de sonido (atrás)
   value4 = analogRead(PIN_SOUND_SENSOR_4);  // Lee el valor del cuarto sensor de sonido (izquierda)

   if (value1 > 400) { 
      digitalWrite(LED, HIGH);  // Enciende el LED si el primer sensor detecta sonido (adelante)
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
        Serial1.println("Sonido detectado por el Sensor 1 Adelante!");  // Envía un mensaje por Bluetooth para el Sensor 1
      #else
        Serial.println("Sonido detectado por el Sensor 1 Adelante!");  // Envía un mensaje por Bluetooth para el Sensor 1
      #endif
   }

   if (value2 > 400) { 
      digitalWrite(LED, HIGH);  // Enciende el LED si el segundo sensor detecta sonido (derecha)
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
        Serial1.println("Sonido detectado por el Sensor 2 Derecha!");  // Envía un mensaje por Bluetooth para el Sensor 2
      #else
        Serial.println("Sonido detectado por el Sensor 2 Derecha!");  // Envía un mensaje por Bluetooth para el Sensor 2
      #endif
   }

   if (value3 > 400) { 
      digitalWrite(LED, HIGH);  // Enciende el LED si el tercer sensor detecta sonido (atrás)
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
        Serial1.println("Sonido detectado por el Sensor 3 Atrás!");  // Envía un mensaje por Bluetooth para el Sensor 3
      #else
        Serial.println("Sonido detectado por el Sensor 3 Atrás!");  // Envía un mensaje por Bluetooth para el Sensor 3
      #endif
   }

   if (value4 > 400) { 
      digitalWrite(LED, HIGH);  // Enciende el LED si el cuarto sensor detecta sonido (izquierda)
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
        Serial1.println("Sonido detectado por el Sensor 4 Izquierda!");  // Envía un mensaje por Bluetooth para el Sensor 4
      #else
        Serial.println("Sonido detectado por el Sensor 4 Izquierda!");  // Envía un mensaje por Bluetooth para el Sensor 4
      #endif
   }

   if (value1 <= 400 && value2 <= 400 && value3 <= 400 && value4 <= 400) {
      digitalWrite(LED, LOW);   // Apaga el LED si no se detecta sonido en ninguno de los sensores
   }

   delay(200);
}
