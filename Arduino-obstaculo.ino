
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //

// Repo  Github WidinsonDanilo  //

// Incluye las bibliotecas necesarias
#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

// Define los pines del sensor de ultrasonido
#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 

// Define la velocidad máxima de los motores
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

// Crea un objeto NewPing para el sensor de ultrasonido
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

// Crea objetos AF_DCMotor para los cuatro motores
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Crea un objeto Servo para el servo motor
Servo myservo;   

// Define variables globales
boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  // Configura el servo motor
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);

  // Lee la distancia inicial del sensor de ultrasonido
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {

  // Lee la distancia actual del sensor de ultrasonido
  distance = readPing();

  // Si la distancia es menor o igual a 15 cm, detiene el robot, retrocede, gira y continúa moviéndose hacia adelante
  if(distance<=15)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    int distanceR = lookRight();
    delay(200);
    int distanceL = lookLeft();
    delay(200);

    if(distanceR>=distanceL)
    {
      turnRight();
      moveStop();
    }else
    {
      turnLeft();
      moveStop();
    }
  }else
  {
    moveForward();
  }
}

// Función para girar hacia la derecha y leer la distancia con el sensor de ultrasonido
int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

// Función para girar hacia la izquierda y leer la distancia con el sensor de ultrasonido
int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

// Función para leer la distancia con el sensor de ultrasonido
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

// Función para detener el movimiento de los motores
void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 

// Función para mover el robot hacia adelante
void moveForward() {

  // Si el robot no se está moviendo hacia adelante, lo mueve hacia adelante y aumenta gradualmente la velocidad
  if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

// Función para mover el robot hacia atrás
void moveBackward() {

  // Si el robot no se está moviendo hacia atrás, lo mueve hacia atrás y aumenta gradualmente la velocidad
  goesForward=false;
  motor1.run(BACKWARD);
