# IoT-Based-System-for-Environmental-Monitoring-and-Crop-Prediction-Using-ML
# IoT-Based System for Environmental Monitoring and Crop Prediction Using ML

**Project Duration:** Feb 2025 - March 2025
**Type:** Academic Project

## Overview

This project integrates the Internet of Things (IoT) and Machine Learning (ML) to build a smart agriculture system. The system monitors key environmental and soil parameters using IoT sensors, sends this data for analysis, and uses a trained ML model to predict the most suitable crop to cultivate. This enables farmers to make data-driven decisions, optimizing crop selection and potentially increasing yield.



---

## System Architecture

The data flows through the system as follows:

1.  **Sensors**: Collect data on temperature, humidity, soil pH, moisture, and nutrient levels (N, P, K).
2.  **ESP32 Microcontroller**: Reads data from the sensors and acts as an IoT gateway.
3.  **Data Transmission**: The ESP32 sends the collected data to a web server via an HTTP POST request.
4.  **ML Model Server**: A Flask API receives the data, feeds it to the pre-trained Random Forest model, and returns the predicted crop.
5.  **Decision Making**: The predicted crop name is sent back, which could be displayed on an LCD or a web dashboard.

```
[Sensors] --> [ESP32] --> [Wi-Fi] --> [API Server (Flask)] --> [ML Model] --> [Prediction]
```

---

## Features

-   **Real-time Monitoring**: Continuously collects environmental data.
-   **Intelligent Prediction**: Uses a Machine Learning model to recommend the most suitable crop.
-   **Scalable**: The architecture can be expanded to include more sensors or monitor larger areas.
-   **Data-Driven**: Replaces guesswork with actionable, data-backed insights for farming.

---

## Technologies & Tools Used

-   **Machine Learning**: Scikit-learn, Pandas
-   **IoT**: ESP32 Microcontroller
-   **Sensors**: DHT11 (Temperature, Humidity), Soil Moisture Sensor, pH Sensor
-   **Programming**: Python (for ML), C++/Arduino (for ESP32)
-   **API Framework**: Flask

---

### 1. Python & Machine Learning Setup

Create a virtual environment and install the required packages.


### 3. Train the ML Model

Run the training script. This will use the `crop_recommendation.csv` file to train a Random Forest model and save it as `model.pkl`.



### 4. Run the Prediction API

Start the Flask server. This API will listen for data from the ESP32.

### 5. ESP32 & Arduino Setup

-   **Install Arduino IDE**: Download it from the [official website](https://www.arduino.cc/en/software).
-   **Add ESP32 Board Manager**:
    -   Go to `File > Preferences`.
    -   In "Additional Board Manager URLs", add: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
    -   Go to `Tools > Board > Boards Manager`, search for "esp32" and install it.
-   **Install Libraries**:
    -   Go to `Sketch > Include Library > Manage Libraries`.
    -   Install `Arduino_JSON`.
-   **Configure and Upload**:
    -   Open `src/iot_device/esp32_datalogger/esp32_datalogger.ino` in the Arduino IDE.
    -   Update your Wi-Fi SSID and password.
    -   Update the `serverName` to your computer's IP address where the Flask API is running.
    -   Connect your ESP32, select the correct board and port from the `Tools` menu, and click Upload.

---

## How It Works

1.  The ESP32 connects to your Wi-Fi.
2.  In a loop, it generates simulated sensor data (Temperature, Humidity, pH, etc.).
3.  It formats this data into a JSON payload.
4.  It sends this payload to the `/predict` endpoint of your Flask API.
5.  The API uses the trained model to predict a crop and sends the name back.
6.  The ESP32 prints the received crop prediction to the Serial Monitor.
