#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "SoftwareSerial.h"
#include "MHZ19.h"

#define RX_PIN D3         //MH-Z19 RX-PIN                                         
#define TX_PIN D4         //MH-Z19 TX-PIN                                   
#define BAUDRATE 9600    //Terminal Baudrate
#define REDYELLOWPIN D6        //Pin für Gelbe/Rote LED
#define ENABLEPIN D5     //Enable Pin für Gelbe LED
#define GREENPIN D7      //Pin für Grüne LED
#define ALERT_LEVEL 1000    //Schwellwert wenn die LED von Gelb auf Rot wechseln soll.
#define WARN_LEVEL  800    //Schwellwert wenn die LED von Grün auf Gelb wechseln soll.

//#define USE_ANALOGIN
#define USE_UART

#ifdef USE_UART
//Klassen definierung
MHZ19 myMHZ19;
SoftwareSerial mySerial(RX_PIN, TX_PIN);
#endif
#ifdef USE_ANALOGIN
#endif
unsigned long getDataTimer = 0;

#define ONE_HOUR 3600000UL

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

File fsUploadFile;                                    // a File variable to temporarily store the received file

ESP8266WiFiMulti wifiMulti;    // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

const char *OTAName = "ESP8266";         // A name and a password for the OTA service
const char *OTAPassword = "esp8266";

const char* mdnsName = "esp8266";        // Domain name for the mDNS responder

WiFiUDP UDP;                   // Create an instance of the WiFiUDP class to send and receive UDP messages

IPAddress timeServerIP;        // The time.nist.gov NTP server's IP address
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48;          // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE];     // A buffer to hold incoming and outgoing packets

void setLED(int r, int y, int g)
{
  if (r != 0)
  {
    digitalWrite(REDYELLOWPIN, LOW);
    digitalWrite(ENABLEPIN, LOW);
    digitalWrite(GREENPIN, HIGH);

  }
  else if (y != 0)
  {
    digitalWrite(REDYELLOWPIN, HIGH);
    digitalWrite(ENABLEPIN, LOW);
    digitalWrite(GREENPIN, HIGH);
  }
  else if (g != 0)
  {
    digitalWrite(REDYELLOWPIN, LOW);
    digitalWrite(ENABLEPIN, HIGH);
    digitalWrite(GREENPIN, LOW);
  }
}

void setup() {
  //LED PIN Mode festlegen
  pinMode(REDYELLOWPIN, OUTPUT);
  pinMode(ENABLEPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  //Serielle Intialisierung
  Serial.begin(BAUDRATE);
#ifdef USE_UART
  mySerial.begin(BAUDRATE);
  myMHZ19.begin(mySerial);
#endif
  startWiFi();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection

  startOTA();                  // Start the OTA service

  startSPIFFS();               // Start the SPIFFS and list all contents

  startMDNS();                 // Start the mDNS responder

  startServer();               // Start a HTTP server with a file read handler and an upload handler

  startUDP();                  // Start listening for UDP messages to port 123

  WiFi.hostByName(ntpServerName, timeServerIP); // Get the IP address of the NTP server
  Serial.print("Time server IP:\t");
  Serial.println(timeServerIP);

  sendNTPpacket(timeServerIP);

  // Let the LEDS blink
  setLED(0, 0, 1);
  delay(2000);
  setLED(0, 1, 0);
  delay(2000);
  setLED(1, 0, 0);
  delay(2000);
  setLED(0, 0, 1);
  delay(2000);
}

int CO2s, CO2a;

const unsigned long intervalNTP = ONE_HOUR; // Update the time every hour
unsigned long prevNTP = 0;
unsigned long lastNTPResponse = millis();

const unsigned long intervalSens = 60000;   // Do a temperature measurement every minute
unsigned long prevSens = 0;

uint32_t timeUNIX = 0;                      // The most recent timestamp received from the time server

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - prevNTP > intervalNTP) { // Request the time from the time server every hour
    prevNTP = currentMillis;
    sendNTPpacket(timeServerIP);
  }

  uint32_t time = getTime();                   // Check if the time server has responded, if so, get the UNIX time
  if (time) {
    timeUNIX = time;
    Serial.print("NTP response:\t");
    Serial.println(timeUNIX);
    lastNTPResponse = millis();
  } else if ((millis() - lastNTPResponse) > 24UL * ONE_HOUR) {
    Serial.println("More than 24 hours since last NTP response. Rebooting.");
    Serial.flush();
    ESP.reset();
  }

  if (timeUNIX != 0) {
    if (currentMillis - prevSens > intervalSens) {  // Every minute, request the sensor data
#ifdef USE_UART
      CO2s = myMHZ19.getCO2();
#endif
#ifdef USE_ANALOGIN
      int raw = analogRead(A0);
      CO2a = map(raw, 0, 1024, 0, 3300);
#endif
      //Ermittel ob der Schwellwert überschritten wurde und Schalten der LED
      if (CO2a > ALERT_LEVEL || CO2s > ALERT_LEVEL) {
        setLED(1, 0, 0); // red LED
        delay(100);
      } else if (CO2a > WARN_LEVEL || CO2s > WARN_LEVEL) {
        setLED(0, 1, 0); // yellow LED
      } else {
        setLED(0, 0, 1);
        delay(100);
      }
      //Ausgabe auf den Seriellen Monitor
      //Serial.print("CO2 (ppm): ");
#ifdef USE_UART
      Serial.print(CO2s);
      Serial.print(", ");
#endif
#ifdef USE_ANALOGIN
      Serial.print(CO2a);
#endif
      Serial.println("");
      prevSens = currentMillis;

      uint32_t actualTime = timeUNIX + (currentMillis - lastNTPResponse) / 1000;
      // The actual time is the last NTP time plus the time that has elapsed since the last NTP response

      Serial.printf("Appending sensor value to file: %lu,", actualTime);
      Serial.println(CO2s);
      File tempLog = SPIFFS.open("/temp.csv", "a"); // Write the time and the sensor data to the csv file
      tempLog.print(actualTime);
      tempLog.print(',');
      tempLog.println(CO2s);
      tempLog.close();
    }
  } else {                                    // If we didn't receive an NTP response yet, send another request
    sendNTPpacket(timeServerIP);
    delay(500);
  }

  server.handleClient();                      // run the server
  ArduinoOTA.handle();                        // listen for OTA events  }
}

/*__________________________________________________________SETUP_FUNCTIONS__________________________________________________________*/

void startWiFi() { // Try to connect to some given access points. Then wait for a connection
  wifiMulti.addAP("F492BF0BD9B2", "0BD9B2wtVexK");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("in-berlin-events", "ADAkqXXxevuS");

  Serial.println("Connecting");
  while (wifiMulti.run() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(250);
    Serial.print('.');
  }
  Serial.println("\r\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());             // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.print(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer
  Serial.println("\r\n");
}

void startUDP() {
  Serial.println("Starting UDP");
  UDP.begin(123);                          // Start listening for UDP messages to port 123
  Serial.print("Local port:\t");
  Serial.println(UDP.localPort());
}

void startOTA() { // Start the OTA service
  ArduinoOTA.setHostname(OTAName);
  ArduinoOTA.setPassword(OTAPassword);

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\r\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready\r\n");
}

void startSPIFFS() { // Start the SPIFFS and list all contents
  SPIFFS.begin();                             // Start the SPI Flash File System (SPIFFS)
  Serial.println("SPIFFS started. Contents:");
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {                      // List the file system contents
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    Serial.printf("\n");
  }
}

void startMDNS() { // Start the mDNS responder
  MDNS.begin(mdnsName);                        // start the multicast domain name server
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");
}

void startServer() { // Start a HTTP server with a file read handler and an upload handler
  server.on("/edit.html",  HTTP_POST, []() {  // If a POST request is sent to the /edit.html address,
    server.send(200, "text/plain", "");
  }, handleFileUpload);                       // go to 'handleFileUpload'

  server.onNotFound(handleNotFound);          // if someone requests any other file or page, go to function 'handleNotFound'
  // and check if the file exists

  server.begin();                             // start the HTTP server
  Serial.println("HTTP server started.");
}

/*__________________________________________________________SERVER_HANDLERS__________________________________________________________*/

void handleNotFound() { // if the requested file or page doesn't exist, return a 404 not found error
  if (!handleFileRead(server.uri())) {        // check if the file exists in the flash memory (SPIFFS), if so, send it
    server.send(404, "text/plain", "404: File Not Found");
  }
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";          // If a folder is requested, send the index file
  String contentType = getContentType(path);             // Get the MIME type
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) { // If the file exists, either as a compressed archive, or normal
    if (SPIFFS.exists(pathWithGz))                         // If there's a compressed version available
      path += ".gz";                                         // Use the compressed verion
    File file = SPIFFS.open(path, "r");                    // Open the file
    size_t sent = server.streamFile(file, contentType);    // Send it to the client
    file.close();                                          // Close the file again
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);   // If the file doesn't exist, return false
  return false;
}

void handleFileUpload() { // upload a new file to the SPIFFS
  HTTPUpload& upload = server.upload();
  String path;
  if (upload.status == UPLOAD_FILE_START) {
    path = upload.filename;
    if (!path.startsWith("/")) path = "/" + path;
    if (!path.endsWith(".gz")) {                         // The file server always prefers a compressed version of a file
      String pathWithGz = path + ".gz";                  // So if an uploaded file is not compressed, the existing compressed
      if (SPIFFS.exists(pathWithGz))                     // version of that file must be deleted (if it exists)
        SPIFFS.remove(pathWithGz);
    }
    Serial.print("handleFileUpload Name: "); Serial.println(path);
    fsUploadFile = SPIFFS.open(path, "w");               // Open the file for writing in SPIFFS (create if it doesn't exist)
    path = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {                                   // If the file was successfully created
      fsUploadFile.close();                               // Close the file again
      Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
      server.sendHeader("Location", "/success.html");     // Redirect the client to the success page
      server.send(303);
    } else {
      server.send(500, "text/plain", "500: couldn't create file");
    }
  }
}

/*__________________________________________________________HELPER_FUNCTIONS__________________________________________________________*/

String formatBytes(size_t bytes) { // convert sizes in bytes to KB and MB
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
}

String getContentType(String filename) { // determine the filetype of a given filename, based on the extension
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

unsigned long getTime() { // Check if the time server has responded, if so, get the UNIX time, otherwise, return 0
  if (UDP.parsePacket() == 0) { // If there's no response (yet)
    return 0;
  }
  UDP.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
  // Combine the 4 timestamp bytes into one 32-bit number
  uint32_t NTPTime = (packetBuffer[40] << 24) | (packetBuffer[41] << 16) | (packetBuffer[42] << 8) | packetBuffer[43];
  // Convert NTP time to a UNIX timestamp:
  // Unix time starts on Jan 1 1970. That's 2208988800 seconds in NTP time:
  const uint32_t seventyYears = 2208988800UL;
  // subtract seventy years:
  uint32_t UNIXTime = NTPTime - seventyYears;
  return UNIXTime;
}


void sendNTPpacket(IPAddress& address) {
  Serial.println("Sending NTP request");
  memset(packetBuffer, 0, NTP_PACKET_SIZE);  // set all bytes in the buffer to 0
  // Initialize values needed to form NTP request
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode

  // send a packet requesting a timestamp:
  UDP.beginPacket(address, 123); // NTP requests are to port 123
  UDP.write(packetBuffer, NTP_PACKET_SIZE);
  UDP.endPacket();
}
