#include <SoftwareSerial.h>

//Connexion des broches  
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 7
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

//Code PIN
String SIM_PIN_CODE = String("xxx");
//conditionnel d'envoi de sms
boolean sms;
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  
  delay(1000);
  //Initialisation
  Serial.println("---## Initialisation ##---");
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
  Serial.println("---## Setup Complete ##---");
  Serial.println("---## SendSMS ##---");
  sms = true;
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

  if(sms==true){
    sendsms("Message ici \r","33600000000");        
    sms = false;
  }
}

  void sendsms(String messageEnvoi, String numeroTel) {
    Serial.println("Début d'envoi de message");
    serialSIM800.print("AT+CMGF=1\r");  // Lance le mode SMS
    delay(1000);
    // Entrez votre numéro de téléphone    
    serialSIM800.print("AT+CMGS=\"+");
    serialSIM800.print(numeroTel);
    serialSIM800.print("\"\r");  
    delay(1000);
    // Entrez votre message ici    
    serialSIM800.print(messageEnvoi);  
    // CTR+Z en langage ASCII, indique la fin du message
    serialSIM800.print(char(26));        
    delay(1000);
    serialSIM800.println();
    Serial.print("SMS pour ");
    Serial.print(numeroTel);
    Serial.print(" Envoyé");
    }
