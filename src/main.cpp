#include <Arduino.h>
void tachePeriodique(void *pvParameters)
{
  TickType_t xLastWakeTime;
  double x = 0, y = 0;
  // Lecture du nombre de ticks quand la tâche débute
  xLastWakeTime = xTaskGetTickCount();
  while (1)
  {
    digitalWrite(16, HIGH); // Met le bit 16 du port 1 à 1 sans toucher aux autres bits
    TickType_t debCalcul = xTaskGetTickCount();
    // Des calculs pour que la tâche occupe le processeur
    int nbTour = 3000 + rand() % 3000;
    for (int i = 0; i < nbTour; i++)
    {
      double xn = sin(x) + cos(y);
      double yn = cos(x) + sin(y);
      double d = sqrt(xn * xn + yn * yn);
      if (d == 0)
      {
        x = 0;
        y = 0;
      }
      else
      {
        x = xn / d;
        y = yn / d;
      }
    }
    TickType_t finCalcul = xTaskGetTickCount();
    Serial.printf("Temps de calcul = %u\n", finCalcul - debCalcul);
    // Endort la tâche pendant le temps restant par rapport au réveil,
    // ici 200ms, donc la tâche s'effectue toutes les 200ms
    digitalWrite(16, LOW); // Met le bit 16 du port 1 à 0 sans toucher aux autres bits
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(200)); // toutes les 200 ms
  }
}
void setup()
{
  Serial.begin(115200);
  Serial.printf("Initialisation\n");
  pinMode(16, OUTPUT); // configure P1.16 en sortie
  // Création de la tâche périodique
  xTaskCreate(tachePeriodique, "Tâche périodique", 10000, NULL, 2, NULL);
}
void loop()
{
  static int i = 0;
  Serial.printf("Boucle principale : %d\n", i++);
  delay(1000);
}
