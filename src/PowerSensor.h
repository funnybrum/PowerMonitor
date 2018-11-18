#ifndef _POWERSENSORBASE_H_
#define _POWERSENSORBASE_H_

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
};

#endif
