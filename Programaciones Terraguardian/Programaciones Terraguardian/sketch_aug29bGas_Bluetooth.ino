#define PIN_MQ2 A4
#define LED     9 

int value;

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serial para el monitor serie
  // Asegúrate de que tu placa tenga un puerto Serial1 o cambia Serial1 a Serial si estás usando un Arduino Uno o Nano.
  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
    Serial1.begin(9600); // Inicia la comunicación serial para Bluetooth en placas con más de un puerto serial
  #endif
  pinMode(LED, OUTPUT);
  pinMode(PIN_MQ2, INPUT);
}

void loop() {
   value = analogRead(PIN_MQ2);  // Lee el valor del sensor MQ2

   Serial.println("VALOR - " + String(value));  // Muestra el valor en el monitor serie

   if (value > 400) { 
      digitalWrite(LED, HIGH);  // Enciende el LED
      #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ARDUINO_SAM_DUE)
        Serial1.println("Se ha detectado un gas inusual!");  // Envía un mensaje por Bluetooth en placas con más de un puerto serial
      #else
        Serial.println("Se ha detectado un gas inusual!");  // Envía un mensaje por Bluetooth usando el puerto serial estándar
      #endif
   } else { 
      digitalWrite(LED, LOW);   // Apaga el LED
   }

   delay(200);
}
