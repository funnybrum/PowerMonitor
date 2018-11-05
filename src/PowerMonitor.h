#ifndef _POWER_MONITOR_H_
#define _POWER_MONITOR_H_

#define HTTP_PORT 80
#define HOSTNAME "power-monitor"

#define LOG_SIZE 256

// Buttons
#define BUTTON_PIN   D3  //GPIO0
#define RELAY_PIN    D6  //GPIO12
#define RED_LED_PIN  D6  //GPIO12
#define BLUE_LED_PIN D7  //GPIO13
#define CSE7789_PIN  TX  //U0RXD

#define CSE77XX_BAUD

#define MIN_TO_MILLIS(mins) (mins * 60L * 1000L)

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
#include "PowerSensor.h"
#include "Logger.h"

#endif
