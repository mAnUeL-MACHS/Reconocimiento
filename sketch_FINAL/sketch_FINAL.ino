int led1 = 7;
int led2 = 8;
int led3 = 12;
int led4 = 10;
int led5 = 9;
int buzzerPin = 11; // Asigna el pin del buzzer
int option;
bool executed = false; // Variable para controlar si se ejecutó o no
unsigned long executionTime = 0; // Variable para controlar el tiempo de espera
int counter = 0; // Contador para la letra 'N'

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (Serial.available() > 0 && !executed) { // Se ejecuta si hay datos disponibles y no se ha ejecutado aún
    option = Serial.read();
    Serial.println(option);
    if (option == 'P') {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      delay(1200);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      delay(7000);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led5, HIGH);
      delay(1200);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led5, LOW);
      executed = true; // Se marca como ejecutado
      executionTime = currentMillis; // Se guarda el tiempo actual
      Serial.end(); // Se cierra el puerto serial
    } else if (option == 'N') {
      digitalWrite(led4, HIGH);
      delay(2000);
      digitalWrite(led4, LOW);
      counter++; // Incrementa el contador al recibir 'N'

      // Si el contador llega a 3, activa el led4 y el buzzer
      if (counter == 3) {
        digitalWrite(led4, HIGH);
        tone(buzzerPin, 1000); // Activa el buzzer a 1000Hz
        counter = 0; // Reinicia el contador
      }
      executed = true; // Se marca como ejecutado
      executionTime = currentMillis; 
      Serial.end(); 
    }
    digitalWrite(led4, HIGH);
    delay(15000);
    digitalWrite(led4, LOW);
  }

  // Si ya se ha ejecutado y han pasado 15 segundos, se reinicia la variable executed
  if (executed && (currentMillis - executionTime >= 15000)) {
    executed = false;
     
    //counter = 0; // Reinicia el contador
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    noTone(buzzerPin); // Detiene el sonido del buzzer
    Serial.begin(9600); 
  }
}
