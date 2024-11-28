#include <WiFi.h>
#include <HTTPClient.h>

#include<DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht22 (DHTPIN, DHTTYPE);

String URL = "http://ip_addr/dht22_project/test_data.php";

const char* ssid = "yournamewifi";
const char* password = "wifipassword";

int temperature = 0;
int humidity = 0;

void setup() {
  Serial.begin(115200);

  dht22.begin();

  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  Load_DHT22_Data();
  String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);

  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData); // Send the POST request
  String payload = http.getString();  // Get the server response

  Serial.print("URL: "); Serial.println(URL);
  Serial.print("Data: "); Serial.println(postData);
  Serial.print("HTTP Code: "); Serial.println(httpCode);
  Serial.print("Payload: "); Serial.println(payload);

  http.end(); // End the HTTP connection

  delay(5000); // Wait 5 seconds before the next loop
}


void Load_DHT22_Data(){

  temperature =dht22.readTemperature(); //Celsius
  humidity = dht22.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    temperature = 0;
    humidity = 0;
  }

  Serial.printf("Temperature: %d  °C\n", temperature);
  Serial.printf("Humidity: %d %%\n", humidity);
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("Connected to: "); Serial.println(ssid);
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
}
