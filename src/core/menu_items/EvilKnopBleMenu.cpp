#include "EvilKnopBleMenu.h"
#include "core/display.h"
#include "core/utils.h"
#include "modules/ble/ble_spam.h"
#include <globals.h>

const String EvilKnopBleMenu::_emptyPath = String("");

void EvilKnopBleMenu::optionsMenu() {
    drawMainBorderWithTitle("EVIL KNOP BLE");
    tft.setTextColor(TFT_RED, bruceConfig.bgColor);
    tft.setTextSize(FM);
    tft.drawCentreString("Booting overdrive...", tftWidth / 2, tftHeight / 2 - LH, 1);
    vTaskDelay(pdMS_TO_TICKS(400));
    evilKnopBleRun();
    returnToMenu = true;
}

void EvilKnopBleMenu::drawIcon(float scale) {
    clearIconArea();

    int cx = iconCenterX;
    int cy = iconCenterY;
    int radius = scale * 22;

    // Red warning circle
    tft.drawCircle(cx, cy, radius, TFT_RED);
    tft.drawCircle(cx, cy, radius - 3, TFT_RED);

    // Red lightning bolt inside
    int lw = scale * 4;
    tft.drawWideLine(cx + scale * 2, cy - radius + scale * 6, cx - scale * 6, cy + scale * 2, lw, TFT_RED, TFT_RED);
    tft.drawWideLine(cx - scale * 6, cy + scale * 2, cx - scale * 2, cy + scale * 2, lw, TFT_RED, TFT_RED);
    tft.drawWideLine(cx - scale * 2, cy + scale * 2, cx - scale * 2, cy + radius - scale * 6, lw, TFT_RED, TFT_RED);
    tft.drawWideLine(cx + scale * 2, cy + radius - scale * 6, cx + scale * 2, cy + scale * 2, lw, TFT_RED, TFT_RED);

    // Red exclamation dot under bolt
    tft.fillCircle(cx, cy + radius + scale * 2, scale * 3, TFT_RED);
}
