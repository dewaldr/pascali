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

