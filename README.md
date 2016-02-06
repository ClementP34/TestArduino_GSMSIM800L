# TestArduino_GSMSIM800L

Test du module SIM800L EVB de chez RoHS

Programme simple pour envoyer des commandes AT au module par la console Serie.
C'est de la repompe de tuto, je suis un débutant et j'arrive pas à bien le brancher...

Il y a 7 PIN
-5v
-GND
-VDD
-SIM_TXD
-SIM_RXD
-GND
-RST

J'ai branché comme ça, il doit y avoir une erreur

GSM           Arduino   Alim externe(sur 5v / 2A)
-5v --------  -5V        
-GND -------  -GND       
-VDD ---1N4007--------- -5v 
-SIM_TXD ---  -D8                           
-SIM_RXD ---  -D7                             
-GND ------------------ -GND                            
-RST

Le module clignote mais ne renvoi rien...
