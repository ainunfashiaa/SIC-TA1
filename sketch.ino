#include <WiFi.h>
#include <HTTPClient.h>

#define LDRPIN 36

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* serverName = "http://192.168.56.1:5000/post-data";

const float GAMMA = 0.7;
const float RL10 = 50;

void setup() {
  Serial.begin(115200);
  
  // Connect ke Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int intensitas = analogRead(LDRPIN);
  float voltage = intensitas / 4095.0 * 5.0;
  float resistance = 2000 * voltage / (1 - voltage / 5.0);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  Serial.print("intensitas cahaya : ");
  Serial.print(lux);
  Serial.println(" lux");

  String payload = "{";
  payload += "\"lux\":";
  payload += String(lux);
  payload += "}";

  // Kirim HTTP POST request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(10000);
}
