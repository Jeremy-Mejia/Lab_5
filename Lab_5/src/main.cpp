//***************************************************************************************************************
// Universidad del Valle de Guatemala 
// BE3015 - Electrónica Digital 2
// Jeremy Mejía 
// Laboratorio #5
// Arduino
// Carné: 19846
//***************************************************************************************************************


//***************************************************************************************************************
// Librerías
//***************************************************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h>

//***************************************************************************************************************
// Definición de Pines
//***************************************************************************************************************

//Definición de entradas
#define Pot1 14 //Potenciómetro 1
#define Pot2 27 //Potenciómetro 2

//El que si corre
//Definición de pines de salidas LCD
#define RS 2
#define E 4 
#define D4 18
#define D5 19
#define D6 21
#define D7 22

//Paso 1: seleccion de parámetros de la señal PWM
#define pwmchannel1 1 //16 canales del 0 - 15
#define pwmchannel2 2 //16 canales del 0 - 15
#define pwmchannel3 3 //16 canales del 0 - 15
#define freqPWM 5000 // Frecuencia en Hz 
#define resolution 8 // 1 - 16 bits de resolución

//Leds a modificar
#define LedRojo 13 //GPIO para tener la salida PWM
#define LedVerde 12 //GPIO para tener la salida PWM
#define LedAzul 14 //GPIO para tener la salida PWM


//***************************************************************************************************************
// Prototipo de Funciones
//***************************************************************************************************************
void configurarPWM(void);

//***************************************************************************************************************
// Variables Globales
//***************************************************************************************************************
int contador = 0;
LiquidCrystal LCD(RS, E, D4, D5, D6, D7);
int adcRaw;
int voltaje; 
int voltaje1; 
//***************************************************************************************************************
// ISR (Interrupciones)
//***************************************************************************************************************

//***************************************************************************************************************
// Configuración
//***************************************************************************************************************

void setup() {
  Serial.begin(115200);
  LCD.begin(16, 2);
  configurarPWM();

  pinMode(LedRojo, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedAzul, OUTPUT);
}

//***************************************************************************************************************
// Loop Principal
//***************************************************************************************************************

void loop() {
  voltaje = analogRead(Pot1);
  voltaje = map(voltaje, 0, 4095, 0, 255);
  ledcWrite(pwmchannel1, voltaje);

  voltaje1 = analogRead(Pot2);
  voltaje1 = map(voltaje1, 02, 4095, 0, 255);
  ledcWrite(pwmchannel2, voltaje1);

  LCD.clear();
  LCD.print("Rojo ");
  LCD.print("Verde ");
  LCD.print("Azul ");
  LCD.setCursor(0, 1);
  LCD.print(voltaje);
/*
  Serial.print("Rojo ");
  Serial.println(voltaje);
  Serial.print("Verde ");
  Serial.println(voltaje1);*/

  
  LCD.setCursor(6, 1);
  LCD.print(voltaje1);
  
  delay(250);
}

//***************************************************************************************************************
// Función Antirebote
//***************************************************************************************************************


//**********************************************************************
// Función para configurar módulo PWM
//**********************************************************************
void configurarPWM(){

  //Paso 1: configurar el módulo PWM
  ledcSetup(pwmchannel1, freqPWM, resolution);
  ledcSetup(pwmchannel2, freqPWM, resolution);
  ledcSetup(pwmchannel3, freqPWM, resolution);


  //Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(LedRojo, pwmchannel1);
  ledcAttachPin(LedVerde, pwmchannel2);
  ledcAttachPin(LedAzul, pwmchannel3);

}