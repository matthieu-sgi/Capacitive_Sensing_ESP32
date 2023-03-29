// #include <Arduino.h>
// // #include "WebServerV2.h"

// // #include "OTA.h"
// // #include "ble.h"

// #define LED 2
// #define BUZZER 27

// const char* ssid = "Interactive_Plant";
// const char* password = "";

// static const int TOUCH_PIN = 4;

// int max_value = 0;


// // // Import required libraries
// // #include <WiFi.h>
// // #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// // // #include "WebServerV2.h"

// // const char* PARAM_INPUT_1 = "output";
// // const char* PARAM_INPUT_2 = "state";

// // // Create AsyncWebServer object on port 80
// // AsyncWebServer server(80);


// // const char index_html[] PROGMEM = R"rawliteral(
// // <!DOCTYPE HTML><html>
// // <head>
// //   <title>ESP Web Server</title>
// //   <meta name="viewport" content="width=device-width, initial-scale=1">
// //   <link rel="icon" href="data:,">
// //   <style>
// //     html {font-family: Arial; display: inline-block; text-align: center;}
// //     h2 {font-size: 3.0rem;}
// //     p {font-size: 3.0rem;}
// //     body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
// //     .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
// //     .switch input {display: none}
// //     .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
// //     .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
// //     input:checked+.slider {background-color: #b30000}
// //     input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
// //   </style>
// // </head>
// // <body>
// //   <h2>ESP Web Server</h2>
// //   %BUTTONPLACEHOLDER%
// // <script>function toggleCheckbox(element) {
// //   var xhr = new XMLHttpRequest();
// //   if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
// //   else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
// //   xhr.send();
// // }
// // </script>
// // </body>
// // </html>
// // )rawliteral";

// // String outputState(int output){
// //   if(digitalRead(output)){
// //     return "checked";
// //   }
// //   else {
// //     return "";
// //   }
// // }

// // // Replaces placeholder with button section in your web page
// // String processor(const String& var){
// //   //Serial.println(var);
// //   if(var == "BUTTONPLACEHOLDER"){
// //     String buttons = "";
// //     buttons += "<h4>Output - GPIO 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(2) + "><span class=\"slider\"></span></label>";
// //     buttons += "<h4>Output - GPIO 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" " + outputState(4) + "><span class=\"slider\"></span></label>";
// //     buttons += "<h4>Output - GPIO 33</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" " + outputState(33) + "><span class=\"slider\"></span></label>";
// //     return buttons;
// //   }
// //   return String();
// // }

// void setup(){
//   // Serial port for debugging purposes
//   Serial.begin(115200);
//   pinMode(BUZZER, OUTPUT);
//   pinMode(TOUCH_PIN, INPUT);
//   // pinMode(2, OUTPUT);
//   // digitalWrite(2, LOW);
//   // pinMode(4, OUTPUT);
//   // digitalWrite(4, LOW);
//   // pinMode(33, OUTPUT);
//   // digitalWrite(33, LOW);
  
  
//   // Generates its own Wi-Fi
// //  if(sizeof(password) < 1){
// //         WiFi.softAP(ssid);
// //     }
// //     else WiFi.softAP(ssid,password);
// //   // while (WiFi.status() != WL_CONNECTED) {
// //   //   delay(1000);
// //   //   Serial.println("Connecting to WiFi..");
// //   // }


// //   Serial.print("AP IP address: ");
// //   Serial.println(WiFi.softAPIP());
// // // Route for root / web page
  
// //   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
// //     Serial.println("HereKJLEHGFHIUJOZEIZAIEZANEPZAEPOZAOIENAZÊUNAZEUAZPENUAZ^NEZANIEÀÂZNUEI^N");
// //     request->send_P(200, "text/html", index_html, processor);
// //   });

// //   // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
// //   server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
// //     String inputMessage1;
// //     String inputMessage2;
// //     // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
// //     if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
// //       inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
// //       inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
// //       digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
// //     }
// //     else {
// //       inputMessage1 = "No message sent";
// //       inputMessage2 = "No message sent";
// //     }
// //     Serial.print("GPIO: ");
// //     Serial.print(inputMessage1);
// //     Serial.print(" - Set to: ");
// //     Serial.println(inputMessage2);
// //     request->send(200, "text/plain", "OK");
// //   });

// //   // Start server
// //   server.begin();
// }



// void loop() {
//   int value_touch = touchRead(TOUCH_PIN);
//   // Serial.print("Value: ");
//   // Serial.println(value_touch);
//   max_value = (int(value_touch) > max_value) ? int(value_touch) : max_value;
//   int pwm_value = map(value_touch, 0, max_value, 50, 0);
//   Serial.print("PWM: ");
//   Serial.println(pwm_value);
//   analogWrite(BUZZER, pwm_value);
  

// }



//////////////////// TEST //////////////////////

#include <Arduino.h>



// #define CALIB_PIN 27
// #define INTERRUPT_PIN 27

// //define the i2s pins
// #define I2S_BITCLOCK_PIN 19
// #define I2S_DATA_PIN 18
// #define I2S_FRAMECLOCK_PIN 21


// int interruptCounter = 0;

// int max_freq = 0;
// int min_freq = 1024;

// unsigned long temp_time = 0;


// // Callback interrupt

// void IRAM_ATTR ISR() {
//   // Serial.println("Interrupt");
//   interruptCounter++;
// }

// void calibrate() {

//   // Set the interrupt pin as input
//   pinMode(INTERRUPT_PIN, INPUT);
//   // Attach the interupt to the pin
//   attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), ISR, RISING);
//   // Do the calibration for 10 seconds
//   Serial.println("Calibration started");
//   unsigned long starting_time = millis();
//   temp_time = millis();
//   while (millis() - starting_time < 30000) // Calibrate for 30 seconds
//   {
//     if(millis() - temp_time > 1000) {
//       // Stop interupt
//       detachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN));
//       Serial.println("Frequence computation in progress");
//       int freq = interruptCounter;
//       max_freq = (freq > max_freq) ? freq : max_freq;
//       min_freq = (freq < min_freq) ? freq : min_freq;
//       interruptCounter = 0;
//       // Reattach interupt
//       attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), ISR, RISING);
//     }

//   }
  
//   detachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN));


// }

// int frequency(){
//     if(millis() - temp_time > 1000) {
//     Serial.print("Frequence :");
//     int freq = interruptCounter;
//     Serial.println(freq);
//     interruptCounter = 0;
//     Serial.print("Max: ");
//     Serial.print(max_freq);
//     Serial.print(" - Min: ");
//     Serial.println(min_freq);
//     temp_time = millis();
//     return freq;
//   }
// }

/*  Example using waveshaping to modify the spectrum of an audio signal
    using Mozzi sonification library.
    Demonstrates the use of WaveShaper(), EventDelay(), Smooth(),
    rand(), and fixed-point numbers.
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.io/Mozzi/
        Mozzi documentation/API
        https://sensorium.github.io/Mozzi/doc/html/index.html
        Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
    Tim Barrass 2012, CC by-nc-sa.
*/
#include <MozziGuts.h>
#include <Oscil.h>
#include <WaveShaper.h>
#include <EventDelay.h>
#include <mozzi_rand.h>
#include <mozzi_midi.h>
#include <Smooth.h>
#include <tables/sin2048_int8.h>
#include <tables/waveshape_chebyshev_3rd_256_int8.h>
#include <tables/waveshape_chebyshev_6th_256_int8.h>
#include <tables/waveshape_compress_512_to_488_int16.h>

#define INTERRUPT_PIN 4
// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA); // sine wave sound source
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aGain1(SIN2048_DATA); // to fade sine wave in and out before waveshaping
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aGain2(SIN2048_DATA); // to fade sine wave in and out before waveshaping
// Chebyshev polynomial curves, The nth curve produces the n+2th harmonic component.
WaveShaper <char> aCheby3rd(CHEBYSHEV_3RD_256_DATA); // 5th harmonic
WaveShaper <char> aCheby6th(CHEBYSHEV_6TH_256_DATA); // 8th harmonic
WaveShaper <int> aCompress(WAVESHAPE_COMPRESS_512_TO_488_DATA); // to compress instead of dividing by 2 after adding signals
// for scheduling note changes
EventDelay kChangeNoteDelay;
// for random notes
Q8n0 octave_start_note = 42;
Q24n8 carrier_freq; // unsigned long with 24 integer bits and 8 fractional bits
// smooth transitions between notes
Smooth <unsigned int> kSmoothFreq(0.85f);
int target_freq, smoothed_freq;

int freq = 0;


void ISR() {
  // Serial.println("Interrupt");
  freq++;
}

int start_time;

void setup(){
  startMozzi(); // :)
  randSeed(); // reseed the random generator for different results each time the sketch runs
  aSin.setFreq(110); // set the frequency
  aGain1.setFreq(2.f); // use a float for low frequencies, in setup it doesn't need to be fast
  aGain2.setFreq(.4f);
  kChangeNoteDelay.set(4000); // note duration ms, within resolution of CONTROL_RATE
  Serial.begin(115200);
  attachInterrupt(INTERRUPT_PIN, ISR, RISING);
  // pinMode(INTERRUPT_PIN, INPUT);
  start_time = millis();
  pinMode(26, OUTPUT);
}




byte rndPentatonic(){
  byte note = rand((byte)5);
  switch(note){
  case 0:
    note = 0;
    break;
  case 1:
    note = 3;
    break;
  case 2:
    note = 5;
    break;
  case 3:
    note = 7;
    break;
  case 4:
    note = 10;
    break;
  }
  return note;
}
void updateControl(){
    if (millis()- start_time  > 1000) {
    Serial.println(freq);
    if (freq > 5){
      // Serial.println("SOUND");
      startMozzi();
      // analogWrite(26, 128);
      // analogWrite(26, 0);
        if(kChangeNoteDelay.ready()){
    if(rand((byte)5)==0){ // about 1 in 5 or so
      // change octave to midi 24 or any of 3 octaves above
      // octave_start_note = (rand((byte)4)*12)+36;
      octave_start_note = (rand((byte)4)*4)+36; // I decreased the number to 5 to avoid high notes
    }
    Q16n16 midi_note = Q8n0_to_Q16n16(octave_start_note+rndPentatonic());
    target_freq = Q16n16_to_Q16n0(Q16n16_mtof(midi_note)); // has to be 16 bits for Smooth
    kChangeNoteDelay.start();
    
  }
  smoothed_freq = kSmoothFreq.next(target_freq*4); // temporarily scale up target_freq to get better int smoothing at low values
  aSin.setFreq(smoothed_freq/4); // then scale it back down after it's smoothed

    }
    else {
      // Serial.println("NO SOUND");
      // analogWrite(26, 0);
      stopMozzi();
    }
    freq = 0;
    start_time = millis();
  }
  // if(kChangeNoteDelay.ready()){
  //   if(rand((byte)5)==0){ // about 1 in 5 or so
  //     // change octave to midi 24 or any of 3 octaves above
  //     // octave_start_note = (rand((byte)4)*12)+36;
  //     octave_start_note = (rand((byte)4)*4)+36; // I decreased the number to 5 to avoid high notes
  //   }
  //   Q16n16 midi_note = Q8n0_to_Q16n16(octave_start_note+rndPentatonic());
  //   target_freq = Q16n16_to_Q16n0(Q16n16_mtof(midi_note)); // has to be 16 bits for Smooth
  //   kChangeNoteDelay.start();
  // }
  // smoothed_freq = kSmoothFreq.next(target_freq*4); // temporarily scale up target_freq to get better int smoothing at low values
  // aSin.setFreq(smoothed_freq/4); // then scale it back down after it's smoothed

}
int updateAudio(){
  char asig0 = aSin.next(); // sine wave source
  // make 2 signals fading in and out to show effect of amplitude when waveshaping with Chebyshev polynomial curves
  // offset the signals by 128 to fit in the 0-255 range for the waveshaping table lookups
  byte asig1 = (byte)128+((asig0*((byte)128+aGain1.next()))>>8);
  byte asig2 = (byte)128+((asig0*((byte)128+aGain2.next()))>>8);
  // get the waveshaped signals
  char awaveshaped1 = aCheby3rd.next(asig1);
  char awaveshaped2 = aCheby6th.next(asig2);
  // use a waveshaping table to squeeze 2 summed 8 bit signals into the range -244 to 243
  int awaveshaped3 = aCompress.next(256u + awaveshaped1 + awaveshaped2);
  return awaveshaped3 * 0.3;
  // return 0;
}
void loop(){
  // audioHook(); // required here
  // Check frequency every second
  // Serial.println(freq);
  // digitalRead(INTERRUPT_PIN);
  // Serial.println(freq);

    // audioHook();

  if (millis()- start_time  > 1000) {
    Serial.println(freq);
    if (freq >= 3){
      Serial.println("SOUND");
      // analogWrite(26, 128);
      // analogWrite(26, 0);
      analogWrite(26, 15);
      delay(500);
      analogWrite(26, 20);
      delay(500);
      analogWrite(26, 0);

    }
    freq = 0;
    start_time = millis();
  }
}


