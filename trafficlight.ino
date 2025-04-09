  // Final Smart Traffic Light Control System for 4 Breadboards (1 per lane)
  // Each lane uses IR sensor and traffic lights, connected to ESP32
  // Only one lane has green at a time, with a delay between transitions
  // Priority given to lanes with lowest vehicle count
  // SAFETY: 5s delay between green transitions to avoid collisions

#include <WiFi.h>
#include <WebSocketsServer.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Create WebSocket server on port 81
WebSocketsServer webSocket = WebSocketsServer(81);

// Add these to your existing global variables
int currentLane = 0;
int remainingTime = 0;
int cycleCount = 0;

// WebSocket event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        
        // Send current status when a client connects
        sendSensorData();
        sendLightStatus();
        sendSystemStatus();
        sendDensityData();
      }
      break;
    case WStype_TEXT:
      // Handle any incoming commands if needed
      break;
  }
}

// Send sensor data to all connected clients
void sendSensorData() {
  String message = "SENSORS:";
  message += digitalRead(IR1) == LOW ? "1" : "0";
  message += ",";
  message += digitalRead(IR2) == LOW ? "1" : "0";
  message += ",";
  message += digitalRead(IR3) == LOW ? "1" : "0";
  message += ",";
  message += digitalRead(IR4) == LOW ? "1" : "0";
  
  webSocket.broadcastTXT(message);
}

// Send traffic light status
void sendLightStatus() {
  String message = "LIGHTS:";
  
  // Add status for each lane (this is simplified - adjust based on your actual light states)
  for (int i = 1; i <= 4; i++) {
    if (i > 1) message += ",";
    message += String(i);
    message += ",";
    
    if (i == currentLane) {
      // Current active lane
      if (remainingTime > 2000) {
        message += "G"; // Green
      } else {
        message += "Y"; // Yellow
      }
    } else {
      message += "R"; // Red
    }
  }
  
  webSocket.broadcastTXT(message);
}

// Send system status
void sendSystemStatus() {
  String message = "STATUS:";
  message += String(currentLane);
  message += ",";
  message += String(remainingTime / 1000); // Convert to seconds
  message += ",";
  message += String(cycleCount);
  
  webSocket.broadcastTXT(message);
}

// Send density data
void sendDensityData() {
  String message = "DENSITY:";
  message += digitalRead(IR1) == LOW ? "3" : "0";
  message += ",";
  message += digitalRead(IR2) == LOW ? "2" : "0";
  message += ",";
  message += digitalRead(IR3) == LOW ? "1" : "0";
  message += ",";
  message += digitalRead(IR4) == LOW ? "1" : "0";
  
  webSocket.broadcastTXT(message);
}
  #define IR1 32  // Lane 1 IR Sensor
  #define IR2 33  // Lane 2 IR Sensor
  #define IR3 34  // Lane 3 IR Sensor
  #define IR4 35  // Lane 4 IR Sensor

  // Lane 1 Traffic Lights
  #define RED1 25
  #define YELLOW1 26
  #define GREEN1 27

  // Lane 2 Traffic Lights
  #define RED2 14
  #define YELLOW2 12
  #define GREEN2 13

  // Lane 3 Traffic Lights
  #define RED3 4
  #define YELLOW3 2
  #define GREEN3 15
    
  // Lane 4 Traffic Lights
  #define RED4 21
  #define YELLOW4 19
  #define GREEN4 18

  void setup() {
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
    pinMode(IR3, INPUT);
    pinMode(IR4, INPUT);

    pinMode(RED1, OUTPUT); pinMode(YELLOW1, OUTPUT); pinMode(GREEN1, OUTPUT);
    pinMode(RED2, OUTPUT); pinMode(YELLOW2, OUTPUT); pinMode(GREEN2, OUTPUT);
    pinMode(RED3, OUTPUT); pinMode(YELLOW3, OUTPUT); pinMode(GREEN3, OUTPUT);
    pinMode(RED4, OUTPUT); pinMode(YELLOW4, OUTPUT); pinMode(GREEN4, OUTPUT);

    allRed(); // Set all lights to red at the start
    void setup() {
  // Your existing setup code...
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
  }

  void loop() {
    int density[4];
    density[0] = digitalRead(IR1) == LOW ? 3 : 0;
    density[1] = digitalRead(IR2) == LOW ? 2 : 0;
    density[2] = digitalRead(IR3) == LOW ? 1 : 0;
    density[3] = digitalRead(IR4) == LOW ? 1 : 0;

    for (int i = 0; i < 4; i++) {
      int minIndex = getMinDensityIndex(density);
      int greenTime = 0;

      if (density[minIndex] == 0) greenTime = 4000;
      else if (density[minIndex] == 1) greenTime = 7000;
      else if (density[minIndex] == 2) greenTime = 10000;
      else greenTime = 15000;

      // Run selected lane with priority
      switch (minIndex) {
        case 0: runLane(RED1, YELLOW1, GREEN1, greenTime); break;
        case 1: runLane(RED2, YELLOW2, GREEN2, greenTime); break;
        case 2: runLane(RED3, YELLOW3, GREEN3, greenTime); break;
        case 3: runLane(RED4, YELLOW4, GREEN4, greenTime); break;
      }

      density[minIndex] = 100; // Mark lane as processed
     
      delay(5000); // SAFETY DELAY before switching to next lane
      
    }
  }

  void runLane(int red, int yellow, int green, int greenTime) {
    allRed();
    delay(500); // brief delay before switching to green

    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    delay(greenTime);

    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    delay(2000);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
  }

  void allRed() {
    digitalWrite(RED1, HIGH); digitalWrite(GREEN1, LOW); digitalWrite(YELLOW1, LOW);
    digitalWrite(RED2, HIGH); digitalWrite(GREEN2, LOW); digitalWrite(YELLOW2, LOW);
    digitalWrite(RED3, HIGH); digitalWrite(GREEN3, LOW); digitalWrite(YELLOW3, LOW);
    digitalWrite(RED4, HIGH); digitalWrite(GREEN4, LOW); digitalWrite(YELLOW4, LOW);
  }

  int getMinDensityIndex(int lanes[]) {
    int min = lanes[0];
    int index = 0;
    for (int i = 1; i < 4; i++) {
      if (lanes[i] < min) {
        min = lanes[i];
        index = i;
      }
    }
    return index;
  }
