
#include <DHT.h>
#include <WiFi.h>
#include <Arduino.h>

// WiFi credentials (replace with your network details)
char* ssid = "ultron";
char* password = "12345678";

// DHT11 Configuration
#define DHTPIN 4          // GPIO 4 for DHT11 data pin
#define DHTTYPE DHT11     // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

// Sensor Pins
#define SOIL_MOISTURE_PIN 34  // Analog pin for soil moisture sensor
#define PH_SENSOR_PIN 35      // Analog pin for pH sensor

// Calibration constants for soil moisture (adjust based on sensor calibration)
const int AIR_VALUE = 3500;   // ADC value in air (dry)
const int WATER_VALUE = 1500; // ADC value in water (wet)

// Calibration constants for pH sensor (adjust based on sensor calibration)
const float PH_4_VOLTAGE = 2.0;  // Voltage at pH 4.0
const float PH_7_VOLTAGE = 2.5;  // Voltage at pH 7.0
const float PH_SLOPE = -5.0;    // pH change per volt

// Function to read soil moisture (0-100%)
float readSoilMoisture() {
  int rawValue = analogRead(SOIL_MOISTURE_PIN); // Read ADC (0-4095)
  // Map to percentage, inverted (high ADC = dry, low ADC = wet)
  float moisture = map(rawValue, AIR_VALUE, WATER_VALUE, 0, 100);
  return constrain(moisture, 0, 100); // Ensure value is 0-100%
}

// Function to read pH (0-14)
float readPHSensor() {
  int rawValue = analogRead(PH_SENSOR_PIN); // Read ADC (0-4095)
  float voltage = rawValue * (3.3 / 4095.0); // Convert to voltage (0-3.3V)
  // Linear interpolation based on calibration points
  float pH = 7.0 + ((voltage - PH_7_VOLTAGE) * PH_SLOPE);
  return constrain(pH, 0, 14); // Ensure value is 0-14
}

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  delay(1000); // Allow hardware to stabilize
  
  // Initialize DHT11 sensor
  dht.begin();
  
  

  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < 20) {
    delay(500);
    Serial.print(".");
    wifiAttempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection failed. Continuing offline.");
  }
}

void loop() {
  // Read DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Check DHT readings
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error: Failed to read from DHT11 sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature, 1); // 1 decimal place
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity, 1); // 1 decimal place
    Serial.println(" %");
  }
  
  // Read soil moisture
  float soilMoisture = readSoilMoisture();
  if (soilMoisture >= 0 && soilMoisture <= 100) {
    Serial.print("Soil Moisture: ");
    Serial.print(soilMoisture, 1); // 1 decimal place
    Serial.println(" %");
  } else {
    Serial.println("Error: Invalid soil moisture reading!");
  }
  
  // Read pH sensor
  float pHValue = readPHSensor();
  if (pHValue >= 0 && pHValue <= 14) {
    Serial.print("pH Value: ");
    Serial.print(pHValue, 2); // 2 decimal places
    Serial.println("");
  } else {
    Serial.println("Error: Invalid pH reading!");
  }
  
  // Print a separator
  Serial.println("-------------------");
  
  // Delay for 5 seconds between readings
  delay(5000);
}
