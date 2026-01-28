#include <Arduino.h>
// Handle de la queue
xQueueHandle queue;
void tacheEnvoi(void *parametres)
{
  int i = 100;
  while (1)
  {
    if (xQueueSend(queue, &i, portMAX_DELAY) == pdPASS)
    {
      Serial.printf("Envoi %d\n", i);
      i++;
    }
    else
    {
      Serial.printf("Envoi échec\n");
    }
    delay(2000);
  }
}
void tacheReception(void *parametres)
{
  int i;
  while (1)
  {
    if (xQueueReceive(queue, &i, 0) != pdTRUE)
    {
      Serial.printf("Réception échec\n");
    }
    else
    {
      Serial.printf("Réception %d\n", i);
    }
    delay(1000);
  }
}
void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.printf("Départ\n");
  // Création de la file
  queue = xQueueCreate(10, sizeof(int));
  // La queue permet a donne une limite de fois avant de bloquer l'envoi ex: si la queue atteint 10 éléments, l'envoi sera bloqué jusqu'à ce qu'un élément soit reçu
  xTaskCreate(
      tacheEnvoi, /* Fonction de la tâche. */
      "Envoi",    /* Nom de la tâche. */
      10000,      /* Taille de la pile de la tâche */
      NULL,       /* Paramètres de la tâche, NULL si pas de paramètre */
      1,          /* Priorité de la tâche */
      NULL);      /* Pointeur pour récupérer le « handle » de la tâche, optionnel */
  xTaskCreate(
      tacheReception, /* Fonction de la tâche. */
      "Réception",    /* Nom de la tâche. */
      10000,          /* Taille de la pile de la tâche */
      NULL,           /* Paramètres de la tâche, NULL si pas de paramètre */
      1,              /* Priorité de la tâche */
      NULL);          /* Pointeur pour récupérer le « handle » de la tâche, optionnel */
  vTaskDelete(NULL); // Supprime la tâche en cours quand le queue est pleine
}
void loop()
{
  // Ne s'exécute pas
}
// dabord on envoie et attend de recevoir jusqu'à ce que la queue soit pleine et on change la taille de la queue
// ensuite on peut continuer a tester sans attendre l'envoie