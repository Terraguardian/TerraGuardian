#define MIC1_PIN A0 //Adelante
#define MIC2_PIN A1 //Derecha
#define MIC3_PIN A2 //Atras
#define MIC4_PIN A3 //Izquierda

int threshold = 500; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  int mic1 = analogRead(MIC1_PIN);
  int mic2 = analogRead(MIC2_PIN);
  int mic3 = analogRead(MIC3_PIN);
  int mic4 = analogRead(MIC4_PIN);

  if (mic1>mic2 && mic1>mic3 && mic1>mic4){
    Serial.println("Se escucha algo adelante");
    delay(2000);
  }else if(mic2>mic1 && mic2>mic3 && mic2>mic4){
    Serial.println("Se escucha algo a la derecha");
    delay(2000);
  }else if (mic3>mic1 && mic3>mic2 && mic3>mic4){
    Serial.println("Se escucha algo atras");
    delay(2000);
  }else{
    Serial.println("Se escucha algo a la izquierda");
    delay(2000);
  }

  // Envía los valores al Serial Plotter
  Serial.print("\tAdelante:");
  Serial.print(mic1);
  Serial.print("\tDerecha:");
  Serial.print(mic2);
  Serial.print("\tAtras:");
  Serial.print(mic3);
  Serial.print("\tIzquierda:");
  Serial.println(mic4);

  delay(100); 
}
