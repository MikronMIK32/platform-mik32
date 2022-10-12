# PlatformIO toolchain for MIK-32

Инструменты разработки для МК-32 Амур под платформу PlatformIO

## Как использовать

- Скачать архив репозитория
- Распаковать его в директорию
  - Windows: `C:\Users\USER_NAME\.platformio\`
- Создать новый проект в **VSCode** или **CLion** выбрав ``MIKRON MIK32``
- Настроить среду для загрузки и отладки в файле ``platformio.ini``:

```
[env:mik32]
platform = MIK32
board = mik32

# Upload configuration
board_upload.protocol = ftdi
board_upload.interface = xds100v2
board_upload.adapter_speed = 1000
board_upload.ldscript = eeprom

# Debug configuration
board_debug.protocol = ftdi
board_debug.interface = xds100v2
board_debug.adapter_speed = 1000
board_debug.ldscript = ram
```

## Проверенные прошивальщики

- Olimex arm-usb-ocd-h (FT2232H)
```
board_{upload/debug}.protocol = ftdi
board_{upload/debug}.interface = m-link
```
- XDS100v2
```
board_{upload/debug}.protocol = ftdi
board_{upload/debug}.interface = xds100v2
```
- J-Link
```
board_{upload/debug}.protocol = jlink
```

## Параметры среды

| Параметр                           | Описание                                           |
|------------------------------------|----------------------------------------------------|
| board_{upload/debug}.protocol      | Протокол прошивальщика                             |
| board_{upload/debug}.interface     | Интерфейс прошивальщика (Если протокол - **ftdi**) |
| board_{upload/debug}.adapter_speed | Скорость JTAG в кГц                                |
| board_{upload/debug}.ldscript      | Скрипт сборщика проекта                            |

## Скрипты сборщика

| Сборщик | Описание                                                         | BOOT0 | BOOT1 |
|---------|------------------------------------------------------------------|-------|-------|
| epprom  | Запись в EEPROM микроконтроллера                                 | GND   | GND   |
| ram     | Запись в оперативную память МК. Используется для режима отладки. | +3.3v | GND   |



