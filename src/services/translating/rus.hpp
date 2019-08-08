#ifndef RUS_H
#define RUS_H

#include <Arduino.h>

class rus
{
private:
    /* data */
public:
      String getRussianDescription(int weatherID);
      String getBetterRussianDescription(int weatherID);

};

#endif // RUS_H