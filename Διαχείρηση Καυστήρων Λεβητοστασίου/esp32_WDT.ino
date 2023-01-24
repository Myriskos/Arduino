
//βιβλιοθηκη
#include <esp_task_wdt.h>

// δευτερόλεπτα WDT
#define WDT_TIMEOUT 20//χρονος επανεκινησης 0 εως απειρο

esp_task_wdt_init(WDT_TIMEOUT, true); //ενεργοποίηση πανικού ώστε το ESP32 να επανεκκινήσει
esp_task_wdt_add(NULL); //προσθήκη τρέχοντος νήματος στο ρολόι WDT

esp_task_wdt_init(WDT_TIMEOUT, false); //απενεργοποίηση πανικού ώστε το ESP32 να επανεκκινήσει

esp_task_wdt_reset();//μηδενισμος χρονου του φυλακα
