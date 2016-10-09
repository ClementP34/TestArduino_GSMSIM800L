#include <SoftwareSerial.h>

//Connexion des broches  
int sim800lTx=8; //SIM_TXD sur Arduino D8
int sim800lRx=7; //SIM_RXD sur Arduino D7
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800L(sim800lTx,sim800lRx);

//conditionnel d'envoi de sms
boolean smsTest;
boolean smsReception;
//--------------------------------------------------------------------------------
 void setup() {
  //Initialisation de la connexion Serie avec l'Arduino et du Moniteur Serie
  Serial.begin(9600);
     
  //Initialisation de la connexion Serie avec l'Arduino et le module SIM800L
  serialSIM800L.begin(9600);
  
  delay(1000);
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
    sendSms(serialSIM800L,"Msg de test !!","330606060606");        
    smsTest = false;
  }

  if(smsReception==true){
    receptionSms(serialSIM800L);        
    smsReception = false;
  }  
}
//--------------------------------------------------------------------------------
void InitialisationGSM(SoftwareSerial serialGSM, String pinGSM) {
  Serial.println("---## Initialisation ##---");  
  Serial.println("-------- Code PIN --------");
  serialGSM.print("AT+CPIN=");
  serialGSM.print(pinGSM);
  serialGSM.println("\r");
  delay(1000);
  Serial.println("--------- Statut ---------");
  serialGSM.println("ATI\r"); 
  delay(1000); 
  Serial.println("----- Etat du Reseau -----");
  serialGSM.println("AT+CSQ\r"); 
  delay(1000);
  Serial.println("------- Operateurs -------");
  serialGSM.println("AT+COPS ?\r"); 
  delay(1000);
  Serial.println("---## -------------- ##---");   
}
//--------------------------------------------------------------------------------    
void sendSms(SoftwareSerial serialGSM, String messageEnvoi, String numeroTel) {
  Serial.println("---##    Send SMS    ##---");
  serialGSM.print("AT+CMGF=1\r");  // Lance le mode SMS
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
  Serial.println("---## -------------- ##---");     
}
//--------------------------------------------------------------------------------
void receptionSms(SoftwareSerial serialGSM) {
  Serial.println("---## ReceveivingSMS ##---");
  serialGSM.print("AT+CMGF=1\r");   // Configure le mode SMS
  // Affiche tous les messages
  serialGSM.print("AT+CMGL=\"ALL\"\r");
  //AT+CMGL= "REC READ" : Affiche tous les messages lus
  //AT+CMGL= "REC UNREAD" : Affiche tous les messages non lus.
  delay(1000);
  serialGSM.println();
}
//--------------------------------------------------------------------------------
