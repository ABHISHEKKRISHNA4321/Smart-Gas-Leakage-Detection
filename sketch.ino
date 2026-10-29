#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "Wokwi-GUEST"; 
const char* password = "1234@5678";

unsigned long myChannelNumber = 3391889;
const char* myWriteAPIKey = "15BL3QNQERTQU35R";      

WiFiClient client;

const int MQ2_AOUT_PIN = 34; // MQ-2 Analog Output -> GPIO 34
const int MQ2_DOUT_PIN = 23; // MQ-2 Digital Output -> GPIO 23
const int POT_PIN = 36;      // Potentiometer Signal -> GPIO 36 (VP)
const int BUZZER_PIN = 18;   // Buzzer Positive (+) -> GPIO 18
const int LED_PIN = 16;      // Red LED Resistor -> GPIO 16

int gasThreshold = 2000;
unsigned long lastTime = 0;
unsigned long timerDelay = 15000; 

void setup() {
  Serial.begin(115200);

  pinMode(MQ2_DOUT_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");

  ThingSpeak.begin(client);  
}

void loop() {
  int analogGasValue = analogRead(MQ2_AOUT_PIN);  
  int digitalGasValue = digitalRead(MQ2_DOUT_PIN); 
  int potValue = analogRead(POT_PIN);           

  gasThreshold = map(potValue, 0, 4095, 500, 4000);

  bool alertActive = (analogGasValue > gasThreshold || digitalGasValue == HIGH);
  if (alertActive) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    Serial.println("⚠️ WARNING: Gas Leakage Detected locally!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  Serial.print("Gas: "); Serial.print(analogGasValue);
  Serial.print(" | Threshold: "); Serial.println(gasThreshold);

  if ((millis() - lastTime) > timerDelay) {
    // Set data fields
    ThingSpeak.setField(1, analogGasValue);
    ThingSpeak.setField(2, digitalGasValue);
    ThingSpeak.setField(3, gasThreshold);
    ThingSpeak.setField(4, alertActive ? 1 : 0);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (x == 200) {
      Serial.println("✅ Data successfully uploaded to ThingSpeak Cloud.");
    } else {
      Serial.println("❌ Cloud update failed. HTTP error code: " + String(x));
    }
    
    lastTime = millis(); 
  }

  delay(1000); 
}
