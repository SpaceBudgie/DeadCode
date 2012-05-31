// Copyright DeadEnd Games.
// License: MIT

/*!
 *	History
 *  March 2012, Phil CK added/created file
 */


/*!
 * 	About
 *	This is a generic lazy include for logging.
 *	Use Log (or ConsoleLog) for logging purposes.
 */


#ifndef DEAD_LOG_INCLUDED
#define DEAD_LOG_INCLUDED

#include <Dead/Config/Platform.hpp>
#include <Dead/Log/Logger.hpp>
#include <Dead/Log/LoggerPolicies.hpp>

#if defined(DEAD_ON_WINDOWS)
#include <Dead/Log/WindowsAppConsolePolicies.hpp>
#endif


namespace Dead {


typedef Logger<ConsoleOutput> 	ConsoleLog;
typedef Logger<FileOutput> 		FileLog;
typedef Logger<ConsoleOutput> 	Log;


} // namespace Dead


#endif // #ifndef DEAD_LOG_INCLUDED