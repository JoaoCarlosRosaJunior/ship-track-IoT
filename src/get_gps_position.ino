#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serial1(10, 11);  // RX, TX
TinyGPS gps1;

// Setting up timers
volatile bool timerFlag = false;

long lat, lng;

static const int deviceId = 1;

void setup() {
  serial1.begin(9600);
  Serial.begin(9600);

  Serial.println("Waiting for satellite signal");

  // Set up Timer1 for interrupt every 1 second
  cli();                               // Disable interrupts
  TCCR1A = 0;                          // Set Timer1 to normal mode
  TCCR1B = (1 << CS12) | (1 << CS10);  // Set prescaler to 1024
  OCR1A = 15625;                       // Set compare value for 1 second
  TIMSK1 = (1 << OCIE1A);              // Enable Timer1 compare interrupt
  sei();                               // Enable interrupts
}

void loop() {
  bool recebido = false;

  while (serial1.available()) {
    char cIn = serial1.read();
    recebido = gps1.encode(cIn);
  }

  if (recebido) {
    //Latitude and Longitude
    long latitude, longitude;
    gps1.get_position(&latitude, &longitude);
    lat = latitude;
    lng = longitude;
  }

  // Check timer flag and execute code every 10 seconds
  if (timerFlag) {
    timerFlag = false;  // Reset timer flag
                        // Insert code to be executed every 10 seconds here
      Serial.print(lat * 10);
      Serial.print(",");
      Serial.print(lng * 10);
      Serial.print(",");
      Serial.print(deviceId);
      Serial.println();
  }
}

// ISR for Timer1 compare match interrupt
ISR(TIMER1_COMPA_vect) {
  timerFlag = true;  // Set timer flag
}
