#ifndef _POWER_MONITOR_H_
#define _POWER_MONITOR_H_

#define HTTP_PORT 80
#define HOSTNAME "power-monitor"

#define LOG_SIZE 256

/**
 * Define one of the following to specify the device type:
 *   * SONOFF_POW_R2
 *   * BW_SHP2
 */

#define BW_SHP2

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

// Koogeek/Blitzwolf SP2 with BL0937
#define LED_PIN   0
#define RELAY_PIN 15
#define SEL_PIN   12
#define CF1_PIN   14
#define CF_PIN    5
#include "SensorBL0937.h"

#endif
