#ifndef _SIM_H_
#define _SIM_H_

#include "Arduino.h"

class Sim {
    public:

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

    private:

};

#endif