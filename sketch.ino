#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address might vary

// Pin Definitions
#define MQ2_PIN 34          // Analog input from MQ2
#define LED_PIN 25          // Fan Indicator LED
#define BUZZER_PIN 26       // Buzzer
#define RESET_BUTTON 27     // Reset button

// Thresholds
#define SAFE_THRESHOLD 1000
#define MODERATE_THRESHOLD 2000

int graphData[SCREEN_WIDTH];  // Graph buffer
bool resetTriggered = false;

void setup() {
  Serial.begin(115200);

  // Initialize OLED
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 failed");
    while (true);
  }
  oled.clearDisplay();
  oled.display();

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Pin setup
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RESET_BUTTON, INPUT_PULLUP); // Active LOW

  lcd.setCursor(0, 0);
  lcd.print("Gas Monitor");
  delay(1500);
}

void loop() {
  if (digitalRead(RESET_BUTTON) == LOW) {
    performReset();
    return;
  }

  int gasValue = analogRead(MQ2_PIN);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  updateOLED(gasValue);
  updateLCD(gasValue);
  handleAlerts(gasValue);

  delay(500);
}

void updateOLED(int gasValue) {
  String emoji;
  if (gasValue < SAFE_THRESHOLD) {
    emoji = ":)";
  } else if (gasValue < MODERATE_THRESHOLD) {
    emoji = ":|";
  } else {
    emoji = ":(";
  }

  // Shift graph
  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    graphData[i] = graphData[i + 1];
  }
  graphData[SCREEN_WIDTH - 1] = map(gasValue, 0, 4095, 0, SCREEN_HEIGHT);

  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.print(emoji);

  // Draw Graph
  for (int x = 0; x < SCREEN_WIDTH - 1; x++) {
    oled.drawLine(x, SCREEN_HEIGHT, x, SCREEN_HEIGHT - graphData[x], SSD1306_WHITE);
  }

  oled.display();
}

void updateLCD(int gasValue) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasValue);

  lcd.setCursor(0, 1);
  if (gasValue < SAFE_THRESHOLD) {
    lcd.print("Status: SAFE");
  } else if (gasValue < MODERATE_THRESHOLD) {
    lcd.print("Status: MODERATE");
  } else {
    lcd.print("Status: DANGER!");
  }
}

void handleAlerts(int gasValue) {
  if (gasValue > MODERATE_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else if (gasValue > SAFE_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void performReset() {
  Serial.println("Reset Button Pressed!");

  // Reset status
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Clear LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Reset!");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring...");

  // Clear OLED
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setCursor(0, 0);
  oled.print("System Reset!");
  oled.display();

  // Clear graph buffer
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    graphData[i] = 0;
  }

  delay(2000);
}


