clear;
% Verbindung zum Arduino herstellen
a = arduino('COM9', 'Uno', 'Libraries', 'Servo');

% Definition der Pins für die Motorsteuerung
ENA = 'D5';
ENB = 'D6';
IN1 = 'D3';
IN2 = 'D4';
IN3 = 'D2';
IN4 = 'D7';

% Definition der Pins für die Sensoren
sensorPins = {'D8', 'D9', 'D10', 'D11'};

% Pins als Ausgang konfigurieren
configurePin(a, ENA, 'PWM');
configurePin(a, ENB, 'PWM');
configurePin(a, IN1, 'DigitalOutput');
configurePin(a, IN2, 'DigitalOutput');
configurePin(a, IN3, 'DigitalOutput');
configurePin(a, IN4, 'DigitalOutput');

% Sensor-Pins als Eingang konfigurieren
for i = 1:length(sensorPins)
    configurePin(a, sensorPins{i}, 'DigitalInput');
end

% Funktion zur Steuerung des Autos
function driveCar(a, ENA, ENB, IN1, IN2, IN3, IN4, direction)
    switch direction
        case 'forward'
            writePWMVoltage(a, ENA, 5 * (120 / 255));
            writePWMVoltage(a, ENB, 5 * (120 / 255));
            writeDigitalPin(a, IN1, 1);
            writeDigitalPin(a, IN2, 0);
            writeDigitalPin(a, IN3, 1);
            writeDigitalPin(a, IN4, 0);
        case 'left'
            writePWMVoltage(a, ENA, 5 * (120 / 255));
            writePWMVoltage(a, ENB, 5 * (120 / 255));
            writeDigitalPin(a, IN1, 0);
            writeDigitalPin(a, IN2, 1);
            writeDigitalPin(a, IN3, 1);
            writeDigitalPin(a, IN4, 0);
        case 'right'
            writePWMVoltage(a, ENA, 5 * (120 / 255));
            writePWMVoltage(a, ENB, 5 * (120 / 255));
            writeDigitalPin(a, IN1, 1);
            writeDigitalPin(a, IN2, 0);
            writeDigitalPin(a, IN3, 0);
            writeDigitalPin(a, IN4, 1);
        case 'stop'
            writePWMVoltage(a, ENA, 0);
            writePWMVoltage(a, ENB, 0);
            writeDigitalPin(a, IN1, 0);
            writeDigitalPin(a, IN2, 0);
            writeDigitalPin(a, IN3, 0);
            writeDigitalPin(a, IN4, 0);
    end
end

% Hauptschleife
while true
    % Sensorwerte einlesen
    Sensor1 = readDigitalPin(a, sensorPins{1});
    Sensor2 = readDigitalPin(a, sensorPins{2});
    Sensor3 = readDigitalPin(a, sensorPins{3});
    Sensor4 = readDigitalPin(a, sensorPins{4});

    % Ausgabe der Sensorwerte zur Überprüfung
    fprintf('Sensor1: %d Sensor2: %d Sensor3: %d Sensor4: %d\n', Sensor1, Sensor2, Sensor3, Sensor4);

    % Steuerlogik für die Bewegung des Autos
    if ((Sensor4 == 1 || Sensor3 == 1) && (Sensor2 == 0 || Sensor1 == 0))
        driveCar(a, ENA, ENB, IN1, IN2, IN3, IN4, 'left');
        disp('links');
        pause(2); % Pause für 2 Sekunden, um die Bewegung zu beobachten
    elseif ((Sensor4 == 0 || Sensor3 == 0) && (Sensor2 == 1 || Sensor1 == 1))
        driveCar(a, ENA, ENB, IN1, IN2, IN3, IN4, 'right');
        disp('rechts');
        pause(2); % Pause für 2 Sekunden, um die Bewegung zu beobachten
    elseif (Sensor4 == 0 && Sensor3 == 0 && Sensor2 == 0 && Sensor1 == 0)
        driveCar(a, ENA, ENB, IN1, IN2, IN3, IN4, 'forward');
        disp('vorwärts');
        pause(2); % Pause für 2 Sekunden, um die Bewegung zu beobachten
    elseif ((Sensor3 == 1 || Sensor2 == 1) && Sensor4 == 0 && Sensor1 == 0)
        driveCar(a, ENA, ENB, IN1, IN2, IN3, IN4, 'forward');
        disp('vorwärts');
        pause(2); % Pause für 2 Sekunden, um die Bewegung zu beobachten
    else
        driveCar(a, ENA, ENB, IN1, IN2, IN3, IN4, 'stop');
        disp('stop');
        pause(2); % Pause für 2 Sekunden, um die Bewegung zu beobachten
    end
    % Kurze Pause für Stabilität
    pause(1);
end
