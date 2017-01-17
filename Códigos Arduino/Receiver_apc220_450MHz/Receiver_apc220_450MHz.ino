// RX 450MHz
int LED3 = 5; //Conectar LED VERDE
int LED2 = 6; //Conectar LED ROJO
int LED1 = 7; //Conectar LED AMARILLO
const byte SetPin = 4; //Pin para poner el APC220 en modo de configuración

int Frecuencia = 450; //Ajustar frecuencia a de recepcion

void setup() {
  Serial.begin(57600);
  //Configuracion de pines para los LED como salidas
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(SetPin, OUTPUT);
  
  digitalWrite(SetPin, HIGH); //Se ajusta el Pin SET del modulo RF en Alto
  SelectFreq(); //Configuracion del modulo
  delay(100);
  SelectFreq(); /* Segunda configuracion del modulo, 
                 * que asegura que la frecuencia fue seteada de manera correcta
                 */  
}

void loop() {
  if (Serial.available()) {
    int DataIn = Serial.read();
    //Separacion de los valores de cada LED
    bool LED1_s = DataIn & 0x04;
    bool LED2_s = DataIn & 0x02;
    bool LED3_s = DataIn & 0x01;
    //Impresion de los valores recibidos
    digitalWrite(LED1, LED1_s);
    digitalWrite(LED2, LED2_s);
    digitalWrite(LED3, LED3_s);
  }
}

void SelectFreq() {
  // Procedimiento de configuración de la frecuencia de recpecion
  Serial.println();
  Serial.println("Configurando a "+String(Frecuencia)+"MHz ...");
  digitalWrite(SetPin, LOW);
  delay(2);
  Serial.end();
  Serial.begin(9600);
  Serial.println("WR "+String(Frecuencia)+"000 4 9 6 0");
  delay(201);

  if (Serial.available())
  {
    String data = Serial.readString();
    Serial.println(data);
  }
  digitalWrite(SetPin, HIGH);
  delay(11);
  Serial.end();
  Serial.begin(57600);
  Serial.println("Configurado!!!");
}
