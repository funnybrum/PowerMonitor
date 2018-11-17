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

// Sonoff Pow R2 with CSE7789B
#define RELAY_PIN   D6  //GPIO12
#define LED_PIN     D7  //GPIO13
#define CSE7789_PIN TX  //U0RXD
#include "SensorCSE77xx.h"
#define MODEL_NAME "Sonoff Pow R2"

#endif
