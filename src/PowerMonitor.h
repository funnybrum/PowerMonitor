#ifndef _POWER_MONITOR_H_
#define _POWER_MONITOR_H_

#define HTTP_PORT 80
#define HOSTNAME "power-monitor"

#define LOG_SIZE 1024

#define DEFAULT_RELAY_STATE on
// #define DEFAULT_RELAY_STATE off

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "Settings.h"
#include "SystemCheck.h"
#include "WiFi.h"
#include "Logger.h"
#include "InfluxDBCollector.h"
#include "WebServer.h"
#include "LED.h"
#include "Relay.h"
#include "PowerSensor.h"
#include "Button.h"

struct SettingsData {
    NetworkSettings network;
    InfluxDBCollectorSettings influxDB;
    PowerSensorSettings sensor;
};

// #define SONOFF_POW_R2
// #define KOOGEEK_P1EU
#define KOOGEEK_P1EU_V23


#ifdef SONOFF_POW_R2
    // Sonoff Pow R2 with CSE7789B
    #define RELAY_PIN   12  //GPIO12
    #define LED_PIN     13  //GPIO13
    #define CSE7789_PIN 1   //U0RXD
    #define BUTTON_PIN  0   // default is HIGH
    #define MODEL_NAME "Sonoff Pow R2"
    #include "SensorCSE77xx.h"
#endif

#ifdef KOOGEEK_P1EU
    // Koogeek P1EU with BL0937
    #define LED_PIN   0
    #define LED2_PIN  2
    #define RELAY_PIN 15
    #define SEL_PIN   12
    #define CF1_PIN   14
    #define CF_PIN    5
    #define MODEL_NAME "Koogeek P1EU"
    #define BUTTON_PIN 13   // default is HIGH
    #include "SensorBL0937.h"
#endif

#ifdef KOOGEEK_P1EU_V23
    // Koogeek P1EU with BL0937
    #define LED_PIN    13
    #define LED2_PIN   1
    #define RELAY_PIN  14
    #define SEL_PIN    12
    #define CF1_PIN    5
    #define CF_PIN     4
    #define BUTTON_PIN 3    // default is HIGH
    #define MODEL_NAME "Koogeek P1EU v2.3"
    #include "SensorBL0937.h"
#endif


extern Logger logger;
extern Settings settings;
extern SettingsData settingsData;
extern WiFiManager wifi;
extern SystemCheck systemCheck;
extern InfluxDBCollector telemetryCollector;

#endif
