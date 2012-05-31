// Copyright DeadEnd Games.
// License: MIT 

/*!
 *	History
 *  April 2012, Phil CK added/created file
 */


/*!
 * 	About
 *	Unit testing.
 */


/*!
 * 	Issues
 *	- Issue with ASSERT_IS_NEAR() with floats. ie (1.0, 1.2, 0.2) doesn't
 *	  pass as true, when it should.
 *	- TestLogging is werid, would prefer this a template member of the UnitTest class.
 *	- Should make it a fully singleton hide asignment etc.
 *	- Add Greater and Less then checks.
 */


#ifndef DEAD_UNIT_TEST_INCLUDED
#define DEAD_UNIT_TEST_INCLUDED


#include <list>
#include <string>
#include <math.h>
#include <Dead/Log/Logger.hpp>
#include <Dead/Log/LoggerPolicies.hpp>


namespace Dead {


/*!
 *	Interface class for the tests.
 */
struct ITest
{
	virtual std::string getName() const = 0;
	virtual void run() const = 0;
}; // end of struct


//! Outputting test information.
typedef Logger<ConsoleOutput>	TestLogging;


/*!
 *	Unit tests, this is a singleton class, access through instance();
 */
class UnitTest
{
	typedef std::list<ITest*> 	TestList;
	typedef TestList::iterator	TestListIt;

	//! Holds all the tests.
	TestList 	m_tests;

	//! Some stats on how things have done.
	unsigned int m_passed, m_failed;

	//! Private ctor.
	explicit UnitTest()
		: m_passed(0)
		, m_failed(0)
		, m_tests()
	{}

public:

	//! Singlton access.
	static UnitTest& instance()
	{
		static UnitTest test;
		return test;
	}


	//! This adds a test to the list.
	void addTest(ITest * newTest) {
		m_tests.push_back(newTest);	
	}


	//! Runs all the tests.
	void runTests()
	{
		// Title screen.
		TestLogging() << "\n" << "Running Unit Tests";
		TestLogging() << "==================";


		// Run the individual tests.
		TestListIt testIt = m_tests.begin();

		for(testIt; testIt != m_tests.end(); ++testIt)
		{
			unsigned int fails(m_failed);

			TestLogging() << "\n" << (*testIt)->getName();
			(*testIt)->run();

			if(fails == m_failed) {
				TestLogging() << "All test(s) passed!";
			} else {
				TestLogging() << (m_failed - fails) << " Test(s) failed!";
			}
		}


		// End screen.
		TestLogging() << "\n" << "Results" << "\n" << "-------";
		TestLogging() << "Tests Passed: " << m_passed;
		TestLogging() << "Tests Failed: " << m_failed;
	}



	//! Increase the passed tests.
	void passedCurrentTest() { m_passed++; }
	//! Increase the failed tests.
	void failedCurrentTest() { m_failed++; }


}; // end of class


// Run the tests
void RunTests()
{
	Dead::UnitTest::instance().runTests();
}


} // end of namespace


//! Creates a test case.
#define TEST(ClassName)								\
struct Test##ClassName : public Dead::ITest			\
{													\
	std::string name; 								\
	Test##ClassName()								\
	: name(#ClassName)								\
	{												\
		Dead::UnitTest::instance().addTest(this);	\
	}												\
													\
	std::string getName() const { return name; }	\
													\
	void run() const;								\
} instanceTest##ClassName;							\
													\
void Test##ClassName::run() const					\



//! Check to see if two values are equal.
#define ASSERT_IS_EQUAL(a, b)																		\
if(a == b) {																						\
	Dead::UnitTest::instance().passedCurrentTest();													\
} else {																							\
	Dead::UnitTest::instance().failedCurrentTest();													\
	Dead::TestLogging() << "Failed! ASSERT_IS_EQUAL, with values: " << a << " and " << b << "."; 	\
}																									\


//! Check to see if two vales are not equal.
#define ASSERT_IS_NOT_EQUAL(a, b)																		\
if(a != b) {																							\
	Dead::UnitTest::instance().passedCurrentTest();														\
} else {																								\
	Dead::UnitTest::instance().failedCurrentTest();														\
	Dead::TestLogging() << "Failed! ASSERT_IS_NOT_EQUAL, with values: " << a << " and " << b << "."; 	\
}																										\


//! Check if two values are inside the error margin.
#define ASSERT_IS_NEAR(a, b, error)																						\
if((fabs(a - b)) <= error) {																							\
	Dead::UnitTest::instance().passedCurrentTest();																		\
} else {																												\
	Dead::UnitTest::instance().failedCurrentTest();																		\
	Dead::TestLogging() << "Failed! ASSERT_IS_NEAR, with values: " << a << ", " << b << " and error " << error << "."; 	\
}																														\


//! Check to see if two values are outside the error margin.
#define ASSERT_IS_NOT_NEAR(a, b, error)																						\
if((fabs(a - b)) > error) {																									\
	Dead::UnitTest::instance().passedCurrentTest();																			\
} else {																													\
	Dead::UnitTest::instance().failedCurrentTest();																			\
	Dead::TestLogging() << "Failed! ASSERT_IS_NOT_NEAR, with values: " << a << ", " << b << " and error " << error << "."; 	\
}																															\


//! Check to see if its true.
#define ASSERT_IS_TRUE(a)														\
if(a) {																			\
	Dead::UnitTest::instance().passedCurrentTest();								\
} else {																		\
	Dead::UnitTest::instance().failedCurrentTest();								\
	Dead::TestLogging() << "Failed! ASSERT_IS_TRUE, with values: " << a;		\
}																				\


//! Check to see its false.
#define ASSERT_IS_FALSE(a)														\
if(!a) {																		\
	Dead::UnitTest::instance().passedCurrentTest();								\
} else {																		\
	Dead::UnitTest::instance().failedCurrentTest();								\
	Dead::TestLogging() << "Failed! ASSERT_IS_FALSE, with values: " << a;		\
}																				\



#define ASSERT_IS_GREATER(a, b)																\
if(a > b) {																					\
	Dead::UnitTest::instance().passedCurrentTest();											\
} else {																					\
	Dead::UnitTest::instance().failedCurrentTest();											\
	Dead::TestLogging() << "Failed! ASSERT_IS_GREATER, with values: " << a << ", " << b;	\
}																							\


#define ASSERT_IS_LESS(a, b)																\
if(a < b) {																					\
	Dead::UnitTest::instance().passedCurrentTest();											\
} else {																					\
	Dead::UnitTest::instance().failedCurrentTest();											\
	Dead::TestLogging() << "Failed! ASSERT_IS_LESS, with values: " << a << ", " << b;	\
}																							\

#endif // end of include guard