#include <Arduino.h>
void maTache(void *parametres)
{
 int v1 = 0;
 static int v2 = 0;
 while (1) // boucle infinie
 {
 Serial.printf("%s : v1=%d v2=%d\n", pcTaskGetName(NULL), v1, v2);
 v1++;
 v2++;
 delay(500);
 }
}
void setup()
{
  Serial.begin(115200);
  Serial.printf("Initialisation\n");
  //pinMode(16, OUTPUT); // configure P1.16 en sortie
  // Création de la tâche périodique
  xTaskCreate(maTache, "Tâche 1", 10000, NULL, 2, NULL);
  xTaskCreate(maTache, "Tâche 2", 10000, NULL, 2, NULL);

}
void loop()
{
  //static int i = 0;
  //Serial.printf("Boucle principale : %d\n", i++);
  delay(1000);
}
// v1 s'incrémente 1 fois à chaque itération de la tâche
// v2 s'incrémente 2 fois à chaque itération de la tâche