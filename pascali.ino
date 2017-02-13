// pascali intelligent pump controller
// -----------------------------------
// Version 0.1
//
// Functionality
// -------------
// Read pressure sensor and:
// - convert to MPa and display
// - if pressure lower than floor value: start pump
// - if pressure value lower than floor value and pump running
//   for more than 60 seconds : error state
// - if pressure higher that ceiling and pump running: stop pump
//
// To Do
// -----
// - LED display
// - Relay timers
// - Pump current sensor
// - State LEDs (solid green = idle, pulsing green = pump running, red = error)
// - remove delays

// User adjustable parameters
const float low  = 2.0; // MPa
const float high = 3.5; // MPa
const int pressurePin = A0;
const int relayPin = 10;

// Constants and code
const int offset = 20;      // zero pressure adjust
const int fullScale = 1023; // max pressure (span) adjust

// TODO: pin as parameter
float getPressure(const int pin) {
    float reading = analogRead(pin);
    float result = (reading - offset) * 1.2 / (fullScale - offset); // MPa conversion
    return result;
}

// true = on, false = off (default)
// TODO: pin as parameter
//       check logic
bool getRelayState(const int pin) {
    bool state = false; // off
    return state;
}

void setup() {
    Serial.begin(115200);
}

void loop() {

    Serial.print("Pressure: ");
    float pressure = getPressure(pressurePin);
    Serial.print(pressure, 1);
    Serial.println(" MPa");
    Serial.print("pump state: ");
    Serial.println(getRelayState(relayPin) == true ? "on" : "off");

    delay(500);
}

