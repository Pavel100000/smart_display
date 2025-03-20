#include <ArduinoNvs.h>

#include "time_controller.h"

void timeSetup() {
    NVS.begin();
    String timezone = NVS.getString("timezone");
    if (timezone) {
        configTime(atoi(timezone.c_str()) * 3600, 0, "pool.ntp.org", "time.nist.gov");
    } else {
        configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    }
    NVS.close();
}
