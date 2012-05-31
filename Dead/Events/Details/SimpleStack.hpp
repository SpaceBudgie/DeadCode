
// Copyright DeadEnd Games.
// License: MIT 

// PhilCK 2012

// Policy for SimpleEventManager.
// This will delete events in the queue, when they all get sent.


#ifndef DEAD_EVENTS_SIMPLE_STACK
#define DEAD_EVENTS_SIMPLE_STACK

#include <stack>

namespace Dead {

template<typename EventID, typename EventPtr>
struct SimpleStack
{
	struct StackEvent { EventID id; EventPtr event; };
	//struct StackEvent { EventID id; Event *event; };

	typedef typename std::stack<StackEvent> EventStack;

	EventStack m_stack;

	explicit SimpleStack()
		: m_stack()
	{}


	//void addToQueue(Event *data, EventID const &id)
	void addToQueue(EventPtr data, EventID const &id)
	{
		StackEvent event = {id, data};

		m_stack.push(event);
	}

	//Event* getNextEvent() {
	EventPtr getNextEvent() {
		return m_stack.top().event;
	}

	EventID getNextEventID() {
		return m_stack.top().id;
	}

	bool popEvent()
	{
		if(!empty())
		{
			StackEvent	&stackEvent = m_stack.top();
			delete stackEvent.event;

			m_stack.pop();
			return true;
		}

		// if it was already empty.
		return false;
	}

	std::size_t size()  const { return m_stack.size();  }
	bool 		empty() const { return m_stack.empty(); }

}; // struct

}  // namespace

#endif // include guard