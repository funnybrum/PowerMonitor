#ifndef _POWERSENSORBASE_H_
#define _POWERSENSORBASE_H_

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
        virtual void loop();

        float getPower_W();
        float getVoltage_V();
        float getCurrent_A();
        float getPowerFactor();
        float getAveragePower60s();

        void setPowerCorrection(float coef);
        void setCurrentCorrection(float coef);
        void setVoltageCorrection(float coef);

        void loadSettings();

    protected:
        long voltage;
        long current;
        long power;
        
    private:
        float vCoef = 1.0f;
        float cCoef = 1.0f;
        float pCoef = 1.0f;
        long avg_power_value[60];
        uint8_t avg_power_readings[60];
        uint8_t avg_power_index;
};

#endif
