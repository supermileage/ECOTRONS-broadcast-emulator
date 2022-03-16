#pragma once

#include "Arduino.h"
#include "Sim.h"

// Simulator for Fuel-Cell Controller
class SimFc : public Sim {

    public:

        /**
         * CONSTRUCTOR
         * 
         * @param updateInterval is the interval at which to update sensor values (ms)
         * */
        SimFc(uint32_t updateInterval) : Sim(updateInterval) {}

        void begin() override;

        void handle() override;

};
