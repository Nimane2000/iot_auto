#include <Servo.h>  // Bibliothek für Servo-Motoren

Servo myservo;      // Erstellen eines Servo-Objekts zum Steuern des Servos

// Definition der Pins für die Motorsteuerung
#define ENA  5 
#define ENB  6       
#define IN1  3      
#define IN2  4    
#define IN3  2    
#define IN4  7    

// Definition der Geschwindigkeit des Autos
#define carSpeed 130

// Funktion zum Linksabbiegen
void gehNachLinks() { 
  // Setzen der Geschwindigkeit für die Motoren
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  
  // Steuerung der Motoren zum Linksabbiegen
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.println("Rechts");
}

// Funktion zum Anhalten
void stop() { 
  // Setzen der Geschwindigkeit für die Motoren auf Null
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  
  Serial.println("Halt!");
}

void setup() {
  // Initialisierung des Servos
  myservo.attach(A0, 700, 2400);  
  Serial.begin(9600);

  // Initialisierung der Pins als Eingänge oder Ausgänge
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Anfangsstellung des Autos
  stop();
  myservo.write(100);  
  delay(100);
}

void loop() 
{
  // Das Auto fährt einmal für 2 Sekunden nach links
  gehNachLinks();
  delay(2000);

  // Das Auto hält für 2 Sekunden an
  stop();
  delay(2000);
}
