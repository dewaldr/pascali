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
// - State LEDs (solid green = idle, pulsing green = pump on, red = error)
//
// ToDo
// ----
// - pump-on timer
// - Remove delays: event driven?

// User adjustable parameters
const float lowMark  = 2.0; // MPa
const float highMark = 3.5; // MPa
const int pressurePin = A0;
const int currentPin = A1;
const int relayPin = 10;
const int greenLedPin = 8;
const int redLedPin = 9;

// Function prototypes
void setPumpOn(const int pin);
void setPumpOff(const int pin);
float readPressure(const int pin);
float readCurrent(const int pin);

void setup() 
{
    pinMode(relayPin, INPUT);   // Work around state bug
    pinMode(relayPin, OUTPUT);  // relay control
    Serial.begin(9600);
}

void loop() 
{

    Serial.print("Pressure: ");
    float pressure = readPressure(pressurePin);
    Serial.print(pressure, 1);
    Serial.println(" MPa");

    Serial.print("Current: ");
    float current = readCurrent(currentPin);
    Serial.print(current, 1);
    Serial.println(" A");

    Serial.print("pump state: ");
    Serial.println((relayPin /* HIGH */ && (current > 0.5)) == true ? "on" : "off");

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

// Function implementations
void setPumpOn(const int pin) 
{
    digitalWrite(pin, HIGH);
}

void setPumpOff(const int pin) {
    digitalWrite(pin, LOW);
}

// TODO: use RMS
float readPressure(const int pin) 
{
    const int offset = 20;      // zero offset
    const int fullScale = 1023; // max pressure (span) adjust

    float reading = analogRead(pin);
    float result = (reading - offset) * 1.2 / (fullScale - offset); // MPa conversion
    return result;
}

float readCurrent(const int currentPin)
{
    const int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module

    int readValue;             //value read from the sensor
    int maxValue = 0;          // store max value here
    int minValue = 1024;          // store min value here

    uint32_t start_time = millis();
    while((millis()-start_time) < 1000) //sample for 1 Sec
    {
        readValue = analogRead(currentPin);
        // see if you have a new maxValue
        if (readValue > maxValue) 
        {
            /*record the maximum sensor value*/
            maxValue = readValue;
        }
        if (readValue < minValue) 
        {
            /*record the maximum sensor value*/
            minValue = readValue;
        }
    }

    // Subtract min from max
    float voltage = ((maxValue - minValue) * 5.0)/1024.0;
    float rms = (voltage / 2.0) * 0.707; 
    float current = (rms * 1000)/mVperAmp;

    return current;
}


