
#include <RCSwitch.h>

// define the onboard arduino uno led
#define LED_PIN 13

RCSwitch mySwitch = RCSwitch();
// 14649425 - close
// 14649426 - open
// 14649428 - home
// 14649432 - sos

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  Serial.println("init done");
}

static String command = "";

void ledOff() { digitalWrite(LED_PIN, LOW); }

void ledOn() { digitalWrite(LED_PIN, HIGH); }

void processCommand(const String& command) {
  if (command == "14649425") {
    Serial.println("close");
    ledOn();
  } else if (command == "14649426") {
    Serial.println("open");
    ledOff();
  } else if (command == "14649428") {
    Serial.println("home");
  } else if (command == "14649432") {
    Serial.println("sos");
  }
}

void loop() {
  if (mySwitch.available()) {
    Serial.print("Received ");
    Serial.print(mySwitch.getReceivedValue());
    Serial.print(" / ");
    Serial.print(mySwitch.getReceivedBitlength());
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println(mySwitch.getReceivedProtocol());

    command = String(mySwitch.getReceivedValue());
    mySwitch.resetAvailable();

    processCommand(command);
  }
}