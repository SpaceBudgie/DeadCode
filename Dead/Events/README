#Event Manager

DeadCodes currently provides one simple event manager. This provides a mechanism to send and receive events in your game.

###Files
EventManager.hpp - access to SimpleEventManager.hpp and all its policies.
SimpleEventManger.hpp - access only to the event manager.

##Simple Event Manager

The event manager's pre-requisits are an `event handeling` class (referred to as the controller), The `id type` you wish to use, and a pointer to the `base Event` class.


###Basic Setup


``` cpp
// Include DeadCode's SimpleEventManager
#include <Dead/Events/EventManager.hpp>

// We will use int's as our id type.

// Base event struct
struct EventBase
{};

// Controller / Event Handler struct (This could be your base GameObject).
struct Controller
{
	bool receiveEvent(int id, EventBase* data)	
};

SimpleEventManger<Controller, int, EventBase*> eventMgr;

```

###Basic Usage

``` cpp
// For a controller to subscribe to an event.


// To send an message.


// To queue a message for the next frame.


// To unsubscribe from that event.

```

###Key Types

The only resitction on what type of key you can use is that it must support the `== operator`. So good choices would be `unsigned ints`, `enums`, or even `std::string`(although this may result in some poor performance, depending on your STL lib etc.)


###Manual Deletion of objects

By default the Manager will delete objects in the queue after its finished with them. If you want to delete objects manually because this would interfere with your framework, You can use the `SimpleStackNoDelete` policy like so...

`
SimpleEventManger<Controller, int, EventBase*, SimpleStackNoDelete<int, EventBase*> > eventMgr;
`


###Using a Memory Pool

Not currently supported with-in the EventManager. 


###Using Smart Pointers

You are able to use smart pointers in the EventManger just remember to turn off deletions.

`
SimpleEventManager<Controller, int, boost::shared_ptr<EventBase>, SimpleStackNoDelete<int, boost::shared_ptr<EventBase> > eventManager;
`

Yikes! Abit long winded.


###Problems
- The Controller *must* have a method defined recivedEvent(), I'd like this to be a bit more flexible in future.
- No support for memory pools.
- No support for boost::pool or custom pool.
- Not checked C++11's shared pointer.
- Not tested what happens if you remove a controller while looping through events yet.
- Controller mechanism can lead to cyclic code easily (is that just me? or is this a problem?)