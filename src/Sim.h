#pragma once

#include "Arduino.h"

// Simulator Abstract class
class Sim {
    public:

        /**
         * CONSTRUCTOR
         * 
         * @param updateInterval is the interval at which to update sensor values (ms)
         * */
        Sim(uint32_t updateInterval) : _updateInterval(updateInterval) {}

        /**
         * ABSTRACT
         * Initialize simulator
         * */
        virtual void begin() = 0;

        /**
         * ABSTRACT
         * Simulator update handler, run as frequently as possible
         * */
        virtual void handle() = 0;

    protected:
        uint32_t _updateInterval;
        uint32_t _lastUpdate = 0;

};
