#include <Arduino.h>
void maTache1(void *parametres)
{
  int i1 = 0;
  while (1) // boucle infinie
  {
    Serial.printf("maTache1 %4d\n", i1++);
    delay(1000);
    if (i1==5){
      vTaskSuspend(NULL);
    }    
  }
}
void maTache2(void *parametres)
{
  int i2 = 0;
  while (1) // boucle infinie
  {
    Serial.printf("maTache2 %4d\n", i2++);
    delay(4000);*
    if (il==10){
      vTaskDelete(NULL);
    } 
  }
}
void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.printf("Départ\n");
  xTaskCreate(
      maTache1,     /* Fonction de la tâche. */
      "Ma tâche 1", /* Nom de la tâche. */
      10000,        /* Taille de la pile de la tâche */
      NULL,         /* Paramètres de la tâche, NULL si pas de paramètre */
      1,            /* Priorité de la tâche */
      NULL);        /* Pointeur pour récupérer le « handle » de la tâche,
            optionnel */
  xTaskCreate(
      maTache2,     /* Fonction de la tâche. */
      "Ma tâche 2", /* Nom de la tâche. */
      10000,        /* Taille de la pile de la tâche */
      NULL,         /* Paramètres de la tâche, NULL si pas de paramètre */
      1,            /* Priorité de la tâche */
      NULL);        /* Pointeur pour récupérer le « handle » de la tâche,
            optionnel */
}
void loop()
{
  static int il = 0;
  Serial.printf("Loop %4d\n", il++);
  delay(1000);
}