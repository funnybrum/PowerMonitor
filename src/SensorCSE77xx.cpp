#include "PowerMonitor.h"

#ifdef SONOFF_POW_R2

unsigned long last_log = millis();

#define GET_VALUE(index) (unsigned long)(data[index]  << 16 | data[index+1]  << 8 | data[index+2])

#define GET_COEF_V GET_VALUE(2)
#define GET_CYCLE_V GET_VALUE(5)

#define GET_COEF_C GET_VALUE(8)
#define GET_CYCLE_C GET_VALUE(11)

#define GET_COEF_P GET_VALUE(14)
#define GET_CYCLE_P GET_VALUE(17)

void PowerSensor::begin() {
    PowerSensorBase::begin();

    Serial.begin(4800);
    while (! Serial) {
        delay(1);
    }
    logger.log("HW Serial started");
}

void PowerSensor::loop() {
    while (Serial.available() > 0) {
        data[pos] = Serial.read();
        if (pos == 1 && data[1] != 0x5A) {
            // Not having 0x5A on position 1 means that data is with some
            // offset. Move to the next position only when we have the expected
            // value here.
            pos--;
        }
        pos++;
        if (pos == 24) {
            pos = 0;
            processPacket();

            // --- DEBUG LOG START ---
            // if (millis() - last_log > 5000) {
            //     String hex_dump = String();
            //     for (int i = 0; i < 24; i++) {
            //         hex_dump.concat("0x" + String(data[i],HEX) + " ");
            //     }
            //     logger.log(hex_dump);
            //     logger.log("V:%lu, C:%lu, P:%lu", voltage, current, power);
            //     last_log = millis();
            // }
            // --- DEBUG LOG END ---


        }
    }
}

bool PowerSensor::isChecksumCorrect() {
    uint8_t sum = 0;
    for (int pos = 2; pos <= 22; pos++) {
        sum += data[pos];
    }

    return sum == data[23];
}

void PowerSensor::processPacket() {
    // PDF -> 3.7 voltage, current, active power calculation reference flow
    // chart. With one mod - ignore data[20], bit 4 in some cases.

    if (data[0] == 0x55 ||
        ((data[0] & 0xF0) == 0xF0 && bitRead(data[0], 2) == 0 && bitRead(data[0], 3) == 0)) {
        if (data[1] == 0x5A) {
            if (isChecksumCorrect()) {
                if (bitRead(data[20], 4) || (bitRead(data[20], 5) && bitRead(data[20], 6))) {
                    // read the power
                    if ((data[0] & 0xF0) == 0xF0 && bitRead(data[0], 1)) {
                        power = 0;
                    } else {
                        power = GET_COEF_P / GET_CYCLE_P;
                    }

                    // A bit of optimization for better detection of no load.
                    // Power being <=2W is considered as no load.
                    if (power <= 2) {
                        power = 0;
                    }
                }
                
                if (bitRead(data[20], 5)) {
                    // read the current
                    if (power == 0) {
                        current = 0;
                    } else {
                        // Convert from A to mA. Otherwise we lookse precision
                        // due to rounding errors.
                        current = 1000 * GET_COEF_C / GET_CYCLE_C;
                    }
                }

                if (bitRead(data[20], 6)) {
                    // read the voltage
                    voltage = GET_COEF_V / GET_CYCLE_V;
                }
            }
        }
    }
}

PowerSensor powerSensor = PowerSensor();

#endif