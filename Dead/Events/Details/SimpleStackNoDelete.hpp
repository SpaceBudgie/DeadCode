// Copyright DeadEnd Games.
// License: MIT 

// PhilCK 2012

// Policy for SimpleEventManager.
// This will not delete any events, but it will clear them off the stack.
// This reqiures that deletion is handled in another manor.


#ifndef DEAD_SIMPLE_STACK_NO_DELETE_POLICY
#define DEAD_SIMPLE_STACK_NO_DELETE_POLICY

#include <Dead/Events/Details/SimpleStack.hpp>

namespace Dead {


template<typename EventID, typename Event>
struct SimpleStackNoDelete : public SimpleStack<EventID, Event>
{
	typedef SimpleStack<EventID, Event> Base;

	// Redefine popEvent() so we ignore the deletion.
	bool popEvent()
	{
		if(!Base::empty())
		{
			typename Base::StackEvent &stackEvent = Base::m_stack.top();

			Base::m_stack.pop();
			return true;
		}


		// if it was already empty.
		return false;
	}

}; // struct
}  // namespace

#endif // include guard