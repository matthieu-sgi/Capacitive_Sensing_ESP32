// #include "WebServerV2.h"
// #include "Arduino.h"
// #include "WiFi.h"
// #include "Website.h"
// #include <SPIFFS.h>
// #include <ESPAsyncWebServer.h>
// // #include <AsyncTCP.h>



// // Current time
// unsigned long currentTime = millis();
// // Previous time
// unsigned long previousTime = 0; 
// // Define timeout time in milliseconds (example: 2000ms = 2s)
// const long timeoutTime = 2000;

// bool serialState = false;



// void WebServer::setupWebServer(const char* ssid, const char* password) {
//   // Connect to Wi-Fi network with SSID and password

//     WiFi.mode(WIFI_AP);
    
//     serial->print("Setting AP (Access Point)…");
//     // Remove the password parameter, if you want the AP (Access Point) to be open
//     if(sizeof(password) < 1){
//         WiFi.softAP(ssid);
//     }
//     else WiFi.softAP(ssid,password);
//     IPAddress IP = WiFi.softAPIP();

//     serial->print("AP IP address: ");
//     serial->println(IP);

//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send(SPIFFS, "/index.html");
//   });

//     server.begin();

// }

// void WebServer::loopWebServer(){

  
// }

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "WebServerV2.h"

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

String WebServer::outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}

// Replaces placeholder with button section in your web page
String WebServer::processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Output - GPIO 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(2) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Output - GPIO 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" " + outputState(4) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Output - GPIO 33</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" " + outputState(33) + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}



void WebServer::setupWebServer(const char* ssid, const char* password){
  // Serial port for debugging purposes
  // Serial.begin(115200);

  
  // Generates its own Wi-Fi
 if(sizeof(password) < 1){
        WiFi.softAP(ssid);
    }
    else WiFi.softAP(ssid,password);


  // serial->print("AP IP address: ");
  // serial->println(WiFi.softAPIP());
// Route for root / web page
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // Serial.println("HereKJLEHGFHIUJOZEIZAIEZANEPZAEPOZAOIENAZÊUNAZEUAZPENUAZ^NEZANIEÀÂZNUEI^N");
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    // Serial.print("GPIO: ");
    // Serial.print(inputMessage1);
    // Serial.print(" - Set to: ");
    // Serial.println(inputMessage2);
    // request->send(200, "text/plain", "OK");
  });

  // Start server
  server.begin();
}

void WebServer::loopWebServer() {
  

}
