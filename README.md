# MIK32: Платформа разработки для PlatformIO

MIK32 АМУР - 32-х битный микроконтроллер с ГОСТ криптозащитой на основе процессорного ядра RISC-V.

Дополнительная информация:
- [Микрон](https://mikron.ru/products/mikrokontrollery/mk32-amur/) (Страница микроконтроллера на сайте АО Микрон)
- [Wiki](https://wiki.mik32.ru/) (Вики страница с информацией о микроконтроллере)

# Установка

1. [Установить PlatformIO](https://platformio.org/)
2. Создайте проект PlatformIO и настройте опцию платформы в файле [platformio.ini](https://docs.platformio.org/page/projectconf.html/):

## Стабильная версия

```
[env:mik32v2]
platform = https://github.com/platformio/platform-espressif32.git#v0.2.0-alpha
board = mik32v2
board_build.ldscript=eeprom
```

## Версия для разработки

```
[env:mik32v2]
platform = https://github.com/platformio/platform-espressif32.git
board = mik32v2
board_build.ldscript=eeprom
```

## Настройки platformio.ini

### `upload_protocol` - выбор отладчика

Значение по умолчанию: `mikron-link`

Возможные значения:

- `mikron-link` - Программатор MIK32;
- `olimex-arm-usb-ocd` - Olimex ARM-USB-OCD;
- `olimex-arm-usb-ocd-h` - Olimex ARM-USB-OCD-H;
- `olimex-arm-usb-tiny-h` - Olimex ARM-USB-TINY-H;
- `olimex-jtag-tiny` - Olimex ARM-USB-TINY;
- `jlink` - JLink;
- `altera-usb-blaster` - USB Blaster;
- `sipeed-rv-debugger` - Sipeed RV Debugger.

Пример использования: 
```
upload_protocol = jlink
```


### `board_build.ldscript` - выбор ld скрипта

Значение по умолчанию: `eeprom`;

Возможные значения:

- `eeprom` - программа сохраняется во внутренней памяти MIK32;
- `spifi` - программа сохраняется во внешней памяти;
- `ram` - программа сохраняется в оперативной памяти.

Пример использования: 

```
board_build.ldscript = spifi
```


### `upload_speed` - Частота интерфейса загрузчика

Частота тактового сигнала интерфейса jtag, кГц.

Значение по умолчанию: `500`;

Пример использования: 

```
upload_speed = 3200
```


### `board_build.f_cpu` - частота основного тактового генератора

Переопределение частоты основного генератора тактовой частоты, Гц в формате длинного числа Си.

Значение по умолчанию: `32000000L`

Пример использования: 

```
board_build.f_cpu = 4000000L
```


### `board_upload.maximum_size` - переопределение максимального размера программы, байты.

Размер программы вычисляется Platformio по суммарному размеру секций .text и .data. Если для размещения программы используется только один вид памяти, то maximum_size нужно установить по объему этой памяти. Полезно для настройки максимального объема внешней памяти.

Значение по умолчанию: 8192;

Пример использования: 

```
board_upload.maximum_size = 4194304
```
