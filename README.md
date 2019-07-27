# Meteostation in our home!

## En
Small meteostation for smart home

<p> <a href="https://yadi.sk/d/TCMbow6C5QRp4w">Librarys for normally use app</a>
<p>Throw this in /Documents/Arduino/ on Windows or in ~/Arduino on Linux(with default settings)

## Ru
<p> <a href="https://yadi.sk/d/TCMbow6C5QRp4w">Либы для использования метеостанции </a>
<p>Кинуть в ~/Documents/Arduino/ на Windows или в ~/Arduino на Linux(по дефолту)
<p>Компилим файл meteostation.ino в любой ide
<p>Пины для подключения модулей, а также данные от домашней сети настраиваются в config.hpp.

### Библиотеки:

* Обязательные:
    * Библиотека для работы с DHT11
    * Библиотека для работы с LCD 1602
    * Все зависимости для них
* Необязательные
    * LCD russian

### Информация о прошивках:
Если воспользовался [злой метеостанцией](https://github.com/Sapfir0/evil-meteostation), то нужно откатиться к дефолтной прошивке по [ссылке](https://www.espressif.com/en/support/download/other-tools?keys=&field_type_tid%5B%5D=14), или [прямая ссыль](https://www.espressif.com/sites/default/files/tools/flash_download_tools_v3.6.6_0.zip). Просто жмякаешь старт и произойдет откат.

[Центральная вики, объединяющая все невозможное](https://github.com/Sapfir0/Meteo-Server/wiki)


#### Примерная схема:
![alt text][logo]

[logo]: https://pp.userapi.com/c855528/v855528450/36b3a/8wnNPy-strI.jpg "https://www.circuito.io/app?components=513,9088,10167,10820,360216,417986"
https://www.circuito.io/app?components=513,9088,10167,10820,360216,417986

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


## FAQ

<p> <a href="http://robotclass.ru/articles/node-mcu-arduino-ide-setup/">Инструкция по установке Node mcu в ArduinoIDE</a>



