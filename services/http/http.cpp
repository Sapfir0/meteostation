
bool http::postQuery(String host, String path, String requestStr) {

    client.println("POST " + path + "?" + requestStr + " HTTP/1.1");
    client.println("Host: " + host );
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Content-Type: application/x-www-form-urlencoded; charset=utf-8" ); //в урле ты так кириллицу не передаешь, ютф только для тела
    Serial.println("Content-Length: " + String(requestStr.length() + 1)   );
    client.println("Connection: close" );
    client.println();
    client.println( requestStr );

//переопределить оператор << на принтлн //мне лень
    //checkConnection(); //вроде не нужно

    countWritenBytes();
    checkResponse();


    skipHttpHeaders();
    String res="";
    res=getResponseFromServer(res);

    Serial.println("Ответ нам: " + res);
    client.stop(); // стоп происходит в респонсе выше


}

// void http::operator << (String sendValue) {
//     client.println(sendValue);
// }

void http::checkConnection() {
    while (client.connected() && !client.available()) {
        delay(1); // waits for data
        Serial.println("ЧИЛЮ");
    }
    if (client.connected()) {
        Serial.println("я сконекчен");
    }
}

bool http::skipHttpHeaders() {
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
        Serial.println(F("Invalid response"));
        return false;
    }
    
}

String http::deleteSpaceForUrlParams(String param) {
    for(int i=0; i<param.length(); i++) {
        if(isspace(param[i])) {
            Serial.println("Пробел");
            param[i] = '+';
        }
    }
    return param;
}

void http::debugSerial(String host, String path, String requestStr) {
    Serial.println("**********НАЧАЛО ЗАПРОСА*******");
    Serial.println("POST " + path +" HTTP/1.1");
    Serial.println("Host: " + host );
    Serial.println("User-Agent: ArduinoWiFi/1.1");
    Serial.println("Content-Type: application/x-www-form-urlencoded" );
    Serial.println("Content-Length: " + String(requestStr.length() + 1)   ); 
    Serial.println("Connection: close" );
    Serial.println();
    Serial.println(requestStr );
    Serial.println("**********КОНЕЦ ЗАПРОСА*******");

}

bool http::getQuery(String host, String path, String requestStr="\0") {
    if (requestStr != "\0") {
        path+="?";
    }
    
    connectToHost(host);

    client.println("GET " + path + requestStr );
    client.println("Host: " + host);
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    countWritenBytes();

    //client.close();
    //client.stop();
}

bool http::countWritenBytes() {
    if (client.println() == 0) {
        Serial.println(F("Failed to send request"));
        return false;
    }
}

bool http::checkResponse() {
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
        Serial.println(F("Unexpected response: "));
        Serial.println("Status is: ");
        Serial.print(status);
        return false;
    }
}

String http::getResponseFromServer(String result) {
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

bool http::connectToHost(String host) {

    if (!client.connected()) {
        client.connect(host, 80);
        Serial.println("Доп проверка ");
    }
    delay(100);

    
    if (!client.connect(host, 80)) {
        Serial.println("Failed connect with " + host);
        //led.displayError("Failed connect with " + host);
        delay(2000);
        return false;
    }
}


