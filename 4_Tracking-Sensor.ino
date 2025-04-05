// Definition der Pins für die Motorsteuerung
#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 7

// Definition der Sensor-Pins
int Sensor1;
int Sensor2;
int Sensor3;
int Sensor4;

void setup() {
  // Motorsteuerungspins als Ausgang konfigurieren
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensor-Pins als Eingang konfigurieren
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  // Serielle Kommunikation initialisieren
  Serial.begin(9600);
}
    
void loop() {
  // Sensorwerte einlesen
  Sensor1 = digitalRead(8);
  Sensor2 = digitalRead(9);
  Sensor3 = digitalRead(10);
  Sensor4 = digitalRead(11);

   // Ausgabe der Sensorwerte zur Überprüfung
  Serial.print("Sensor1: ");
  Serial.print(Sensor1);
  Serial.print(" Sensor2: ");
  Serial.print(Sensor2);
  Serial.print(" Sensor3: ");
  Serial.print(Sensor3);
  Serial.print(" Sensor4: ");
  Serial.println(Sensor4);
 
  // Wenn Sensor 3 oder 4 HIGH und Sensor 1 oder 2 LOW sind, nach links fahren
  if ((Sensor4 == HIGH || Sensor3 == HIGH) && (Sensor2 == LOW || Sensor1 == LOW)) {
    analogWrite(ENA, 120);
    analogWrite(ENB, 120);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("links");
    delay(2000); // Pause für 2 Sekunden, um die Bewegung zu beobachten
  }
  // Wenn Sensor 1 oder 2 HIGH und Sensor 3 oder 4 LOW sind, nach rechts fahren
  else if ((Sensor4 == LOW || Sensor3 == LOW) && (Sensor2 == HIGH || Sensor1 == HIGH)) {
    analogWrite(ENA, 120);
    analogWrite(ENB, 120);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("rechts");
    delay(2000); // Pause für 2 Sekunden, um die Bewegung zu beobachten
  }
  // Wenn alle Sensoren LOW sind, vorwärts fahren
  else if (Sensor4 == LOW && Sensor3 == LOW && Sensor2 == LOW && Sensor1 == LOW) {
    analogWrite(ENA, 120);
    analogWrite(ENB, 120);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("vorwärts");
    delay(2000); // Pause für 2 Sekunden, um die Bewegung zu beobachten
  }
  // Wenn Sensor 2 oder 3 HIGH und Sensor 1 und 4 LOW sind, vorwärts fahren
  else if ((Sensor3 == HIGH || Sensor2 == HIGH) && Sensor4 == LOW && Sensor1 == LOW) {
    analogWrite(ENA, 120);
    analogWrite(ENB, 120);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("vorwärts");
    delay(2000); // Pause für 2 Sekunden, um die Bewegung zu beobachten
  }
  // In allen anderen Fällen anhalten
  else {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(2000); // Pause für 2 Sekunden, um die Bewegung zu beobachten
  }
  // Kurze Pause für Stabilität
  delay(1000);
}