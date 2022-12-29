#include "CanBehaviorBmsSwitcher.h"

#define SWITCH_INTERVAL 5000

CanBehaviorBmsSwitcher::CanBehaviorBmsSwitcher(CanBehavior* orion, CanBehavior* tiny) :
    _orion(orion), _tiny(tiny), _current(orion) { }

CanBehaviorBmsSwitcher::~CanBehaviorBmsSwitcher() { }

void CanBehaviorBmsSwitcher::transmit() {
    if (millis() > _lastSwitchMillis + SWITCH_INTERVAL) {
        _lastSwitchMillis = millis();
        _switchBms();
    }

    _current->transmit();
}

void CanBehaviorBmsSwitcher::receive(CanMessage& msg) {
    _current->receive(msg);
}

void CanBehaviorBmsSwitcher::setSender(Delegate* sender) {
    _orion->setSender(sender);
    _tiny->setSender(sender);
}

void CanBehaviorBmsSwitcher::_switchBms() {
    Serial.println("Switching Bms");

    if (_current == _orion) {
        _current = _tiny;
    } else {
        _current = _orion;
    }
}
