#include "PowerMonitor.h"
#include "DataCollector.h"

DataCollector::DataCollector():
    InfluxDBCollector(&logger,
                      NULL,
                      &settings.getSettings()->influxDB,
                      &settings.getSettings()->network) {
}

bool DataCollector::shouldCollect() {
    return true;
}

void DataCollector::collectData() {
    this->append("power", powerSensor.getPower_W(), 1);
    this->append("current", powerSensor.getCurrent_A(), 2);
    this->append("voltage", powerSensor.getVoltage_V(), 1);
    this->append("power_factor", powerSensor.getPowerFactor(), 2);
    this->append("free_heap", ESP.getFreeHeap());
}

bool DataCollector::shouldPush() {
    return false;
}   

void DataCollector::onPush() {
}