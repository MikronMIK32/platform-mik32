
# Журнал изменений
Все заметные изменения в проекте будут задокументированы в этом файле.

## Типы изменений
- **Добавлено** — для новых функций.
- **Изменено** — для изменений в существующей функциональности.
- **Устарело** — для функций, которые скоро будут удалены.
- **Удалено** — для удалённых на данный момент.
- **Исправлено** — для любых исправлений багов.
- **Безопасность** — на случай уязвимостей.

## [Невыпущенное] - yyyy-mm-dd
 
В этот раздел следует заносить изменения, которые ещё не были добавлены в новый релиз.
 
### Добавлено
  
### Изменено
 
### Исправлено

## [v0.5.0] - 2025-03-17
 
### Добавлено
- Поддержка учебной отладочной платы;
- Возможность сборки без framework. При удалении опции framework из 
platformio.ini заголовочные файлы и библиотеки не собираются, их следует 
добавлять в src или lib.
  
### Изменено
- Обновлены примеры до версии v0.1.2;
- Требуемые версии uploader'а и framework'а увеличены до v0.3.3 и v0.2.2 
соответственно.
 
### Исправлено
- Максимальный размер по умолчанию для платы Старт;
- При выборе скрипта линковки по произвольному пути, содержащая его директория 
добавляется в пути библиотек для линковщика, для корректного поиска вложенных 
скриптов;
- Добавлена остановка сборки, если не найден скрипт линковки по пути, 
указанному в board_build.ldscript - для сборки с framework (custom.py);
- Исправлено описание регистров TIMER32 (@adogadkin).

### Удалено
- Выбор отладчика из списка поддерживаемых протоколов. Предполагаем, что опция 
upload_protocol обозначает название конфигурации для openocd, если не указано 
custom;
- Печать выбранного скрипта линковки в консоль.

## [v0.4.0] - 2024-11-05
 
Добавлена поддержка платы START-MIK32-V1

## [v0.3.0] - 2024-08-14
 
Выпущены изменения, находившиеся в разработке, в т.ч. описание регистров для отладки, 
расширен набор поддерживаемых через OpenOCD отладочных адаптеров, настройка частоты
внешнего генератора/резонатора параметром f_cpu в файле platformio.ini, поддержка Linux
 
### Добавлено

- [Update mik32v2.svd](https://github.com/MikronMIK32/platform-mik32/commit/8f633cceca098c2525db88dc7f3175f4f693f7b2)
  Добавлено SVD описание регистров
- [upload speed support](https://github.com/MikronMIK32/platform-mik32/commit/d77cd8161408702b08485caaeea45021f5a178f3)
  Добавлена настройка скорости интерфейса загрузки
- [support for debug_speed option in pio,ini](https://github.com/MikronMIK32/platform-mik32/commit/1b70ebac81261c23b8a8f88d0a65dc8b27f41ff4)
  Добавлена настройка скорости интерфейса отладки
- [test support more debug interfaces](https://github.com/MikronMIK32/platform-mik32/commit/b7b629fbdf6f25bda548d1b6249dcfc884e2de70)
  Добавлен список поддерживаемых отладочных интерфейсов
- [change openocd package, add usb blaster option](https://github.com/MikronMIK32/platform-mik32/commit/8b865c7a3810871bba7ebdbde7679837da94ee67)
  Добавлен USB Blaster в список поддерживаемых отладочных интерфейсов
- [Add OSC_SYSTEM_VALUE define](https://github.com/MikronMIK32/platform-mik32/commit/a644f7d61ead289934807623fe7f1a83cc9acb12)
  Определена константа OSC_SYSTEM_VALUE для выбора частоты основного генератора OSC32M, значение задается параметром f_cpu 
- [linux support test](https://github.com/MikronMIK32/platform-mik32/commit/eef295282ba3eb5f7cc1b734c302066b9cbb5fc5)
  Добавлена поддержка Linux
- [add examples submodule](https://github.com/MikronMIK32/platform-mik32/commit/85d8851f51efc13d2393f8620fb0d3dc2bdc4bad)
  В платформу добавлены примеры
  
### Изменено

- [add interface.cfg path finding](https://github.com/MikronMIK32/platform-mik32/commit/17d007824d27898f7bcfb8f0d60cfc35ea90fc27)
  Улучшен механизм поиска файла конфигурации интерфейса загрузки/отладки
- [add project folder in search paths](https://github.com/MikronMIK32/platform-mik32/commit/308fca812119b1cbca07b11c7473958d338bab23)
  Изменен механизм поиска скрипта линковки, выполняется начиная с папки проекта
- [update version](https://github.com/MikronMIK32/platform-mik32/commit/41d7b7f5a5661efb97752f14a5ba81e77f86f6fc)
  Изменена версия инструментария GCC RISC-V до последней доступной в репозитории PlatformIO
 
### Исправлено

- [fix inaccessable memory in ro memory](https://github.com/MikronMIK32/platform-mik32/commit/0502f69da4d97fa3769c10a9777f488b904f0f94)
  Исправлена ошибка с добавлением точек останова во внешней памяти
- [fix ram debug](https://github.com/MikronMIK32/platform-mik32/commit/9b6727a4bff8946ee0a754ec61f7d1bf2bc710aa)
  Исправлена ошибка доступа отладчика в ОЗУ
- [getting a list of boards before installing deps fix](https://github.com/MikronMIK32/platform-mik32/commit/943324b26105d425c737eefa38065c6521747d52)
  Исправлена ошибка создания проекта при отсутствии зависимостей платформы

## [v0.2.1] - 2023-03-29
 
Исправлены ошибки с загрузкой программы и отладкой
 
### Исправлено

- [enable debug symbols generation](https://github.com/MikronMIK32/platform-mik32/commit/617425bac354f98a58f04d9a964720774277523f)
  Включена генерация отладочных символов
- [fix upload for user names with whitespaces](https://github.com/MikronMIK32/platform-mik32/commit/dcd5ba6aa8482586dc0f40e55a42b1f9e38e612f)
  Исправлена загрузка программы для путей с пробелами
 
## [v0.2.0-alpha] - 2023-03-14
  
Тестовый релиз

Были произведены следующие изменения:

- Библиотеки из фреймворка теперь собираются вместе с проектом
- Изменен выбор источника загрузки
- Источник загрузки привязан к имени скрипта ld. 

Для выбора источника загрузки необходимо указать ram, eeprom или spifi в имени файла перед разделителем (0...9 . _ -). Программа будет собрана с помощью выбранного ld-скрипта и загружена в выбранную память.

Ld-скрипт настраивается в файле platformio.ini с параметром:

```
board_build.ldscript = eeprom.ld
```

На данный момент режим загрузки spifi недоступен в этой платформе, его поддержка будет добавлена позже.
 