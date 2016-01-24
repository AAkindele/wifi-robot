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

#define WEBSITE "www.adafruit.com"
#define WEBPAGE "/testwifi/index.html"

void setup(void)
{
  Serial.begin(115200);

  Serial.println("\nInitializing...");
  cc3000.begin();

  Serial.println("enter password");
  String pass;
  while(Serial.available() == 0) {}
  while(Serial.available() > 0) {
    pass = Serial.readString();
  }
  char passChar[pass.length()];
  pass.toCharArray(passChar, (pass.length() + 1));

  Serial.print("\nAttempting to connect to "); Serial.println(WLAN_SSID);
  cc3000.connectToAP(WLAN_SSID, passChar, WLAN_SECURITY);

  Serial.println("Connected!");
/*
  // Wait for DHCP to complete 
  Serial.println("Request DHCP");
  cc3000.checkDHCP();
*/
  // You need to make sure to clean up after yourself or the CC3000 can freak out
  // the next time your try to connect ...
  Serial.println("\n\nDisconnecting");
  cc3000.disconnect();
}

void loop(void){
}
