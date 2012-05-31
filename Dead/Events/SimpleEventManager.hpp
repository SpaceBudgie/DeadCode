// Copyright DeadEnd Games.
// License: MIT 

/*!
 *	History
 *  April 2012, Phil CK added/created file
 */


/*!
 * 	About
 *	Sending and receiving events.
 *	This is a very simplistic event system, there are many possibilites for improvments.
 *	This is also very template heavy, but again designed more for quick easy portablitiy.
 */


/*!
 *	Useage
 *	There is a little setup required to use SimpleEventManager
 *	You need a listener class (This could be the base game object class or dedicated reciever class).
 *	You need a base event class (in a push you could use void*).
 *	You need a system of id's for your events, enum's are a good choice for small scale projects.
 *	
 *	Then with all this informations
 *	SimpleEventManager<Listener, EventID, EventBase>
 *
 *	There is an optional template paramater
 *	SimpleEventManager<Listener, EventID, EventBase, FastMemPool>
 *
 *	This gives you a access to a policy that can deal with memory management for
 *	your events. If you have alot of events this is recomended.
 *
 */


/*!
 * 	Issues
 *	- If you remove your self from a list while updating you might have some problems.
 *	- Currently events are stored in a map, they need to be stored in a memory pool instead.
 *	- Want to make sure it works well with smart pointers.
 */



#ifndef DEAD_SIMPLE_EVENT_MANAGER_INCLUDED
#define DEAD_SIMPLE_EVENT_MANAGER_INCLUDED

#include <list>
#include <map>
#include <Dead/Events/Details/SimpleStack.hpp>

namespace Dead {

template<typename Controller,
		 typename EventID,
		 typename EventPtr,
		 typename EventQueue = SimpleStack<EventID, EventPtr> >
class SimpleEventManager : public EventQueue
{
	typedef typename std::list<Controller* > 				ControllerList;
	typedef typename ControllerList::iterator				ControllerListIt;

	typedef typename std::map<EventID, ControllerList>		EventControllerMap;
	typedef typename std::pair<EventID, ControllerList>		EventControllerPair;
	typedef typename EventControllerMap::iterator			EventControllerIt;


	EventControllerMap 	m_controllers;

	using EventQueue::addToQueue;
	using EventQueue::getNextEvent;
	using EventQueue::getNextEventID;
	using EventQueue::popEvent;
	using EventQueue::size;
	using EventQueue::empty;

public:


	explicit SimpleEventManager()
		: m_controllers()
	{}

	~SimpleEventManager() {
		m_controllers.clear();
	}


	//! Add an event Controller (receiver/handler what ever you want to call it)
	bool addController(Controller * controller, EventID const & id)
	{
		// Find the event in the map
		EventControllerIt controllerIt = m_controllers.find(id);

		// If it exists try and add the controller to the list.
		if(controllerIt != m_controllers.end())
		{
			ControllerList& list = controllerIt->second;

			// Check to see if the controller is allready in the list.
			ControllerListIt listIt = list.begin();

			for(listIt; listIt != list.end(); ++listIt)
			{
				if((*listIt) == controller) {
					return false;
				}
			}

			// Add the controller to the list.
			list.push_back(controller);
		}

		// If it doesn't exist we'll add it to the list.
		else
		{
			ControllerList list;
			list.push_back(controller);

			m_controllers.insert(EventControllerPair(id, list));
		}

		return true;

	} // end of addConstroller(...)


	//! Remove a controller from an event.
	bool removeControllerFromEvent(Controller const * controller, EventID const & id)
	{
		EventControllerIt mapIt = m_controllers.find(id);

		if(mapIt != m_controllers.end())
		{
			ControllerList &list = mapIt->second;

			// Search list for the controller.
			ControllerListIt listIt = list.begin();

			for(; listIt != list.end(); ++listIt)
			{
				// Remove controller.
				if(*listIt == controller)
				{
					listIt = list.erase(listIt);
					
					// Success
					return true;
				}
			}
		}

		// Failed
		return false;
	}


	//! Remove a controller from all events
	//! (This is a convenice method, might be slow if a large number of events).
	void removeControllerFromAllEvents(Controller const *controller)
	{
		EventControllerIt mapIt = m_controllers.begin();
		
		for(; mapIt != m_controllers.end(); ++mapIt)
		{
			removeControllerFromEvent(controller, mapIt->first);
		}
	}


	//! Add an event to the queue. The queue will be processed later,
	//! usuall the next frame.
	//void addQueuedEvent(Event *data, EventID const &id)
	void addQueuedEvent(EventPtr data, EventID const &id)
	{
		EventQueue::addToQueue(data, id);
	}


	//! Fire all the queued events off.
	void fireQueuedEvents()
	{
		while(!EventQueue::empty())
		{
			sendEvent(EventQueue::getNextEvent(), EventQueue::getNextEventID());
			popEvent();
		}
	}


	//! How big the queue is.
	std::size_t sizeOfQueue() const { return EventQueue::size(); }


	//! Send an instant event, this is the fastest way to send an event.
	//! However you might might cause framerate problems. If an instant event
	//! triggers a large number of other instant events.
	//void fireInstantEvent(Event const * data, EventID const & id)	{
	void fireInstantEvent(const EventPtr data, EventID const & id)	{
		sendEvent(data, id);
	}


private:

	//! This actually sends the event. The process is the the same for
	//! Queued and Instant events.
	//void sendEvent(Event const * data, EventID const & id)
	void sendEvent(const EventPtr data, EventID const & id)
	{
		EventControllerIt eventControlerIt = m_controllers.find(id);

		if(eventControlerIt != m_controllers.end())
		{
			ControllerList& list = eventControlerIt->second;

			ControllerListIt listIt = list.begin();

			for(listIt; listIt != list.end(); ++listIt)
			{
				bool swallow = (*listIt)->receiveEvent();

				// Break if the message has been swallowed.
				if(swallow) {
					break;
				}
			}
		}
	} // end of sendEvent(...)


}; // class
}  // namespace

#endif // include guard