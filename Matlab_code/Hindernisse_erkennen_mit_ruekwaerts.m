clear all;

% Verbindung zum Arduino herstellen
a = arduino('COM9', 'Uno', 'Libraries', {'Servo', 'Ultrasonic'});

% Servo-Objekt erstellen
s = servo(a, 'A0', 'MinPulseDuration', 700e-6, 'MaxPulseDuration', 2400e-6);

% Ultrasonic-Sensor-Objekt erstellen
ultrasonicSensor = ultrasonic(a, 'D12', 'D13'); % Verwende Pin D12 für Trigger und D13 für Echo

% Definition der Pins für die Motorsteuerung
ENA = 'D5';
ENB = 'D6';
IN1 = 'D3';
IN2 = 'D4';
IN3 = 'D2';
IN4 = 'D7'; % Verwende Pin D7 für IN4

% Definition der Geschwindigkeit des Autos
carSpeed = 125/250; % Normierung auf [0, 1]

% Pins als Ausgang definieren
configurePin(a, IN1, 'DigitalOutput');
configurePin(a, IN2, 'DigitalOutput');
configurePin(a, IN3, 'DigitalOutput');
configurePin(a, IN4, 'DigitalOutput');
configurePin(a, ENA, 'PWM');
configurePin(a, ENB, 'PWM');

% Funktion zum Vorwärtsfahren
function geradeAus(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed)
    % Setzen der Geschwindigkeit für die Motoren
    writePWMVoltage(a, ENA, carSpeed * 5);
    writePWMVoltage(a, ENB, carSpeed * 5);

    % Steuerung der Motoren zum Vorwärtsfahren
    writeDigitalPin(a, IN1, 1);
    writeDigitalPin(a, IN2, 0);
    writeDigitalPin(a, IN3, 1);
    writeDigitalPin(a, IN4, 0);

    disp('Vorwärts');
end

% Funktion zum Rechtsfahren
function rechtsFahren(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed)
    % Setzen der Geschwindigkeit für die Motoren
    writePWMVoltage(a, ENA, carSpeed * 5);
    writePWMVoltage(a, ENB, carSpeed * 5);

    % Steuerung der Motoren zum Rechtsfahren
    writeDigitalPin(a, IN1, 1);
    writeDigitalPin(a, IN2, 0);
    writeDigitalPin(a, IN3, 0);
    writeDigitalPin(a, IN4, 1);

    disp('Rechts');
end

% Funktion zum Linksfahren
function linksFahren(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed)
    % Setzen der Geschwindigkeit für die Motoren
    writePWMVoltage(a, ENA, carSpeed * 5);
    writePWMVoltage(a, ENB, carSpeed * 5);

    % Steuerung der Motoren zum Linksfahren
    writeDigitalPin(a, IN1, 0);
    writeDigitalPin(a, IN2, 1);
    writeDigitalPin(a, IN3, 1);
    writeDigitalPin(a, IN4, 0);

    disp('Links');
end

% Funktion zum Rückwärtsfahren
function rueckfahren(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed)
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

% Funktion zur Distanzmessung
function distance = measureDistance(sensor)
    distance = readDistance(sensor) * 100; % Umwandlung in cm
    if isnan(distance) || distance == Inf
        distance = -1; % Setze ungültige Messungen auf -1
    end
end

% Anfangsstellung des Autos
stop(a, ENA, ENB);
writePosition(s, 0.5); % Mittelstellung
pause(5); % Längere Pause, um sicherzustellen, dass der Servo in Position ist

% Hauptschleife
while true
    % Distanz nach vorne messen
    forwardDistance = measureDistance(ultrasonicSensor);
    fprintf('Vorwärts Distanz: %.2f cm\n', forwardDistance);

    if forwardDistance > 20
        % Vorwärtsfahren für 2 Sekunden
        geradeAus(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed);
        pause(2);
        stop(a, ENA, ENB);
    else
        % Servo nach rechts drehen und Distanz messen
        writePosition(s, 1); % Rechtsstellung
        pause(2); % Längere Pause, um sicherzustellen, dass der Servo in Position ist
        rightDistance = measureDistance(ultrasonicSensor);
        fprintf('Rechts Distanz: %.2f cm\n', rightDistance);

        if rightDistance > 20
            % Rechtsfahren für 2 Sekunden
            rechtsFahren(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed);
            pause(2);
            stop(a, ENA, ENB);
        else
            % Servo nach links drehen und Distanz messen
            writePosition(s, 0); % Linksstellung
            pause(2); % Längere Pause, um sicherzustellen, dass der Servo in Position ist
            leftDistance = measureDistance(ultrasonicSensor);
            fprintf('Links Distanz: %.2f cm\n', leftDistance);

            if leftDistance > 20
                % Linksfahren für 2 Sekunden
                linksFahren(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed);
                pause(2);
                stop(a, ENA, ENB);
            else
                % Rechtsfahren für 2 Sekunden
                rueckfahren(a, ENA, ENB, IN1, IN2, IN3, IN4, carSpeed);
                pause(2);
                stop(a, ENA, ENB);
            end
        end
    end

   

    % Servo zurück zur Mittelstellung
    writePosition(s, 0.5);
    pause(4); % Längere Pause, um sicherzustellen, dass der Servo in Position ist
end
