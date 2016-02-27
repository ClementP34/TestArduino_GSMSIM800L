#include <SoftwareSerial.h>

//Connexion des broches  
//SIM800 TX is connected to Arduino D8
#define SIM800L_TX_PIN 8
 
//SIM800 RX is connected to Arduino D7
#define SIM800L_RX_PIN 7
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800L(SIM800L_TX_PIN,SIM800L_RX_PIN);

//conditionnel d'envoi de sms
boolean smsTest;
boolean smsReception;
//--------------------------------------------------------------------------------
 void setup() {
  //Initialisation de la connexion Serie avec l'Arduino et du Moniteur Serie
  Serial.begin(9600);
     
  //Initialisation de la connexion Serie avec l'Arduino et le module SIM800L
  serialSIM800L.begin(19200);
  
  delay(1000);
  Serial.println("---## Initialisation ##---");  
  InitialisationGSM(serialSIM800L,"0000");
  
  //envoi de sms de test
  smsTest = false;
  smsReception = false;
}
//-------------------------------------------------------------------------------- 
void loop() {
  //Read SIM800L output (if available) and print it in Arduino IDE Serial Monitor
  if(serialSIM800L.available()>0){
    Serial.write(serialSIM800L.read());
  }
  
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800L
  if(Serial.available()){    
    serialSIM800L.write(Serial.read());
  }

  if(smsTest==true){
    Serial.println("---## Send TEST SMS ##---");
    sendSms(serialSIM800L,"Msg de test !!","33600000000");        
    smsTest = false;
  }

  if(smsReception==true){
    Serial.println("---## Reception SMS ##---");
    receptionSms(serialSIM800L);        
    smsReception = false;
  }  
}
//--------------------------------------------------------------------------------
void InitialisationGSM(SoftwareSerial serialGSM, String pinGSM) {
  Serial.println("----- Code PIN -----");
  serialGSM.print("AT+CPIN=");
  serialGSM.print(pinGSM);
  serialGSM.println("\r");
  delay(5000);
  Serial.println("----- Statut -----");
  serialGSM.println("ATI\r"); 
  delay(1000);
  Serial.println("----- Etat du Reseau -----");
  serialGSM.println("AT+CSQ\r"); 
  delay(1000);
  Serial.println("----- Operateur -----");
  serialGSM.println("AT+COPS ?\r"); 
  delay(1000);   
}
//--------------------------------------------------------------------------------    
void sendSms(SoftwareSerial serialGSM, String messageEnvoi, String numeroTel) {
  Serial.println("Début d'envoi de message");
    // Lance le mode SMS
    serialGSM.print("AT+CMGF=1\r");  
    delay(1000);
    //numéro de téléphone    
    serialGSM.print("AT+CMGS=\"+");
    serialGSM.print(numeroTel);
    serialGSM.print("\"\r");  
    delay(1000);
    //message    
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
void receptionSms(SoftwareSerial serialGSM) {
  Serial.println("Receiving text message...");
  // Configure le mode SMS
  serialGSM.print("AT+CMGF=1\r");   
  // Affiche tous les messages
  serialGSM.print("AT+CMGL=\"ALL\"\r");
  //AT+CMGL= "REC READ" : Affiche tous les messages lus
  //AT+CMGL= "REC UNREAD" : Affiche tous les messages non lus.
  delay(1000);
  serialGSM.println();
}
//--------------------------------------------------------------------------------
