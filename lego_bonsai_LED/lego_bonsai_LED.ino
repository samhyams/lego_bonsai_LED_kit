/*
  To use this program:
  1. Change the credentials in 'ssid.h' to match your chosen WiFi network
  2. Compile and upload to your ESP8266 board
    
  Notes: - Requires ESP8266Wifi, Adafruit_Neopixel
         - I used a Wemos D1 Mini clone. This is the only hardware tested!
         - I also used standard WS2812 LEDs, and these are the only LEDs tested
         - Set to 4 LEDs by default, change this using NUM_LEDS
   
  Uses basic structure from 'ESP8266 First Web Server', from:
  https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html

  Example of writing int to EEPROM:
  https://forum.arduino.cc/t/how-to-read-and-write-eeprom-in-esp8266-arduino-ide/395238/4

  Adafruit Neopixel library used, brightness not used

*/
#include <EEPROM.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#include "ssid.h"
#include "html.h"

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

// function prototypes for HTTP handlers
void handleRoot();              
void handleLED();
void handleCol();
void handleNotFound();

void changeLEDcolour();

// Load LED library
#include <Adafruit_NeoPixel.h>
// Define number of LEDs
#define NUM_LEDS 4
#define DATA_PIN 5
Adafruit_NeoPixel pixels(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
// Initialise LED features
bool led_state = false;
int col_r = 128;
int col_b = 128;
int col_g = 128;
//int brightness = 128;

void setup(void) {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP(ssid, password);   //Add wifi details, using ssid.h details
  //wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2"); //Can add extra AP if necessary

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("bonsai")) {              // Start the mDNS responder for bonsai.local
    Serial.println("mDNS responder started (bonsai.local)");
  } else {
    Serial.println("Error setting up MDNS responder! (bonsai.local)");
  }

  // TELL THE SERVER WHAT FUNCTIONS TO CALL DEPENDING ON THE RECEIVED REQUEST
  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.on("/col", HTTP_POST, handleCol); // Call the 'handleCol' function when a POST request is made to URI "/col"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");

  EEPROM.begin(6);              // Initialise 6 bytes of EEPROM (3 ints)
  EEPROM_readCols();            // Read the colours form memory
  Serial.println("Values read from EEPROM:");
  Serial.println(col_r); Serial.println(col_g); Serial.println(col_b);

  // LED initialise
  pixels.begin();
}

void loop(void) {
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", the_page(col_r, col_g, col_b));
}

// Read integers from EEPROM
// Must do this since each int takes up 2 bytes
void EEPROM_readCols() {
  byte high = EEPROM.read(0); //read the first half
  byte low = EEPROM.read(1);  //read the second half
  col_r = (high << 8) + low;  //reconstruct the integer
  // Repeat for other cols...
  high = EEPROM.read(2); //read the first half
  low = EEPROM.read(3);  //read the second half
  col_g = (high << 8) + low;  //reconstruct the integer
  high = EEPROM.read(4); //read the first half
  low = EEPROM.read(5);  //read the second half
  col_b = (high << 8) + low;  //reconstruct the integer
}

// Write integers to EEPROM
// Must do this since each int takes up 2 bytes
void EEPROM_writeCols(int r, int g, int b) {
    EEPROM.write(0, highByte(r)); //write the first half
    EEPROM.write(1, lowByte(r)); //write the second half
    EEPROM.write(2, highByte(g)); //write the first half
    EEPROM.write(3, lowByte(g)); //write the second half
    EEPROM.write(4, highByte(b)); //write the first half
    EEPROM.write(5, lowByte(b)); //write the second half
    // Save changes to EEPROM
    if (EEPROM.commit()) {
      Serial.println("EEPROM successfully committed");
      Serial.println("Values saved to  EEPROM:");
      Serial.println(r); Serial.println(g); Serial.println(b);
    } else {
      Serial.println("ERROR! EEPROM commit failed");
    }
}

// If a POST request is made to URI /LED
void handleLED() {                         
  // Change the state of the LED
  if (led_state == true){
    led_state = false;
    changeLEDcolour(0, 0, 0);
    pixels.show();
  } else {
    led_state = true;
    changeLEDcolour(col_r, col_g, col_b);
    
  }
  Serial.println("LED toggle, LED power = " + String(led_state));
       
  server.sendHeader("Location", "/");       // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}


// If a POST request is made to URI /col
void handleCol() {
  // There is no verification of input data!
  Serial.println("R: " + server.arg("col_r"));
  Serial.println("G: " + server.arg("col_g"));
  Serial.println("B: " + server.arg("col_b"));
  //Serial.println("Brightness: " + server.arg("bright"));
  // Get the ints for each colour from the submitted data
  col_r = atoi(server.arg("col_r").c_str());
  col_g = atoi(server.arg("col_g").c_str());
  col_b = atoi(server.arg("col_b").c_str());
  //brightness = atoi(server.arg("bright").c_str());

  // First, turn off to prevent weirdness
  led_state = true;
  handleLED();
  // Change the colour
  changeLEDcolour(col_r, col_b, col_g);
  // Turn back on!
  led_state = false;
  handleLED();

  // Write to EEPROM
  EEPROM_writeCols(col_r, col_g, col_b);

  // Return the original webpage
  handleRoot();

}

// Change pixel colour
void changeLEDcolour(int r, int g, int b) {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
    if (led_state == true)
    {
      pixels.show();
    }
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
