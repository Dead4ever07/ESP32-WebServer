#include <WiFi.h>
#include <WebServer.h>
#include "FS.h"
#include <LittleFS.h>

const char* ssid = "Vodafone-5BAE0F"; 
const char* password = "HPua9NwY7Pt8DfWt";

IPAddress local_IP(192, 168, 1, 88);   // ESP32 IP
IPAddress gateway(192, 168, 1, 1);      // Your router IP
IPAddress subnet(255, 255, 255, 0);     // Subnet mask
IPAddress primaryDNS(8, 8, 8, 8);       // Optional: Google DNS
IPAddress secondaryDNS(8, 8, 4, 4);     


WebServer server(80);

// Generic file-serving handler
void handleFileRequest() {
  String path = server.uri();  // get the URL path
  if (path == "/") path = "/index.html"; // default file

  Serial.println("Request for: " + path);

  if (LittleFS.exists(path)) {
    File file = LittleFS.open(path, "r");
    
    // Set MIME type based on file extension
    String contentType = "text/plain";
    if (path.endsWith(".html")) contentType = "text/html";
    else if (path.endsWith(".css")) contentType = "text/css";
    else if (path.endsWith(".js")) contentType = "application/javascript";
    else if (path.endsWith(".png")) contentType = "image/png";
    else if (path.endsWith(".jpg") || path.endsWith(".jpeg")) contentType = "image/jpeg";

    server.streamFile(file, contentType);
    file.close();
  } else {
    server.send(404, "text/plain", "File not found: " + path);
  }
}

void setup() {
  Serial.begin(115200);

  if(!LittleFS.begin(true)) {
    Serial.println("SPIFFS mount failed");
    return;
  }

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected: " + WiFi.localIP().toString());

  // Handle all GET requests with the generic handler
  server.onNotFound(handleFileRequest);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
