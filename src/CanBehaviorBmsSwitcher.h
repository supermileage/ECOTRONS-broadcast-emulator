#ifndef _CAN_BEHAVIOR_BMS_SWITCHER_H_
#define _CAN_BEHAVIOR_BMS_SWITCHER_H_

#include "CanBehavior.h"

class CanBehaviorBmsSwitcher : public CanBehavior {
    public:
        CanBehaviorBmsSwitcher(CanBehavior* orion, CanBehavior* tiny);
		~CanBehaviorBmsSwitcher();
		void transmit() override;
		void receive(CanMessage& msg) override;
        void setSender(Delegate* sender) override;

    private:
        CanBehavior* _orion;
        CanBehavior* _tiny;
        CanBehavior* _current;
        uint64_t _lastSwitchMillis = 0;

        void _switchBms();
};

#endif