#include <Arduino.h>
void maTache(void *parametres)
{
  while (1) // boucle infinie
  {
    Serial.printf("%s %08X Core = %d\n", 
      pcTaskGetName(NULL), 
      (int)xTaskGetCurrentTaskHandle(),
      xPortGetCoreID());
    
    delay(1000);
  }
}
void setup()
{
  int priorite = 0;
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.printf("Départ\n");
  xTaskCreatePinnedToCore(maTache, "Ma tâche", 10000, NULL, 1, NULL, 1);
  //xTaskCreatePinnedToCore(maTache,)
  //priorite = uxTaskPriorityGet(handle);
}
void loop()
{
  Serial.printf("%s %08X Core = %d\n", 
    pcTaskGetName(NULL), 
    (int)xTaskGetCurrentTaskHandle(),
    xPortGetCoreID());
  delay(1000);
}
