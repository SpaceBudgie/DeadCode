// UtilitiesTest.cpp

#include <Dead/Test/UnitTest.hpp>
#include <Dead/Events/EventManager.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

// TEST SETUP
struct Controller
{
	bool m_hasReceivedEvent;

public:

	Controller()
	: m_hasReceivedEvent(false)
	{}

	bool receiveEvent()	{
		m_hasReceivedEvent = true;

		return true;
	}

	bool hasReceivedEvent() const {
		return m_hasReceivedEvent;
	}
};


// Event Data
struct IEvent;

// Enum Events
enum EnumEvents
{
	GAME_START_MSG,
	PLAYER_DEAD_MSG,
	GAME_END_MSG,
};


struct GameStartEventData;
struct GameEndEventData;


// ** TEST USING ENUMS AS KEY ** //
//typedef EnumEvents Events;
//typedef Dead::SimpleEventManager<Controller, Events, IEvent*> EventManager;
//typedef GameEndEventData* 	GameEndEventDataPtr;
//typedef GameStartEventData* GameStartEventDataPtr;
//EnumEvents g_events[] = { GAME_START_MSG, PLAYER_DEAD_MSG, GAME_END_MSG, };



// ** TEST USING STD::STRING AS KEY ** //
//typedef std::string Events;
//typedef Dead::SimpleEventManager<Controller, std::string, IEvent> EventManager;	// Using string keys
//typedef GameEndEventData* 	GameEndEventDataPtr;
//typedef GameStartEventData* GameStartEventDataPtr;
//std::string g_events[] = { "GameStart", "PlayerDead", "GameEnd" };

// ** TEST USING ENUMS AS KEY, AND MANUAL DELETE POLICIY ** //
//typedef EnumEvents Events;
//typedef Dead::SimpleEventManager<Controller, Events, IEvent, Dead::SimpleStackNoDelete<Events, IEvent> > EventManager;	// Using no delete.
//typedef GameEndEventData* 	GameEndEventDataPtr;
//typedef GameStartEventData* GameStartEventDataPtr;
//EnumEvents g_events[] = { GAME_START_MSG, PLAYER_DEAD_MSG, GAME_END_MSG, };

// ** TEST USING FAST MEM POOL POLICY ** //
//typedef Dead::SimpleEventManager<Controller, std::string, IEvent, FastPool> EventManager;	// Using fast pool.

// ** TEST USING BOOST::SHARED_PTR ** //
// Using Smart Ptrs
typedef EnumEvents Events;
typedef boost::shared_ptr<IEvent> EventType;
typedef EventType 	GameEndEventDataPtr;
typedef EventType	GameStartEventDataPtr;
typedef Dead::SimpleEventManager<Controller, Events, EventType, Dead::SimpleStackNoDelete<Events, EventType> > EventManager;
EnumEvents g_events[] = { GAME_START_MSG, PLAYER_DEAD_MSG, GAME_END_MSG, };


struct IEvent
{
	virtual Events getID() = 0;
};


// Event ids
struct GameStartEventData : public IEvent {
	Events getID() { return g_events[GAME_START_MSG]; }
};

struct GameEndEventData : public IEvent {
	Events getID() { return g_events[GAME_END_MSG]; }
};




// Globals for Testing //

EventManager 	g_eventManger;

Controller* g_listener1 = new Controller();
Controller* g_listener2 = new Controller();




// TESTS


// Adding two listeners.
TEST(AddListener)
{ 
	bool shouldBeTrue  = g_eventManger.addController(g_listener1, g_events[GAME_START_MSG]);
	bool shouldBeFalse = g_eventManger.addController(g_listener1, g_events[GAME_START_MSG]);

	ASSERT_IS_TRUE(shouldBeTrue)
	ASSERT_IS_FALSE(shouldBeFalse)


	shouldBeTrue  = g_eventManger.addController(g_listener2, g_events[GAME_END_MSG]);
	shouldBeFalse = g_eventManger.addController(g_listener2, g_events[GAME_END_MSG]);

	ASSERT_IS_TRUE(shouldBeTrue)
	ASSERT_IS_FALSE(shouldBeFalse)
}



// Sending an instant event.
TEST(SendInstantMsg)
{
	ASSERT_IS_FALSE(g_listener1->hasReceivedEvent())

	GameStartEventDataPtr data(new GameStartEventData());
	g_eventManger.fireInstantEvent(data, data->getID());

	ASSERT_IS_TRUE(g_listener1->hasReceivedEvent())
}



// Testing to see if message has been swollowed.
TEST(InstantMsgSwollow)
{
	GameStartEventDataPtr data(new GameStartEventData());
	g_eventManger.fireInstantEvent(data, data->getID());

	ASSERT_IS_FALSE(g_listener2->hasReceivedEvent())
}



// Test to see if queuing works ok.
TEST(QueueAndSendQueuedMsg)
{
	ASSERT_IS_EQUAL(0, g_eventManger.sizeOfQueue())

	GameEndEventDataPtr data1(new GameEndEventData());
	GameEndEventDataPtr data2(new GameEndEventData());

	g_eventManger.addQueuedEvent(data1, data1->getID());
	g_eventManger.addQueuedEvent(data2, data2->getID());

	ASSERT_IS_EQUAL(2, g_eventManger.sizeOfQueue())

	g_eventManger.fireQueuedEvents();

	ASSERT_IS_TRUE(g_listener2->hasReceivedEvent())
	ASSERT_IS_EQUAL(0, g_eventManger.sizeOfQueue())
}


// Test to remove listeners
TEST(RemoveListner)
{
	// Make sure that listener is in all events.
	g_eventManger.addController(g_listener1, g_events[GAME_START_MSG]);
	g_eventManger.addController(g_listener1, g_events[PLAYER_DEAD_MSG]);
	g_eventManger.addController(g_listener1, g_events[GAME_END_MSG]);

	// Check single removed.
	bool removed;
	removed = g_eventManger.removeControllerFromEvent(g_listener1, g_events[GAME_START_MSG]);

	ASSERT_IS_TRUE(removed);

	// Check multi removed.
	g_eventManger.removeControllerFromAllEvents(g_listener1);


	// These should all be true because they all got removed.

	// ** DO ME ** //
}



int main()
{
	Dead::RunTests();

	return 0;
}