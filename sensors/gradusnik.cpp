Gradusnik::Gradusnik() {

}

void Gradusnik::start() {
    dht.begin();
}

float Gradusnik::getTemperature() {
    temperature = dht.readTemperature();
    return temperature;
}
float Gradusnik::getHumidity() {
    humidity = dht.readHumidity();
    return humidity;
}

float Gradusnik::getIluminating() { //��� ������������� ������������ 0
    illumination = analogRead(photoresistor); //��� ����������� 1024
    //Serial.println(illumination); // очень трудно его сдвинуть с 1024 // нужно купить спец датчик
    return illumination;
}

int Gradusnik::analyzeEnivromentQuality() {

}

void Gradusnik::changeBrightning() {
    int brightn; //так, это вроде адаптивная яркость, но она работала и без фоторезистора
    // вот это крипота
    brightn = getIluminating() / 4; 
    //при минимальной 1024
    //возвращаемое значение с порта - 1024 - приводим к 256
    analogWrite(D6, brightn);
}