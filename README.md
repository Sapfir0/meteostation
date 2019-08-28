# Meteostation in our home!

## Ru

Т.к. как проект использует platformio, его необходимо установить
    
    pip3 install plaftormio --user

>Пины для подключения модулей, а также данные от домашней сети настраиваются в config.cpp.

## IDE installation guide
### Clion

Первоначальное создание Cmake

    pio init --ide clion
    
Выбрать ![](https://sun9-43.userapi.com/c855732/v855732524/d5eb8/WgKoxFqRcHA.jpg)


### Vscode 
Установить соответствующее расширение

### Arduino IDE
Т.к. тут нет прямой поддержки platformio и node mcu, придется поработать ручками. 

* `src/main.cpp` следует переименовать в `meteostation/meteostation.ino` - решит проблему с platformio
* <p> <a href="http://robotclass.ru/articles/node-mcu-arduino-ide-setup/">Инструкция по установке Node mcu в ArduinoIDE</a>

И компилировать `meteostation/meteostation.ino` в детской ide.


### Библиотеки:
Подгрузятся с platformio автоматически, но вот список зависимостей:

* Обязательные:
    * [Библиотека для асинхронной работы с ардуино](https://github.com/avdosev/async-library-arduino)
    * Библиотека для работы с DHT11
    * Библиотека для работы с LCD 1602
    * Все зависимости для них
* Необязательные (без нее все равно не скомпилируется)
    * LCD russian

### Информация о прошивках:
Если воспользовался [злой метеостанцией](https://github.com/Sapfir0/evil-meteostation), то нужно откатиться к дефолтной прошивке по [ссылке](https://www.espressif.com/en/support/download/other-tools?keys=&field_type_tid%5B%5D=14), или [прямая ссыль](https://www.espressif.com/sites/default/files/tools/flash_download_tools_v3.6.6_0.zip). Просто жмякаешь старт и произойдет откат.

[Центральная вики, объединяющая все невозможное](https://github.com/Sapfir0/Meteo-Server/wiki)


#### Примерная схема:

[![logo](https://pp.userapi.com/c855528/v855528450/36b3a/8wnNPy-strI.jpg)](https://www.circuito.io/app?components=513,9088,10167,10820,360216,417986)

>RGB модуль не обязателен, он только покажет цветом насколько благоприятная погода на улице.

>Всегда можно снять перемычку и подвести ее к средней ноге потенциометра чтобы сделать настраиваемую подстветку.


### Первый экран:
![alt text][one]

[one]: https://pp.userapi.com/c854024/v854024459/35ec1/xTbQma0wmM0.jpg "First information"

#### Когда погода состоит из нескольких слов, не показывается информация о городе

![alt text][four]

[four]: https://pp.userapi.com/c855036/v855036460/47882/hnfgMcYd_eY.jpg "Long info"

### Второй экран:
![alt text][two]

[two]: https://pp.userapi.com/c848736/v848736459/185833/tEAiChO1dEg.jpg "Second information"

### Третий экран:
![alt text][three]

[three]: https://pp.userapi.com/c846123/v846123459/1f23c9/MBUddAPYiYo.jpg "Third information"
