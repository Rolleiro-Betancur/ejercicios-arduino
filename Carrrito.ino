// --- Motor Shield L298P ---
// Motor A conectado a M1 (izquierdo)
// Motor B conectado a M2 (derecho)

// Pines Motor A
#define IN1 12
#define IN2 13
#define ENA 10

// Pines Motor B
#IN3 8
#define IN4 9
#define ENB 11

// Pines receptor KRF100
#define D0 2  // Botón adelante
#define D1 3  // Botón atrás
#define D2 4  // Botón izquierda
#define D3 5  // Botón derecha

// --- POTENCIA INDIVIDUAL DE LOS MOTORES (0 a 255) ---
int potMotorA_adelante = 200;  // Potencia Motor A al avanzar
int potMotorB_adelante = 200;  // Potencia Motor B al avanzar

int potMotorA_atras = 190;     // Potencia Motor A al retroceder
int potMotorB_atras = 190;     // Potencia Motor B al retroceder

int potMotorA_giro = 200;      // Potencia Motor A en giros
int potMotorB_giro = 225;      // Potencia Motor B en giros

void setup() {
  Serial.begin(9600);

  // Pines del motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Pines del receptor
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);

  Serial.println("Sistema listo con potencia individual...");
}

void loop() {
  // Lectura de botones
  bool adelante = digitalRead(D0);
  bool atras = digitalRead(D1);
  bool izquierda = digitalRead(D2);
  bool derecha = digitalRead(D3);

  // --- Control lógico ---
  if (adelante) {
    Adelante();
  } 
  else if (atras) {
    Atras();
  } 
  else if (izquierda) {
    Izquierda();
  } 
  else if (derecha) {
    Derecha();
  } 
  else {
    Parar();
  }
}

// --- FUNCIONES DE MOVIMIENTO ---

void Adelante() {
  Serial.println("→ Adelante");
  // Motor izquierdo (A)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, limitar(potMotorA_adelante));

  // Motor derecho (B)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, limitar(potMotorB_adelante));
}

void Atras() {
  Serial.println("← Atrás");
  // Motor izquierdo (A)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, limitar(potMotorA_atras));

  // Motor derecho (B)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, limitar(potMotorB_atras));
}

void Izquierda() {
  Serial.println("↺ Izquierda");
  // Motor izquierdo (A) apagado
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  // Motor derecho (B) avanza
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, limitar(potMotorB_giro));
}

void Derecha() {
  Serial.println("↻ Derecha");
  // Motor derecho (B) apagado
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);

  // Motor izquierdo (A) avanza
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, limitar(potMotorA_giro));
}

void Parar() {
  Serial.println("■ Parado");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// --- Función de seguridad ---
int limitar(int valor) {
  if (valor > 255) return 255;
  if (valor < 0) return 0;
  return valor;
}