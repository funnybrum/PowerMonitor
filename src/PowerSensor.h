#ifndef _POWERSENSORBASE_H_
#define _POWERSENSORBASE_H_

#include "WebServerBase.h"

const char POWER_SENSOR_CONFIG_PAGE[] PROGMEM = R"=====(
<fieldset style='display: inline-block; width: 300px'>
<legend>Power sensor settings</legend>
Power correction coefficient:<br> 
<input type="text" name="pcoef" value="%f"><br>
<small><em>1.00 for no correction, [0.8, 1.2]</em></small><br><br>
Voltage correction coefficient:<br>
<input type="text" name="vcoef" value="%f"><br>
<small><em>1.00 for no correction, [0.8, 1.2]</em></small><br><br>
Voltage correction coefficient:<br>
<input type="text" name="ccoef" value="%f"><br>
<small><em>1.00 for no correction, [0.8, 1.2]</em></small><br><br>
</fieldset>
)=====";

struct PowerSensorSettings {
    float voltageCoef;
    float currentCoef;
    float powerCoef;
};

/*
 * Common power sensor interface.
 */
class PowerSensorBase {
    public:
        virtual void begin();
        virtual void loop() = 0;

        float getPower_W();
        float getVoltage_V();
        float getCurrent_A();
        float getPowerFactor();

        void get_config_page(char* buffer);
        void parse_config_params(WebServerBase* webServer);
    protected:
        long voltage;
        long current;
        long power;
};

#endif
