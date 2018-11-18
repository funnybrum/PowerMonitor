#ifndef _POWER_MONITOR_H_
#define _POWER_MONITOR_H_

#define HTTP_PORT 80
#define HOSTNAME "power-monitor"

#define LOG_SIZE 256

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "Settings.h"
#include "SystemCheck.h"
#include "WebServer.h"
#include "WiFi.h"
#include "LED.h"
#include "Relay.h"
#include "Logger.h"
#include "PowerSensor.h"

#define KOOGEEK_P1EU
// #define SONOFF_POW_R2

#ifdef SONOFF_POW_R2
    // Sonoff Pow R2 with CSE7789B
    #define RELAY_PIN   D6  //GPIO12
    #define LED_PIN     D7  //GPIO13
    #define CSE7789_PIN TX  //U0RXD
    #define MODEL_NAME "Sonoff Pow R2"
    #include "SensorCSE77xx.h"
#endif

#ifdef KOOGEEK_P1EU
    // Koogeek P1EU with BL0937
    #define LED_PIN   0
    #define RELAY_PIN 15
    #define SEL_PIN   12
    #define CF1_PIN   14
    #define CF_PIN    5
    #define MODEL_NAME "Koogeek P1EU"
    #include "SensorBL0937.h"
#endif

#endif
