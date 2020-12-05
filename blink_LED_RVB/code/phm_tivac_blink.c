/*  
  Skecth      : phm_tivac_blink.c  
  Description : Test CCS TIVA c avec blink sur la LED RGB embarquée sur la carte
                branchée sur le port F et les pins F1, F2 et F3 de ce port
                avec PF1 : Rouge, PF2 : Bleu et PF3 : Vert
                Pour mémoire, 0xnn indique un nombre hexadecimal nn derrière le 0x                        
  Auteur      : PHMARDUINO  
  Création    : 28/11/2020  
  Mise a jour :
*/
//Registres de contrôle pour l'horloge du port F à débloquer car a l 'arrêt par defaut pour économie energie//
#define SYS_CTRL_RCGC2  (*((volatile unsigned long *)0x400FE108))   //offset registre RCGC2 0x108
#define CLK_GPIOF   0x20 //c est a dire en binaire 0010 0000 donc pour pouvoir positionner a 1 bit 5

//Registres de 32 bits pour le port F//
//Adresse en mémoire pour les données transitant sur le port F//
#define PORTF_DATA  (*((volatile unsigned long *)0x40025038))
//Adresse en mémoire pour les directions des pins du port F//
#define PORTF_DIR   (*((volatile unsigned long *)0x40025400))
//Adresse  en mémoire pour le déblocage du port F //
#define PORTF_DEN   (*((volatile unsigned long *)0x4002551C))

//Définition des trois pins PF1 PF2 PF3 qui sont sur les bits 1, 2 et 3 sur le registre DATA du port F//
#define PF1_pin 0x02 // LED rouge, 2 puissance 1 = 2 car bit 1 a partir de la droite du registre
#define PF2_pin 0x04 // LED bleue, 2 puissance 2 = 4 car bit 2 a partir de la droite du registre
#define PF3_pin 0x08 // LED verte, 2 puissance 3 = 8 car bit 3 a partir de la droite du registre

//Protype fonction delay pour une tempo entre chaque changement sur les LED//
void delay(unsigned long);

void main(void)
{
   SYS_CTRL_RCGC2 |= CLK_GPIOF; //Deblocage horloge pour le port F en forcant le bit 5 a 1
   PORTF_DIR |= 0x0000000E;    //PF1, PF2, PF3 sont déclarés en sortie
                               //le dernier octet est mis à E en hexa c'est a dire en binaire 000001110
                               //PF1, PF2 et PF3 sont donc a 1 donc déclarés en sortie
   PORTF_DEN |= 0x0000000E;    //PF1, PF2, PF3 sont débloqués, cf ci-dessus
   PORTF_DATA = 0;
   while(1)
   {
       PORTF_DATA |= (PF1_pin); // On met la pin PF1 à 1 en sortie pour allumer la LED rouge avec un ou logique inclusif
       delay(2000000);
       PORTF_DATA &= ~(PF1_pin); // On met la pin PF1 à 0 en sortie pour eteindre la LED rouge avec un et logique
       delay(2000000);
       PORTF_DATA |= (PF2_pin); // On met la pin PF2 à 1 en sortie pour allumer la LED bleue avec un ou logique inclusif
       delay(2000000);
       PORTF_DATA &= ~(PF2_pin); // On met la pin PF2 à 0 en sortie pour eteindre la LED bleue avec un et logique
       delay(1000000);
       PORTF_DATA |= (PF3_pin);// On met la pin PF3 à 1 en sortie pour allumer la LED verte avec un ou logique inclusif
       delay(2000000);
       PORTF_DATA &= ~(PF3_pin); // On met la pin PF1 à 0 en sortie pour eteindre la LED verte avec un et logique
       delay(2000000);
   }
    //;
}
void delay(unsigned long max)
{
   unsigned long compteur=0; // On fait "max" boucles passé en paramètre
   for(compteur=0; compteur<max; compteur++);
}
