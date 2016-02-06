#include <SoftwareSerial.h>

//Connexion des broches  
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 7
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

//Code PIN
String SIM_PIN_CODE = String("xxxx");
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);

  Serial.println("----- Code PIN -----");
  serialSIM800.print("AT+CPIN=");
  serialSIM800.println(SIM_PIN_CODE);
  delay(5000);
  Serial.println("----- Statut -----");
  serialSIM800.println("ATI"); 
  delay(5000);
  Serial.println("----- Etat du Reseau -----");
  serialSIM800.println("AT+CSQ"); 
  delay(5000);
  Serial.println("----- Operateur -----");
  serialSIM800.println("AT+COPS ?"); 
  delay(5000);   
  Serial.println("Setup Complete!");
}
 
void loop() {
  //Read SIM800 output (if available) and print it in Arduino IDE Serial Monitor
  if(serialSIM800.available()){
    Serial.write(serialSIM800.read());
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800
  if(Serial.available()){    
    serialSIM800.write(Serial.read());
  }
}
