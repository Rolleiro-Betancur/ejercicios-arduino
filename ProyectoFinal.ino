#include <IRremote.h>

const int RECV_PIN = 11; // Pin del receptor IR
IRrecv irrecv(RECV_PIN);
decode_results results;

// Pines de los 10 LEDs
int leds[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 12};

// Códigos HEX de cada botón ()
unsigned long codigos[] = {
  0x10E742BD, // Botón 1 -> LED 1 (pin 2)
  0x10E7827D, // Botón 2 -> LED 2 (pin 3)
  0x10E702FD, // Botón 3 -> LED 3 (pin 4)
  0x10E7629D, // Botón 4 -> LED 4 (pin 5)
  0x10E7A25D, // Botón 5 -> LED 5 (pin 6)
  0x10E722DD, // Botón 6 -> LED 6 (pin 7)
  0x10E752AD, // Botón 7 -> LED 7 (pin 8)
  0x10E7926D, // Botón 8 -> LED 8 (pin 9)
  0x10E712ED, // Botón 9 -> LED 9 (pin 10)
  0x10E7B24D  // Botón 10 -> LED 10 (pin 12)
};


unsigned long codigoApagarTodo = 0x10E7C23D; // Ejemplo (cambia este por el que obtengas en el monitor serial)

// Estado de cada LED
bool estadoLeds[10] = {false};

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  for (int i = 0; i < 10; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  Serial.println("Listo para controlar 10 LEDs con apagado total.");
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned long codigo = results.value;
    Serial.print("Código recibido: ");
    Serial.println(codigo, HEX);

    //  Si es el botón de "apagar todo"
    if (codigo == codigoApagarTodo) {
      apagarTodos();
    } else {
      //  Si es uno de los 10 botones de LED individual
      for (int i = 0; i < 10; i++) {
        if (codigo == codigos[i]) {
          estadoLeds[i] = !estadoLeds[i];
          digitalWrite(leds[i], estadoLeds[i]);
          Serial.print("LED ");
          Serial.print(i + 1);
          Serial.println(estadoLeds[i] ? " ON" : " OFF");
        }
      }
    }

    irrecv.resume();
  }
}

// 🔧 Función para apagar todos los LEDs
void apagarTodos() {
  for (int i = 0; i < 10; i++) {
    estadoLeds[i] = false;
    digitalWrite(leds[i], LOW);
  }
  Serial.println(" TODOS LOS LEDS APAGADOS");
}
