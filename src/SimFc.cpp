#include "SimFc.h"

#define FC_INTERVAL 1000
SimFc::SimFc(Stream *serial) {
    _serial = serial;
}

void SimFc::begin(){ }

void SimFc::handle(){
    if(millis() >= _lastTransmit + FC_INTERVAL) {
        _serial->println("This is a test message");
        _serial->print("Send at time ");
        _serial->println(millis());
        _serial->print("From the FC Simulator!*");
        _lastTransmit = millis();
    }
}

String SimFc::getHumanName() {
    return "FC";
}
