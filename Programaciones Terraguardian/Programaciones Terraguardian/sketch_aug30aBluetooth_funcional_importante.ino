#define PIN_SOUND_SENSOR_1 A0  // Definir el pin del primer sensor de sonido (adelante)
#define PIN_SOUND_SENSOR_2 A1  // Definir el pin del segundo sensor de sonido (derecha)
#define PIN_SOUND_SENSOR_3 A2  // Definir el pin del tercer sensor de sonido (atrás)
#define PIN_SOUND_SENSOR_4 A3  // Definir el pin del cuarto sensor de sonido (izquierda)
#define PIN_MQ2 A4             // Definir el pin del sensor MQ2
#define LED                 9  // Definir el pin del LED

int value1, value2, value3, value4, gasValue;

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
  pinMode(PIN_MQ2, INPUT);
}

void loop() {
   // Lee los valores de los sensores de sonido
   value1 = analogRead(PIN_SOUND_SENSOR_1);  // Adelante
   value2 = analogRead(PIN_SOUND_SENSOR_2);  // Derecha
   value3 = analogRead(PIN_SOUND_SENSOR_3);  // Atrás
   value4 = analogRead(PIN_SOUND_SENSOR_4);  // Izquierda
   gasValue = analogRead(PIN_MQ2);           // Lee el valor del sensor MQ2
    delay(2000);
   // Sensores de sonido
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

   // Sensor MQ2
   if (gasValue > 400) { 
      digitalWrite(LED, HIGH);  // Enciende el LED si el sensor de gas detecta un valor alto
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
        Serial1.println("Valores de ICA dañinos para su salud!");  // Envía un mensaje por Bluetooth para el sensor de gas
      #else
        Serial.println("Valores de ICA dañinos para su salud!");  // Envía un mensaje por Bluetooth para el sensor de gas
      #endif
   }else{
    Serial.println("Ambiente libre de gases extraños!");  // Envía un mensaje por Bluetooth para el sensor de gas
   }

   // Apagar el LED si no se detecta sonido ni gas inusual
   if (value1 <= 400 && value2 <= 400 && value3 <= 400 && value4 <= 400 && gasValue <= 400) {
      digitalWrite(LED, LOW);   // Apaga el LED
   }

   delay(200);
}
