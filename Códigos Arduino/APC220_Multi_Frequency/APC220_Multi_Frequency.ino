// TX
const byte SetPin = 13; //Pin para poner el APC220 en modo de configuración
const byte interruptPin = 2; //Selección de la Frecuencia

volatile int Freq = 0;
int Frecuencia1 = 420; //Primera frecuencia a configurar
int Frecuencia2 = 435; //Segunda frecuencia a configurar
int Frecuencia3 = 450; //Tercera frecuencia a configurar

volatile byte Configured = LOW; //El Módulo ha sido configurado
  
volatile unsigned long last_micros;
long debouncing_time = 175; //Debouncing Time in Milliseconds

uint8_t data = 0,x = 0;

void setup() {
  Serial.begin(57600);
  Serial1.begin(57600);
  pinMode(SetPin, OUTPUT);

  //Interrupciones
  pinMode(2, INPUT_PULLUP);

  //Mensaje Inicial
  Serial.println();
  Serial.println("Transmisor Multifrecuencia con APC220");
  Serial.println("-------------------------------------");
  Serial.println("Frecuencia inicial: "+String(Frecuencia1)+"MHz");

  //Configuración Inicial del APC220
  digitalWrite(SetPin, HIGH);
  SelectFreq1();
  delay(100);

  //SelectFreq();
  attachInterrupt(digitalPinToInterrupt(2), Interrupt1, FALLING);
}

void loop() {
  if (Configured == LOW) {
    if (Freq == 0) {
      SelectFreq1();
    }
    else if (Freq == 1) {
      SelectFreq2();
    }
    else if (Freq == 2) {
      SelectFreq3();
    }
  }

  Serial1.write(data);
  delay(1);
  x++;
  if(x==100)
  {
    data++;
    x=0;
  }
  if (data >= 7) {
    data = 0;
  }
}

void Interrupt1() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {
    last_micros = micros();
    Configured = LOW;
    Freq = Freq + 1;
    if (Freq == 3) {
      Freq = 0;
    }
  }
}

void SelectFreq1() {
  // Procedimiento de configuración a la primera frecuencia
  Serial.println();
  Serial.println("-------------------------------------");
  Serial.println("Configurando a " + String(Frecuencia1) + "MHz ...");
  digitalWrite(SetPin, LOW);
  delay(2);
  Serial1.end();
  Serial1.begin(9600);
  Serial1.println("WR " + String(Frecuencia1) + "000 4 9 6 0");
  delay(201);

  if (Serial1.available())
  {
    String data = Serial1.readString();
    Serial.println(data);
  }
  digitalWrite(SetPin, HIGH);
  delay(11);
  Serial1.end();
  Serial1.begin(57600);
  Serial.println("Configurado!!!");
  Configured = HIGH;
  Serial.println();
  Serial.println("Transmitiendo a "+String(Frecuencia1)+"MHZ...");
}

void SelectFreq2() {
  //Procedimiento de configuración a la segunda frecuencia
  Serial.println();
  Serial.println("-------------------------------------");
  Serial.println("Configurando a " + String(Frecuencia2) + "MHz ...");
  digitalWrite(SetPin, LOW);
  delay(2);
  Serial1.end();
  Serial1.begin(9600);
  Serial1.println("WR " + String(Frecuencia2) + "000 4 9 6 0");
  delay(201);

  if (Serial1.available())
  {
    String data = Serial1.readString();
    Serial.println(data);
  }
  digitalWrite(SetPin, HIGH);
  delay(11);
  Serial1.end();
  Serial1.begin(57600);
  Serial.println("Configurado!!!");
  Configured = HIGH;
  Serial.println();
  Serial.println("Transmitiendo a "+String(Frecuencia2)+"MHZ...");
}

void SelectFreq3() {
  // Procedimiento de configuración a la tercera frecuencia
  Serial.println();
  Serial.println("-------------------------------------");
  Serial.println("Configurando a " + String(Frecuencia3) + "MHz ...");
  digitalWrite(SetPin, LOW);
  delay(2);
  Serial1.end();
  Serial1.begin(9600);
  Serial1.println("WR " + String(Frecuencia3) + "000 4 9 6 0");
  delay(201);

  if (Serial1.available())
  {
    String data = Serial1.readString();
    Serial.println(data);
  }
  digitalWrite(SetPin, HIGH);
  delay(11);
  Serial1.end();
  Serial1.begin(57600);
  Serial.println("Configurado!!!");
  Configured = HIGH;
  Serial.println();
  Serial.println("Transmitiendo a "+String(Frecuencia3)+"MHZ...");
}

