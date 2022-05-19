#include <HTTPClient.h>
#include <WiFi.h>

HTTPClient http;

// Replace with your network credentials (STATION)
const char* ssid = "Seu Wifi";
const char* password = "Senha Wifi";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  // Wait for wifi to be connected
  uint32_t notConnectedCounter = 0;
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Wifi connecting...");
      notConnectedCounter++;
      if(notConnectedCounter > 50) { // Reset board if not connected after 5s
          Serial.println("Resetting due to Wifi not connecting...");
          ESP.restart();
      }
  }
  Serial.println("Wifi connected, IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Call Api: http://192.168.0.20:8127/api/local/");
  http.begin("http://192.168.0.20:8127/api/local");
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
/*
  Serial.println("Call Api: https://viacep.com.br/ws/01001000/json/");
  http.begin("https://viacep.com.br/ws/01001000/json/");

  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }*/
  
}
void loop() {
  // put your main code here, to run repeatedly:
}
