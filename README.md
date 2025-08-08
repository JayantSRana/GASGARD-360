🛡️ GASGARD 360
A powerful, real-time air quality monitoring system using an ESP32, MQ2 gas sensor, buzzer, LED, OLED, and I2C LCD display. This project visually and audibly alerts users about changing gas concentration levels and allows for system reset via a button. Ideal for learning embedded systems, sensor integration, and data visualization.

📦 Features
✅ Real-time gas concentration monitoring (analog read from MQ2)
✅ OLED display with emoji-based status and dynamic gas value graph
✅ LCD display showing exact gas value and air quality status
✅ Buzzer and LED alerts for moderate and dangerous levels
✅ Reset button to clear graph, reset warnings, and reinitialize display
✅ User-friendly emoji & graph-based visualizations

🔌 Components Used
Component	Function
ESP32 Dev Board	Main microcontroller
MQ2 Gas Sensor	Measures air quality (smoke/gas)
OLED Display (SSD1306)	Shows emoji + dynamic graph
16x2 LCD (I2C)	Displays gas value & air status
Buzzer	Audible warning
LED	Visual warning
Push Button	Resets system
Jumper Wires, Breadboard	For connections

🖥️ Pin Configuration
Device	ESP32 Pin
MQ2 Sensor (Aout)	GPIO 34 (Analog)
Buzzer	GPIO 26
LED	GPIO 25
Reset Button	GPIO 27
OLED SDA	GPIO 21
OLED SCL	GPIO 22
LCD SDA (I2C)	GPIO 21 (shared)
LCD SCL (I2C)	GPIO 22 (shared)

✅ OLED and LCD share the same I2C bus.

🚦 Threshold Logic
Gas Value Range	Status	Alert
0 - 999	SAFE	No alert
1000 - 1999	MODERATE	LED ON
2000+	DANGER	LED + Buzzer ON

📟 Display Behavior
OLED:

Displays emoji: :), :|, or :(

Shows dynamic gas value graph (real-time)

LCD (16x2):

Line 1: Gas: <value>

Line 2: Status: SAFE / MODERATE / DANGER!

🧠 Code Features
analogRead() from MQ2 (values 0–4095)

map() used to visualize sensor output as vertical bar

OLED graph buffer to visualize live data

Pushbutton triggers full system reset (buzzer, LED, displays, graph)

🚀 Getting Started
🔧 Requirements
ESP32 board support in Arduino IDE

Libraries:

Adafruit_GFX

Adafruit_SSD1306

LiquidCrystal_I2C

Wire

💡 Setup
Connect all components using the pin table above.

Upload the code using Arduino IDE.

Monitor gas levels and observe real-time alerts and display behavior.

📷 Screenshots
(Insert screenshots of graph/emoji display)
(Insert screenshots of LCD showing status)

📌 Future Improvements
Add Blynk or Firebase for cloud-based monitoring

Use PPM calibration curve for accurate gas level (instead of raw values)

Add LoRa or WiFi module for remote alerts

Introduce battery-powered support for portability

🧪 Demo & Simulation
🔗 This project can be simulated on Wokwi:https://wokwi.com/projects/438642914220158977
