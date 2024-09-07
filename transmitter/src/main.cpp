#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile

#include "Arduino.h"

// Define RX and TX pins
const int RX_PIN = 12;
const int TX_PIN = 13;
const int SEND_MESSAGE_INTERVAL = 5000;

// Initialize the driver with custom RX and TX pins
RH_ASK driver(2000, RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);

  if (!driver.init())  // Initialize the driver
    Serial.println("init failed");

  Serial.println("init success");
}

void recive() {
  // Receiver code
  //   uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  Serial.print(".");
  if (driver.recv(buf, &buflen)) {  // Non-blocking receive
    Serial.print("Received: ");
    Serial.write(buf, buflen);
    Serial.println();
  }
}

void transmit() {
  static unsigned long lastSend = 0;
  if (millis() - lastSend > SEND_MESSAGE_INTERVAL) {
    lastSend = millis();
    // Transmitter code
    const char *msg = "Hello!";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();

    // print the message sent with exac message
    Serial.print("Sending message: ");
    Serial.println(msg);
  }
}

void loop() {
  transmit();
  // recive();
  // delay(10);
}
