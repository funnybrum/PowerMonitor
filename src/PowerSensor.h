#ifndef _POWERSENSORBASE_H_
#define _POWERSENSORBASE_H_

/*
 * Common power sensor interface.
 */
class PowerSensorBase {
    public:
        virtual void begin() = 0;
        virtual void loop() = 0;

        float getPower_W();
        float getVoltage_V();
        float getCurrent_mA();
        float getPowerFactor();

        void setPowerCorrection(float coef);
        void setCurrentCorrection(float coef);
        void setVoltageCorrection(float coef);

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
