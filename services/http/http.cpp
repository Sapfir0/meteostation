//надо сделать так, чтобы последний аргумент был необязательным, но
// если он задается, то к пути в конце добавляется вопрос
//в wifi.cpp вопрос убрать

bool http::postQuery(String host, String path, String requestStr="\0") {
    if (requestStr != "\0") {
        path+="?";
    }
    else {
        Serial.println("Warning: in post query should be query");
    }

    if (!client.connect(host, 80)) {
        Serial.println("Failed connect with " + host);
        return false;
    }

    client.println("POST " + path +" HTTP/1.1");
    client.println("Host: " + host );
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Content-Length: " + requestStr.length()+1  );
    client.println("Content-Type: application/x-www-form-urlencoded" );
    client.println("Connection: keep-alive" );
    client.println();
    client.println(requestStr );

    countWritenBytes();
    checkResponse();
}


bool http::getQuery(String host, String path, String requestStr="\0") {
    if (requestStr != "\0") {
        path+="?";
    }
    
    if (!client.connect(host, 80)) {
        Serial.println("Failed connect with " + host);
        return false;
    }
    client.println("GET " + path + requestStr );
    client.println("Host: " + host);
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    countWritenBytes();

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
        Serial.print(F("Unexpected response: "));
        Serial.println(status);
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