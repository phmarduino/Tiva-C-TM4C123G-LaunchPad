/*  
  Skecth : pm_temp_led_tivac_10122020.ino
  Description : Mesure température avec affichage console série et LED 
  Auteur : PHMARDUINO
  Création : 10 décembre 2020
  Derniere mise a jour :
*/
// Définition des broches ports LED et entrée analogique ADC
#define led_Verte PA_2
#define led_Jaune PA_3
#define led_Rouge PA_4
#define PIN_LM35 PE_2 // Entrée analogique ADC

//Définition des variables de travail
int valeurLm35;
float tension;
float temp;

// Traitements 'initialisation
void setup() {
  // déclaration 
  pinMode(led_Verte, OUTPUT);
  pinMode(led_Rouge, OUTPUT);
  pinMode(led_Jaune, OUTPUT);
  digitalWrite(led_Jaune, HIGH);
  digitalWrite(led_Rouge, HIGH);
  digitalWrite(led_Verte, HIGH);
  delay(100);
  digitalWrite(led_Jaune, LOW);
  digitalWrite(led_Rouge, LOW);
  digitalWrite(led_Verte, LOW);
  delay(100);
  // Initialisation liaison série
  Serial.begin(9600); // 
}

void loop() {
  valeurLm35 = analogRead(PIN_LM35);  //Mesure température
  tension=(valeurLm35*3.3)/4096;      //Conversion en tension cf ADC sur 12 bits et tension max à 3.3 volts
  temp = tension * 100.0;             //Conversion en température
  Serial.print("valeur : ");          //Affichage résulta console
  Serial.print(valeurLm35);
  Serial.print(" - Tension : ");
  Serial.print(tension);
  Serial.print(" - Temperature : ");
  Serial.println(temp);
  if (temp < 19.0)  {                 //Si température inférieure à 19 degrés allumage LED jaune
    digitalWrite(led_Jaune, HIGH);
    digitalWrite(led_Rouge, LOW);
    digitalWrite(led_Verte, LOW);
  }
  if ((temp >= 19.0) & (temp <= 22.0))   {  //Si température inférieure à 19 degrés 
    digitalWrite(led_Jaune, LOW);           //  et supérieure à 22 degrés allumage LED verte
    digitalWrite(led_Rouge, LOW);
    digitalWrite(led_Verte, HIGH);
  }
  if (temp > 22.0)  {                        //Si température supérieure à 22 degrés allumage LED rouge
    digitalWrite(led_Jaune, LOW);
    digitalWrite(led_Rouge, HIGH);
    digitalWrite(led_Verte, LOW);
  }
  delay(2000); // Délai de 2 secondes dans la boucle principale avant de refaire une mesure de température
}
