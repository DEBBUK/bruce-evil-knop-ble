#ifndef __EVIL_KNOP_BLE_MENU_H__
#define __EVIL_KNOP_BLE_MENU_H__

#include <MenuItemInterface.h>

class EvilKnopBleMenu : public MenuItemInterface {
public:
    EvilKnopBleMenu() : MenuItemInterface("EVIL KNOP BLE") { _titleColor = TFT_RED; }

    void optionsMenu(void);
    void drawIcon(float scale);
    bool hasTheme() { return false; }
    const String& themePath() override { return _emptyPath; }

private:
    static const String _emptyPath;
};

#endif
