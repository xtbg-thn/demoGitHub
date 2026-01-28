#include <Arduino.h>
TaskHandle_t h1;
TaskHandle_t h2;
void maTache1(void *parametres)
{
  int i1 = 0;
  while (1) // boucle infinie
  {
    Serial.printf("maTache1 %4d\n", i1++);
    delay(1000);
    if (i1 == 5)
    {
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

    delay(4000);
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
      &h1);         /* passer l'adresse du handle */
  xTaskCreate(
      maTache2,     /* Fonction de la tâche. */
      "Ma tâche 2", /* Nom de la tâche. */
      10000,        /* Taille de la pile de la tâche */
      NULL,         /* Paramètres de la tâche, NULL si pas de paramètre */
      1,            /* Priorité de la tâche */
      &h2);         /* passer l'adresse du handle */
}
void loop()
{
  static int il = 0;                // persist across loops
  Serial.printf("Loop %4d\n", il++);
  if (il == 10)
  {
    vTaskDelete(h2);
  }
  else if (il == 15)
  {
    vTaskResume(h1);
  }
  delay(1000);
}