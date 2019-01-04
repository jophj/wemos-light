#include <ESP8266WiFi.h>
 
const char* ssid = "***";
const char* password = "***";
const IPAddress ip(192, 168, 1, 99);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

const int ledPin = LED_BUILTIN;
const int relayPin = D1;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}

int status = LOW;

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new request");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/status") != -1){
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println(""); //  do not forget this one
    client.print("{\"status\":");client.print(!status);client.print("}");
    return;
  }
 
  // Match the request
  if (request.indexOf("/light=on") != -1) {
    status = LOW;
  } 
  if (request.indexOf("/light=off") != -1){
    status = HIGH;
  }

  digitalWrite(ledPin, status);
  digitalWrite(relayPin, status);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Status: ");
 
  if(status == HIGH) {
    client.print("OFF");  
  } else {
    client.print("ON");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/light=on\">here</a> turn the LED on pin 5 ON<br>");
  client.println("Click <a href=\"/light=off\">here</a> turn the LED on pin 5 OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
