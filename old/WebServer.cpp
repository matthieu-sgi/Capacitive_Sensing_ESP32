#include "WebServer.h"
#include "Arduino.h"
#include "WiFi.h"
#include "Website.h"

WiFiServer server(80);


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

bool serialState = false;



void Webserver::setupWebServer(const char* ssid, const char* password) {
  // Connect to Wi-Fi network with SSID and password

    WiFi.mode(WIFI_AP);
    
    serial->print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    if(sizeof(password) < 1){
        WiFi.softAP(ssid);
    }
    else WiFi.softAP(ssid,password);
    IPAddress IP = WiFi.softAPIP();

    serial->print("AP IP address: ");
    serial->println(IP);

    server.begin();

}

void Webserver::loopWebServer(){

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                            // If a new client connects,
    serial->println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        // serial->print("C value : ");
        serial->write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
        if (currentLine.length() == 0 ){
            serial->println("Home page");
            website.HomePage(&client);
                    break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // serial->println(header);
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
