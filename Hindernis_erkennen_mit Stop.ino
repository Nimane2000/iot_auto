#include <Servo.h>  // Bibliothek für Servo-Motoren

Servo myservo;      // Erstellen eines Servo-Objekts zum Steuern des Servos

int Trig = 12;     // Pin für den Triggersensor
int Echo = 13;    // Pin für den Echosensor

// Pin-Definitionen für die Motorsteuerung
#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 7

// Geschwindigkeit des Autos
int carSpeed = 100;

// Funktion zur Messung der Entfernung mit dem Ultraschallsensor
float GetDistance() {
  float distance;
  
  // Auslösen des Ultraschallsensors
  digitalWrite(Trig, LOW);
  delayMicroseconds(2); 
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  // Berechnung der Entfernung basierend auf der Zeit bis zum Echo
  distance = pulseIn(Echo, HIGH) / 58.00;
    
  return distance;
}

// Funktion zum Vorwärtsfahren
void geradeAus() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Vorwärts");
}

// Funktion zum Rechtsfahren
void rechtsFahren() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Rechts");
}

// Funktion zum Linksfahren
void linksFahren() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Links");
}

// Funktion zum Anhalten
void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("Halt!");
}

// Funktion zur Messung der Entfernungen nach vorne, links und rechts
void measureDistances(float &forwardDistance, float &leftDistance, float &rightDistance) {
  // Messen der Entfernung nach vorne
  myservo.write(90);  // Servo auf 90 Grad (vorne) einstellen
  delay(1000);         // Kurze Wartezeit, damit der Servo seine Position erreicht
  forwardDistance = GetDistance();
  Serial.print("Entfernung nach vorne: ");
  Serial.print(forwardDistance);
  Serial.println(" cm");

  // Messen der Entfernung nach rechts
  myservo.write(0);  // Servo auf 0 Grad (rechts) einstellen
  delay(3000);        // Kurze Wartezeit, damit der Servo seine Position erreicht
  rightDistance = GetDistance();
  Serial.print("Entfernung nach rechts: ");
  Serial.print(rightDistance);
  Serial.println(" cm");

  // Messen der Entfernung nach links
  myservo.write(180);  // Servo auf 180 Grad (links) einstellen
  delay(3000);          // Kurze Wartezeit, damit der Servo seine Position erreicht
  leftDistance = GetDistance();
  Serial.print("Entfernung nach links: ");
  Serial.print(leftDistance);
  Serial.println(" cm");

  // Servo wieder in die mittlere Position zurücksetzen
  myservo.write(90);
  delay(3000);
}

void setup() {
  // Initialisierung des Servos
  myservo.attach(A0, 700, 2400);  
  Serial.begin(9600);

  // Initialisierung der Pins als Eingänge oder Ausgänge
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);

  // Motorpins als Ausgang definieren
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Anfangsstellung des Autos
  stopCar();
}

void loop() {
  float forwardDistance, leftDistance, rightDistance;

  // Messen und Ausgeben der Entfernungen
  measureDistances(forwardDistance, leftDistance, rightDistance);
  
  if (forwardDistance > 20) {
    // Vorwärtsfahren für 2 Sekunden
    geradeAus();
    delay(2000);
    stopCar();
  } else if (rightDistance > 20) {
    // Rechtsfahren für 2 Sekunden
    rechtsFahren();
    delay(2000);
    stopCar();
  } else if (leftDistance > 20) {
    // Linksfahren für 2 Sekunden
    linksFahren();
    delay(2000);
    stopCar();
  } else {
    // Wenn kein Weg frei ist, anhalten
    stopCar();
  }

  // Kurze Pause zwischen den Messungen
  delay(2000);
}

