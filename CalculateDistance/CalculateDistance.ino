#include <Servo.h>  // Bibliothek für Servo-Motoren

Servo myservo;      // Erstellen eines Servo-Objekts zum Steuern des Servos

int Trig = 12;     // Pin für den Triggersensor
int Echo = 13;    // Pin für den Echosensor

// Funktion zur Messung der Entfernung mit dem Ultraschallsensor
float GetDistance()
{
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

// Funktion zur Messung der Entfernungen nach vorne, links und rechts
void measureDistances() {
  float forwardDistance, leftDistance, rightDistance;

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
}

void loop() 
{
  // Messen und Ausgeben der Entfernungen
  measureDistances();
  
  // Kurze Pause zwischen den Messungen
  delay(2000);
}
