#ifndef _SIM_FC_H_
#define _SIM_FC_H_

#include "Arduino.h"
#include "Sim.h"

#define FC_BAUD_RATE        9600
#define FC_STOP_CHARACTER   '*'

class SimFc : public Sim {
    public:
        /**
         * Constructor 
         * 
         * @param serial port for outputting ECU data
         **/
        SimFc(Stream *serial);

        void begin();

        void handle();

        String getHumanName();

    private:
        Stream *_serial;
        unsigned long _lastTransmit = 0;

};

#endif
