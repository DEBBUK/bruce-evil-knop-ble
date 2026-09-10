# ⚡ EVIL KNOP BLE — Bruce Custom

> Максимально мощная BLE-атака на iPhone с красной кнопкой в главном меню.

Кастомная прошивка на основе [Bruce Firmware](https://github.com/BruceDevices/firmware) для **LilyGO T-Display TTGO (ESP32)**. Добавляет в главное меню пункт **`EVIL KNOP BLE`** — при нажатии мгновенно запускает поливальную BLE-атаку на Apple-устройства с попапами **"Setup New Phone"** (настройка нового айфона).

![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Board](https://img.shields.io/badge/Board-LilyGO%20T--Display%20TTGO-orange)
![Status](https://img.shields.io/badge/Status-Working-brightgreen)

---

## 🚀 Возможности

| Функция | Описание |
|---|---|
| ⚡ **EVIL KNOP BLE** | Новый пункт в главном меню (первый, подсвечен красным) |
| 🍎 **Apple Action Spam** | Попапы **"Setup New Phone"**, "Apple TV Setup", "HomePod Setup" и др. |
| 🔥 **Макс. мощность** | Радио передаёт на полной мощности (`TX_MAX`) |
| ⚙️ **Мин. интервал** | `adv_ms=3`, `gap_ms=3` — максимальная скорость пакетов |
| 🎭 **Ротация MAC** | Новый MAC-адрес на каждый пакет (`EVERY_PACKET`) |
| 🛑 **Быстрый выход** | Атака идёт до нажатия `ESC` |

## 📸 Что увидишь

При нажатии на пункт **`EVIL KNOP BLE`** в главном меню:

```
┌─────────────────────────────┐
│      EVIL KNOP BLE          │
│                             │
│  ATTACK: Setup New Phone    │
│  iPhone BLE Spam @ MAX      │
│  Press ESC to stop          │
└─────────────────────────────┘
```

Айфоны рядом получают системные попапы **"Настройка нового iPhone"** прямо на экран блокировки.

---

## 📂 Структура

```
├── firmware.bin                     # Готовая прошивка для заливки
├── patches/evil-knop-ble.patch      # Патч к исходникам Bruce
└── src/                             # Изменённые файлы (оригинал -> мод)
    ├── core/
    │   ├── menu_items/
    │   │   └── EvilKnopBleMenu.cpp/h    # Кнопка EVIL KNOP BLE (красная иконка)
    │   └── main_menu.cpp/h              # Пункт подключён в главное меню
    ├── include/
    │   └── MenuItemInterface.h          # Поддержка цвета заголовка (_titleColor)
    └── modules/ble/
        ├── ble_spam.cpp/h               # evilKnopBleRun() — запуск атаки
```

## 🛠️ Как собрать

```bash
# 1. Клонируем исходники Bruce
git clone https://github.com/BruceDevices/firmware.git
cd firmware

# 2. Накладываем патч
git apply ../bruce-evil-knop-ble/patches/evil-knop-ble.patch

# 3. Собираем под LilyGO T-Display TTGO
python -m platformio run -e lilygo-t-display-ttgo
# Результат: Bruce-lilygo-t-display-ttgo.bin
```

## 🔌 Как прошить

```bash
# Убедись, что ESP32 подключён (порт COM может отличаться)
python -m esptool --chip esp32 --port COM4 --baud 460800 write-flash -z 0x0 firmware.bin
```

Или открой **firmware.bin** через онлайн-flasher Bruce:

- [Bruce Flasher](https://bruce.fff.bot) → Upload Firmware → выбрать `firmware.bin`

---

## 📜 Изменённые файлы (дифф от Bruce)

| Файл | Что добавлено |
|---|---|
| `src/core/menu_items/EvilKnopBleMenu.cpp` | **Новый.** Иконка (красный круг + молния), запуск атаки |
| `src/core/menu_items/EvilKnopBleMenu.h` | **Новый.** Класс меню, `_titleColor = TFT_RED` |
| `src/core/main_menu.cpp` | Пункт `&evilKnopBleMenu` первым в `_menuItems` |
| `src/core/main_menu.h` | `#include` + член `EvilKnopBleMenu evilKnopBleMenu;` |
| `include/MenuItemInterface.h` | Поле `_titleColor`, красный заголовок в `drawTitle()` |
| `src/modules/ble/ble_spam.cpp` | Новая публичная функция `evilKnopBleRun()` |
| `src/modules/ble/ble_spam.h` | Объявление `void evilKnopBleRun();` |

---

## ⚠️ Дисклеймер

- Проект создан **только для исследовательских и учебных целей**.
- Проверяй воздействие **только на свои устройства** или с явного разрешения владельца.
- Использование атак на чужие устройства может нарушать законы твоей страны. Ответственность — на тебе.

---

## 🙏 Спасибо

- [BruceDevices/firmware](https://github.com/BruceDevices/firmware) — оригинальная прошивка
- [Flipper Zero ble_spam](https://github.com/flipperdevices/flipperzero) — база Apple-попапов