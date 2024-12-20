#include <EmonLib.h>
#include <DHT.h>
EnergyMonitor emon1;
const int LDR_PINS[6] = {34, 35, 32, 33, 25, 26};
LDR_PINS[1]="Overload";
LDR_PINS[2]="Yarn Tension";
LDR_PINS[3]="Cover";
LDR_PINS[4]="One-Piece";
LDR_PINS[5]=" ERROR 5";
LDR_PINS[6]=" ERROR 6 ";
#define ZMCT 12
#define LM35 27
#define DHTPIN 15

DHT dht(DHTPIN, DHT22);  
void setup() {
  Serial.begin(115200);
  dht.begin();
  for (int i = 0; i < 6; i++) {
    pinMode(LDR_PINS[i], INPUT);
  }
  pinMode(4, OUTPUT);
  analogSetAttenuation(ADC_11db);
    emon1.current(ZMCT, 0.1);
  }

void loop() {
  bool ledState = LOW;
  float h = dht.readHumidity();
  Serial.print("Humidity= ");
  Serial.println(h);
  for (int i = 0; i < 6; i++) {
    int LDR_value = analogRead(LDR_PINS[i]);
    Serial.print("LDR_value[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(LDR_value);
    if (LDR_value > 500 && LDR_value < 1300) {  
      ledState = HIGH;
    }
  }
    digitalWrite(4, ledState);
  {
  float lmvalue = analogRead(LM35);
  float tempr = (lmvalue * 500)/4095;
  Serial.print("Temp: ");
  Serial.println(tempr);}
 {
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  Serial.print(Irms*230.0);	       // Apparent power
  Serial.print(" ");
  Serial.println(Irms);	}

  delay(5000); 
}