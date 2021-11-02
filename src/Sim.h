#include "Arduino.h"

#ifndef _SIM_H_
#define _SIM_H_

class Sim {
    public:

        /**
         * INTERFACE
         * Initialize simulator
         * */
        virtual void begin() = 0;

        /**
         * INTERFACE
         * Simulator update handler, run as frequently as possible
         * */
        virtual void handle() = 0;

        /**
         * INTERFACE
         * @return Human name for this simulator type
         * */
        virtual String getHumanName() = 0;

    private:

};

#endif