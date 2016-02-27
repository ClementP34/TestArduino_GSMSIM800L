#include <SoftwareSerial.h>

//Connexion des broches  
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 7
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

//conditionnel d'envoi de sms
boolean sms;
//--------------------------------------------------------------------------------
 void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  //while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(19200);
  
  delay(1000);
  InitialisationGSM(serialSIM800,"0000");
  Serial.println("---## Send TEST SMS ##---");
  
  //envoi de sms de test
  sms = false;
}
//-------------------------------------------------------------------------------- 
void loop() {
  //Read SIM800 output (if available) and print it in Arduino IDE Serial Monitor
  if(serialSIM800.available()){
    Serial.write(serialSIM800.read());
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800
  if(Serial.available()){    
    serialSIM800.write(Serial.read());
    serialSIM800.println();
  }

  if(sms==true){
    sendSms(serialSIM800,"Msg de test !!","33600000000");        
    sms = false;
  }
}
//--------------------------------------------------------------------------------
void InitialisationGSM(SoftwareSerial serialGSM, String pinGSM) {
  Serial.println("---## Initialisation ##---");
  Serial.println("----- Code PIN -----");
  serialGSM.print("AT+CPIN=");
  serialGSM.println(pinGSM);
  delay(5000);
  Serial.println("----- Statut -----");
  serialGSM.println("ATI"); 
  delay(4000);
  Serial.println("----- Etat du Reseau -----");
  serialGSM.println("AT+CSQ"); 
  delay(4000);
  Serial.println("----- Operateur -----");
  serialGSM.println("AT+COPS ?"); 
  delay(4000);   
}
//--------------------------------------------------------------------------------    
void sendSms(SoftwareSerial serialGSM, String messageEnvoi, String numeroTel) {
  Serial.println("Début d'envoi de message");
    serialGSM.print("AT+CMGF=1\r");  // Lance le mode SMS
    delay(1000);
    // Entrez votre numéro de téléphone    
    serialGSM.print("AT+CMGS=\"+");
    serialGSM.print(numeroTel);
    serialGSM.print("\"\r");  
    delay(1000);
    // Entrez votre message ici    
    serialGSM.print(messageEnvoi);
    serialGSM.print(" \r");  
    // CTR+Z en langage ASCII, indique la fin du message
    serialGSM.print(char(26));        
    delay(1000);
    serialGSM.println();
    Serial.print("SMS : ");
    Serial.print(messageEnvoi);
    Serial.print(" Pour :");
    Serial.print(numeroTel);
    Serial.println(" Envoyé");
}
//--------------------------------------------------------------------------------
