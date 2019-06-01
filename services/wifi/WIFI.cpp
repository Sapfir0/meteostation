#include "../../sensors/gradusnik.hpp"

#include "../translating/rus.hpp"
#include "../json/jsonParse.hpp"

void WIFI::getWeatherData()  { // client function to send/receive GET request data.
    connectToServer(CityID, APIKEY);
    result = getResponseFromServer(result);
    parsingJSON(result);
}

// DynamicJsonDocument WIFI::setJSON() {    
//     Gradusnik grad;
//     rus rus;
//     std::time_t result = std::time(nullptr);
//     DynamicJsonDocument request(1024);
//     request["TempInHome"] = grad.getTemperature();
//     request["HumInHome"] = grad.getHumidity();
//     request["Temperature"] = getTemperature();
//     request["Pressure"] = getPressure();
//     request["WeatherDescription"] = rus.getBetterRussianDescription(getWeatherID());
//     request["CURRENTTIMESTAMP"] = std::asctime(std::localtime(&result));
//     return request;
// }

void WIFI::postToOurServer() {
    int port = 80;
    if (!client.connect("meteo-server.herokuapp.com", port)) { //чет не работет, если сюда переменную кинуть
        Serial.println("connection failed");
        return;
    }
    else {
      Serial.println("connection successful");
    }

    Gradusnik grad;
    rus rus;
    std::time_t result = std::time(nullptr);
    String requestStr = "temperatureInHome=" + String(grad.getTemperature())
        + "&humidityInHome=" + String(grad.getHumidity()) 
        + "&temperature=" + String(getTemperature())
        + "&humidity=" + String(getHumidity())
        + "&pressure=" + String(getPressure())
        + "&weatherDescription=" + String(getWeatherDescription() )
        //+ "&CURRENTTIMESTAMP=" + String(std::asctime(std::localtime(&result)))
        ;  
    Serial.println(requestStr + " Размер запроса+'0' " + requestStr.length()+1 );

    client.println("POST /arduinoData HTTP/1.1");
    client.println("Host: meteo-server.herokuapp.com" );
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Content-Length: " + requestStr.length()+1  );
    client.println("Content-Type: application/x-www-form-urlencoded" );
    client.println("Connection: close" );
    client.println();
    client.println();
    client.println(requestStr );
 
    if (client.println() == 0) {
        Serial.println(F("Failed to send request"));
    return;
  }
}

void WIFI::parsingJSON(String json) { //переход на новую версию
    ourJson ourjson;
    DynamicJsonDocument root = ourjson.parseJSON(json);
    setWeatherLocation(root["name"]);
    setCountry(root["sys"]["country"]);
    setTemperature(root["main"]["temp"]);
    setHumidity(root["main"]["humidity"]);
    setPressure(root["main"]["pressure"]);
    setWeatherID(root["weather"]["id"]);
    setWindSpeed(root["wind"]["speed"]);

    setWeatherDescription(root["weather"]["0"]["description"]);
    //setWeatherID(root["weather"]["0"]["id"]); //если погода в городе разная, то станций будет много, и нужно получать хотя бы с одной
    setWeatherID(root["weather"]["id"]);

}

void WIFI::startWifiModule() {
    WiFi.begin(_ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connection isnt successful");
        //led.loadiiing();  //надо как-то кидать исключение на лсд
    }
}

void WIFI::connectToServer(String CityID, String APIKEY) {
    if (client.connect("api.openweathermap.org", 80)) {
        // starts client connection, checks for connection
        client.println("GET /data/2.5/weather?id=" + CityID +
            "&units=metric&APPID=" + APIKEY);
        client.println("Host: api.openweathermap.org");
        client.println("User-Agent: ArduinoWiFi/1.1");
        client.println("Connection: close");
        client.println();
    } else {
        Serial.println("connection failed"); // error message if no client connect
        Serial.println();
    }
}

String WIFI::getResponseFromServer(String result) {
    while (client.connected() && !client.available())
        delay(1); // waits for data
    while (client.connected() || client.available()) {
        // connected or data available
        char c = client.read(); // gets byte from ethernet buffer
        result = result + c;
    }
    client.stop(); // stop client

    return result;
}

float WIFI::toMmRtSt(float GectoPaskal) {
    float res = 0;
    res = GectoPaskal * 100 / 133;
    return res;
}

const char * WIFI::getSSID() {
    return _ssid;
}

String WIFI::getWeatherDescription() {
    return weatherDescription;
}
String WIFI::getWeatherLocation() {
    return weatherLocation;
}
String WIFI::getCountry() {
    return Country;
}
float WIFI::getTemperature() {
    return Temperature;
}
float WIFI::getHumidity() {
    return Humidity;
}
float WIFI::getPressure() {
    return Pressure;
}
int WIFI::getWeatherID() {
    return weatherID;
}
int WIFI::getWindSpeed() {
    return windSpeed;
}

void WIFI::setSSID(const char * ssid) {
    _ssid = ssid;
}

void WIFI::setWeatherDescription(String weatherDescription) {
    this->weatherDescription = weatherDescription;
}
void WIFI::setWeatherLocation(String weatherLocation) {
    this -> weatherLocation = weatherLocation;
}
void WIFI::setCountry(String country) {
    this->Country = country;
}
void WIFI::setTemperature(float temperature) {
    this->Temperature = temperature;
}
void WIFI::setHumidity(float humidity) {
    this->Humidity = humidity;
}
void WIFI::setPressure(float pressure) {
    this->Pressure = pressure;
}
void WIFI::setWeatherID(int weatherId) {
    this->weatherID = weatherId;
}
void WIFI::setWindSpeed(int windSpeed) {
    this->windSpeed = windSpeed;
}