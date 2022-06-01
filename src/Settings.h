#pragma once

#include "SettingsBase.h"
#include "WiFi.h"
#include "InfluxDBCollector.h"
#include "PowerSensor.h"


struct SettingsData {
    NetworkSettings network;
    InfluxDBCollectorSettings influxDB;
    PowerSensorSettings sensor;
};

struct Empty {};

class Settings: public SettingsBase<SettingsData, Empty> {
    public:
        Settings();
        SettingsData* getSettings();

    protected:
        void initializeSettings();
        Empty* getRTCSettings();

    private:
        SettingsData settingsData;
};

