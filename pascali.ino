// pascali intelligent pump controller
// -----------------------------------
// Version 0.1
//
// Functionality
// -------------
// Read pressure sensor and:
// - if pressure < floor: pump-on
// - if pressure < floor & pump-on time > 120s => error (oow)
// - if pressure >= ceiling and pump-on => pump-off
//
// To Do
// -----
// - pump-on timer
// - State LEDs (solid green = idle, pulsing green = pump on, red = error)
// - Remove delays: event driven?
// - Pump current sensor

// User adjustable parameters
const float lowMark  = 2.0; // MPa
const float highMark = 3.5; // MPa
const int pressurePin = A0;
const int currentPin = A1;
const int relayPin = 10;

// Constants
const int offset = 20;      // zero offset
const int fullScale = 1023; // max pressure (span) adjust

// TODO: use running average
float getPressure(const int pin) {
    float reading = analogRead(pin);
    float result = (reading - offset) * 1.2 / (fullScale - offset); // MPa conversion
    return result;
}

float getCurrent(const int pin) {
    float reading = analogRead(pin);
    float result = (reading - offset) * 1.2 / (fullScale - offset);
    return result;
}

void setPumpOn(const int pin) {
    digitalWrite(pin, HIGH);
}

void setPumpOff(const int pin) {
    digitalWrite(pin, LOW);
}

// Global functions

bool isPumpRunning(const int relay_pin, const int current_pin) {
    bool state = false;
    if (digitalRead(relay_pin) /* is HIGH */ && getCurrent(current_pin) > 0.1) {
        state = true;
    }
    return state;
}

void setup() {
    pinMode(relayPin, INPUT);   // Work around bug
    pinMode(relayPin, OUTPUT);  // relay control
    Serial.begin(115200);
}

void loop() {

    Serial.print("Pressure: ");
    float pressure = getPressure(pressurePin);
    Serial.print(pressure, 1);
    Serial.println(" MPa");
    Serial.print("pump state: ");
    Serial.println(isPumpRunning(relayPin, currentPin) == true ? "on" : "off");

    if (pressure < lowMark) {
        // check is pump already running -> error
        setPumpOn(relayPin);
    }
    else if (pressure > highMark) {
        setPumpOff(relayPin);
    }
    // check pump run time + compare with pressure differential

    delay(250);
}

