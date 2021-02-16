#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,11,12);


float Ubit;
float Uconv;

bool etat, etatAnterieur;
float vitesseKMH, vitesseMPH, frequence,impulsion;
unsigned long temps;

void setup() {
Serial.begin(9600);  
analogReference(DEFAULT); //Définition de la tension par défaut de la sortie AREF, c'est à dire 5V

pinMode(8,INPUT);
etatAnterieur = 0;
frequence = 0;

}
void loop() {
Temperature();
Girouette();
Anemometre();  

}
void Temperature(){
int n = analogRead(0);//Récupération de la valeur sur le port analogique//
  float v = n*(5.0/1024.0);//On remonte la chaîne d'information afin d'avoir la tension de sortie du capteur LM335
  float C = v*100-273.15; //Convertion de la température de Kelvin à Celsius//
    Serial.print("Celius:");
    Serial.println(C);
  float F = (C*9.0/5.0)+32 ; 
    Serial.print("Fahrenheit:");
    Serial.println(F);
  float K = C+273.15; 
    Serial.print("Kelvin:");
    Serial.println(K);
    delay(1000);
}


void Girouette(){
  Acquerirdir(); //On récupère la valeur analogique de la girouette 
  Traiterdir(); //On converti la valeur en bit précédement acquise en volt
  Afficherdir(); //On affiche la direction du vent
  delay(1000);  
}
void Acquerirdir()
{
  Ubit = analogRead(1); //On récupère la valeur sur 1024bits sur la pin Analog0 
  Serial.print("Ubit=");
  Serial.println(Ubit);
}


void Traiterdir()
{
  Uconv = 5 * Ubit / 1023;
  Serial.print("Uconv=");
  Serial.println(Uconv);
}



void Afficherdir()
{
  Serial.print("Direction du vent: ");
  int dir;
  
  if (Uconv <= 3.9 && Uconv >= 3.7)
  {
    Serial.println("N");
  }
  
  if (Uconv >= 2.1 && Uconv <= 2.3)
  {
    Serial.println("NE");
  }
  
  if (Uconv >= 0.3 && Uconv <= 0.5)
  {
    Serial.println("E");
  }
  
  if (Uconv <= 1 && Uconv >= 0.8)
  {
    Serial.println("SE");
  }
  
  if (Uconv <= 1.5 && Uconv >= 1.3)
  {
    Serial.println("S");
  }
  
  if (Uconv <= 3.09 && Uconv >= 3.07)
  {
    Serial.println("SO");
  }
  
  if (Uconv <= 4.63 && Uconv >= 4.61)
  {
    Serial.println("O");
  }
  
  if (Uconv >= 4.3 && Uconv <= 4.4)
  {
    Serial.println("SO");
  }
  
}


void Anemometre(){
  MesureFrequence(1000); /*Indiquer le temps en millis seconde*/
  Traitervit();
  Affichervit();
}
  void MesureFrequence(int tempsPourFrequence)
{
  temps = millis();
  while(millis()-temps < tempsPourFrequence)
  {
    etat = digitalRead(8);
    if(etat == 1 && etatAnterieur == 0)
    {
      impulsion=impulsion+1;
      //Serial.println(impulsion);
    }
      etatAnterieur = etat;
  
    
  }
   frequence = impulsion /(tempsPourFrequence * 0.001);
   Serial.println(impulsion);
}

void Traitervit()
{
  vitesseKMH = frequence * 2.4;
  vitesseMPH = frequence * 1.492;
  impulsion = 0;
}

void Affichervit()
{
  Serial.print(frequence);
  Serial.print(" Hz"); 
  Serial.print("\t"); 
  Serial.print(vitesseMPH);
  Serial.print(" MPH"); 
  Serial.print("\t"); 
  Serial.print(vitesseKMH);
  Serial.println("Km/h"); 
}  


