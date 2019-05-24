#include <Arduino.h>

class parallel
{
  public:
	parallel(uint32_t interval);				
	void setInterval(uint32_t interval);	
	boolean isReady();						
	void reset();							
	void stop();							
	void start();							
	
  private:
	uint32_t timer = 0;
	uint32_t interval = 0;
	boolean _state = true;
};


parallel::parallel(uint32_t interval) {
	this->interval = interval;
	this->timer = millis();
}

void parallel::setInterval(uint32_t interval) {
	this->interval = interval;
	parallel::reset();
}

void parallel::start() {
	_state = true;
}
void parallel::stop() {
	_state = false;
}
boolean parallel::isReady() {
	if (!_state) 
        return false;

	if ((long)millis() - this->timer >= this->interval) {
		return true;
	} else {
		return false;
	}
}

void parallel::reset() {
	this->timer = millis();
}

