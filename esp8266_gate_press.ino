#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#ifndef STASSID
#define STASSID "SSID_Name"
#define STAPSK  "SSID_Password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const int relayPin = D1;

ESP8266WebServer server(80);

void handleGatePress() {
  Serial.println("Pressing Gate");
  digitalWrite(relayPin, HIGH);
  delay(750);
  digitalWrite(relayPin, LOW);
  server.send(200, "text/plain", "Gate Pressed");
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(relayPin, LOW);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/gate/press", handleGatePress);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  
}
