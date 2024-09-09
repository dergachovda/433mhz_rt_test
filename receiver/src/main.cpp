
#include <RCSwitch.h>

#define LED_PIN 2
#define RX_PIN 15

const String CLOSE_COMMAND = "14649425";
const String OPEN_COMMAND = "14649426";
const String HOME_COMMAND = "14649428";
const String SOS_COMMAND = "14649432";


RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  mySwitch.enableReceive(RX_PIN);
  Serial.println("init done");
}

static String command = "";

void ledOff() { digitalWrite(LED_PIN, LOW); }

void ledOn() { digitalWrite(LED_PIN, HIGH); }

void processCommand(const String& command) {
  if (command == CLOSE_COMMAND) {
    Serial.println("close");
    ledOn();
  } else if (command == OPEN_COMMAND) {
    Serial.println("open");
    ledOff();
  } else if (command == HOME_COMMAND) {
    Serial.println("home");
  } else if (command == SOS_COMMAND) {
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