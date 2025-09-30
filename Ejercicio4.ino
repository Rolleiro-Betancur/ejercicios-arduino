#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

// Pines de los sensores
#define PIN_DHT   8       // Pin de datos del DHT11
#define DHTTYPE   DHT11
#define PIN_LM35  A0      // Pin de salida analógica del LM35

// Inicialización de librerías
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(PIN_DHT, DHTTYPE);

// --- Función para leer temperatura del LM35 ---
float readLM35C() {
  int value = analogRead(PIN_LM35); 
  float voltage = value * (5.0 / 1023.0);  
  float tempC = voltage * 100.0;   // LM35 -> 10mV/°C
  return tempC;
}

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leer datos del DHT11
  float h = dht.readHumidity();
  float t_dht = dht.readTemperature();  // Celsius

  // Leer datos del LM35
  float t_lm35 = readLM35C();

  // Verificar si hay error de lectura
  if (isnan(h) || isnan(t_dht)) {
    lcd.clear();
    lcd.print("Error DHT11");
    delay(2000);
    return;
  }

  // Mostrar en pantalla
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(h, 0);
  lcd.print("% Temperatura:");
  lcd.print(t_dht, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("LM35:");
  lcd.print(t_lm35, 1);
  lcd.print("C");

  delay(2000); // refrescar cada 2 seg
}