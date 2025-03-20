#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "wifi_controller.h"
#include "bluetooth_controller.h"
#include "temperature_controller.h"
#include "time_controller.h"
#include "display.h"

DisplayController& displayController = DisplayController::getInstance();
MatrixPanel_I2S_DMA *display;

void setup() {
    Serial.begin(115200);
    displayController.begin();
    display = displayController.getDisplay();
    display->setBrightness8(displayController.getBrightness());

    xTaskCreate(bluetoothSetup, "bluetoothSetup", 4096, NULL, 1, NULL);
    xTaskCreate(wifiSetup, "wifiSetup", 4096, NULL, 1, NULL);

    while (!isWifiConnected()) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    timeSetup();
}

void loop() {
    static int current_brightness = 0;
    if (current_brightness != displayController.getBrightness()) {
        display->setBrightness8(displayController.getBrightness());
        current_brightness = displayController.getBrightness();
    }

    static enum ImageType current_image = ImageType::CLOCK_IMAGE;
    if (current_image != displayController.getImage()) {
        current_image = displayController.getImage();
        Serial.println("Changing image");
        Serial.printf("Current image: %d\n", current_image);
    }

    image_draws[current_image](display);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
