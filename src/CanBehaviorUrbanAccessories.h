<<<<<<< HEAD
#ifndef URBAN_ACCESSORIES_BEHAVIOR_H_
#define URBAN_ACCESSORIES_BEHAVIOR_H_
=======
#pragma once
>>>>>>> master

#include "CanBehavior.h"

class CanBehaviorUrbanAccessories : public CanBehavior {
	public:
		CanBehaviorUrbanAccessories() { }

		void transmit();

<<<<<<< HEAD
		void receive(CanMessage& msg);
	
	protected:
		void _randomizeMessage(CanMessage& message);

		bool _messageContainsId(CanMessage& message, byte id, byte& index);
};

#endif
=======
		void receive(CanMessage& msg) { }
	
	protected:
		void _randomizeMessage(CanMessage& message);
};
>>>>>>> master
