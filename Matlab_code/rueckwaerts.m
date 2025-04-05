clear all;

% Verbindung zum Arduino herstellen
a = arduino('COM9', 'Uno', 'Libraries', 'Servo');

% Servo-Objekt erstellen
s = servo(a, 'A0', 'MinPulseDuration', 700e-6, 'MaxPulseDuration', 2400e-6);

% Definition der Pins für die Motorsteuerung
ENA = 'D5';
ENB = 'D6';
IN1 = 'D3';
IN2 = 'D4';
IN3 = 'D2';
IN4 = 'D7';

% Definition der Geschwindigkeit des Autos
carSpeed = 125 / 255; % Normierung auf [0, 1]

% Pins als Ausgang definieren
configurePin(a, IN1, 'DigitalOutput');
configurePin(a, IN2, 'DigitalOutput');
configurePin(a, IN3, 'DigitalOutput');
configurePin(a, IN4, 'DigitalOutput');
configurePin(a, ENA, 'PWM');
configurePin(a, ENB, 'PWM');

% Funktion zum Rückwärtsfahren
function rueckwaerts(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed)
    % Setzen der Geschwindigkeit für die Motoren
    writePWMVoltage(a, ENA, carSpeed * 5);
    writePWMVoltage(a, ENB, carSpeed * 5);
  
    % Steuerung der Motoren zum Rückwärtsfahren
    writeDigitalPin(a, IN1, 0);
    writeDigitalPin(a, IN2, 1);
    writeDigitalPin(a, IN3, 0);
    writeDigitalPin(a, IN4, 1);

    disp('Rückwärts');
end

% Funktion zum Anhalten
function stop(a, ENA, ENB)
    % Setzen der Geschwindigkeit für die Motoren auf Null
    writePWMVoltage(a, ENA, 0);
    writePWMVoltage(a, ENB, 0);
  
    disp('Halt!');
end

% Anfangsstellung des Autos
stop(a, ENA, ENB);
writePosition(s, 0.5); % Mittelstellung
pause(0.1);

% Hauptschleife
while true
    % Das Auto fährt einmal für 2 Sekunden rückwärts
    rueckwaerts(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed);
    pause(2);

    % Das Auto hält für 10 Sekunden an
    stop(a, ENA, ENB);
    pause(10);
end