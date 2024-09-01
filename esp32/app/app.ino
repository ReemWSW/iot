#include <WiFi.h>
#include <WebSocketsClient.h>

const char* ssid = "CHAY";
const char* password = "027041216";
const char* websocket_server = "192.168.1.48"; 
const int websocket_port = 3000;

WebSocketsClient webSocket;

const int ledPin = 2; 

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {

  Serial.printf("%s\n", payload);
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Disconnected from WebSocket server");
      break;
    case WStype_CONNECTED:
      Serial.println("Connected to WebSocket server");
      break;
    case WStype_TEXT:
      Serial.printf("Received: %s\n", payload);
      if (strcmp((char*)payload, "ON") == 0) {
        digitalWrite(ledPin, HIGH);  // Turn on LED
      } else if (strcmp((char*)payload, "OFF") == 0) {
        digitalWrite(ledPin, LOW);  // Turn off LED
      }
      break;
    case WStype_BIN:
      Serial.println("Received binary data");
      break;
  }
}

void setup() {
  Serial.begin(115200);  
  delay(10);

  Serial.println();
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin(websocket_server, websocket_port, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(1000); 
}

void loop() {
  webSocket.loop();
}
