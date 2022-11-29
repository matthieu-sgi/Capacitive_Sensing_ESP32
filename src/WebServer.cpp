#include "WebServer.h"
#include "Arduino.h"
#include "WiFi.h"
#include "Website.h"

WiFiServer server(80);
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

bool serialState = false;

void setupWebServer(const char* ssid, const char* password) {
  // Connect to Wi-Fi network with SSID and password
//   Serial.begin(115200);
    WiFi.mode(WIFI_AP);
    if(Serial) serialState = true;
    if(serialState) Serial.print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    if(sizeof(password) < 1){
        WiFi.softAP(ssid);
    }
    else WiFi.softAP(ssid,password);
    IPAddress IP = WiFi.softAPIP();
    if(serialState){
    Serial.print("AP IP address: ");
    Serial.println(IP);
    }
    server.begin();
}

void loopWebServer(){

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                            // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
 
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
