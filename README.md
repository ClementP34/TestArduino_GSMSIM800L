# TestArduino_GSMSIM800L

##Test du module SIM800L EVB de chez RoHS

Programme simple pour envoyer des commandes AT au module par la console Serie.
C'est de la repompe de tuto, je suis un débutant et j'arrive pas à bien le brancher...

J'ai branché comme ça, il doit y avoir une erreur

###Materiel

1. 1 x Alim externe(calibré sur 5v / 2A)
2. 1 x Arduino Nano
3. 1 x SIM800L EVB de RoHS
4. 1 x Diode 1N4007

###PIN

Il y a 7 PIN :
* 5v
* GND
* VDD
* SIM_TXD
* SIM_RXD
* GND
* RST
 
###Branchement...

* 5v du module vers 5v de l'Alim externe
* GND du module vers GND de l'Alim externe
* VDD du module vers 5v de l'Alim externe via 1N4007
* SIM_TXD du module vers D8 de l'arduino
* SIM_RXD du module vers D7 de l'arduino
* GND du module vers GND de l'Alim externe

##Resultat
La diode "d2 ring" module s'allume, la led "d6 net" clignote mais le module ne comunique pas avec l'Arduino...
