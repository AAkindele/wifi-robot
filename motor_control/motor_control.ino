#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

#define ADAFRUIT_CC3000_IRQ  3
#define ADAFRUIT_CC3000_VBAT 5
#define ADAFRUIT_CC3000_CS   10
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);

#define WLAN_SSID "ssid"

#define WLAN_SECURITY WLAN_SEC_WPA2

#define WEBSITE "192.168.0.8"
#define WEBPAGE "/commands"

#define IDLE_TIMEOUT_MS  3000

uint32_t ipAddress = cc3000.IP2U32(192, 168, 0, 8);
Adafruit_CC3000_Client www;

void setup(void)
{
  Serial.begin(115200);

  Serial.println("Disconnecting");
  cc3000.disconnect();

  Serial.println("Initializing...");
  cc3000.begin();

  Serial.println("enter password");
  String pass;
  while(Serial.available() == 0) {}
  while(Serial.available() > 0) {
    pass = Serial.readString();
  }
  char passChar[pass.length()];
  pass.toCharArray(passChar, (pass.length() + 1));

  Serial.print("Attempting to connect to ");
  Serial.println(WLAN_SSID);
  cc3000.connectToAP(WLAN_SSID, passChar, WLAN_SECURITY);
  Serial.println("Connected!");
}

void loop(void){
  www = cc3000.connectTCP(ipAddress, 5000);
  if (www.connected()) {
    www.fastrprint("GET ");
    www.fastrprint(WEBPAGE);
    www.fastrprint(" HTTP/1.1\r\n");
    www.fastrprint("Host: "); www.fastrprint(WEBSITE); www.fastrprint("\r\n");
    www.fastrprint("\r\n");
    www.println();
  }
  else {
    Serial.println("Connection failed");
    return;
  }

  // Read data until either the connection is closed, or the idle timeout is reached.
  unsigned long lastRead = millis();
  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    while (www.available()) {
      char c = www.read();
      Serial.print(c);
      lastRead = millis();
    }
  }
  www.close();
}
