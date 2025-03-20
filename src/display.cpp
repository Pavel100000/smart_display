#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <time.h>

#include "display.h"
#include "time_controller.h"
#include "wifi_controller.h"
#include "temperature_controller.h"

void draw_image_clock(MatrixPanel_I2S_DMA* display) {
    display->clearScreen();
    display->setTextSize(1);
    display->setCursor(8, 6);
    display->setTextColor(display->color565(255, 255, 255));

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    } else {
        display->printf("%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        display->setCursor(2, 20);
        display->printf("%02d.%02d.%04d", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
    }
}

void draw_image_temperature(MatrixPanel_I2S_DMA* display) {
    TemperatureController& temperatureController = TemperatureController::getInstance();
    display->clearScreen();
    display->setTextSize(1);
    display->setTextColor(display->color565(255, 255, 255));
    
    display->setCursor(2, 4);
    display->printf("Temp: %.1f", temperatureController.getTemperature());
    display->setCursor(2, 12);
    display->printf("Hum:  %.1f", temperatureController.getHumidity());
    display->setCursor(2, 20);
    display->printf("Heat: %.1f", temperatureController.getHeatIndex());
}