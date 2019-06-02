#include "../../sensors/gradusnik.hpp"
#include "../translating/rus.hpp"
#include "../json/jsonParse.hpp"
#include "../http/http.hpp"

WIFI::WIFI() {
    weatherDescription="unknown";
}

void WIFI::getWeatherData()  { // client function to send/receive GET request data.
    http req;
    connectToServer(CityID, APIKEY);
    result = req.getResponseFromServer(result);
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
    if (!client.connect(ourServer, port)) { //чет не работет, если сюда переменную кинуть
        Serial.println("connection failed");
        return;
    }
    else {
      Serial.println("connection successful");
    }


    Gradusnik grad;
    rus rus;
    //Serial.println("Описание погоды " + rus.getRussianDescription(getWeatherID()) );

    //std::time_t result = std::time(nullptr);
    String requestStr = "temperatureInHome=" + String(grad.getTemperature())
        + "&humidityInHome=" + String(grad.getHumidity()) 
        + "&temperature=" + String(getTemperature())
        + "&humidity=" + String(getHumidity())
        + "&pressure=" + String(toMmRtSt(getPressure()))
        + "&weatherDescription=" + getWeatherDescription()
        //+ "&CURRENTTIMESTAMP=" + String(std::asctime(std::localtime(&result)))
        ;  

    //Serial.println(requestStr);
    http req;
    req.postQuery(ourServer, "/arduinoData/", requestStr);

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
    String requestStr = "id=" + CityID +"&units=metric&APPID=" + APIKEY;
    http req;
    req.getQuery("api.openweathermap.org", "/data/2.5/weather", requestStr);
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