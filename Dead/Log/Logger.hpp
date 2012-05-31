// Copyright DeadEnd Games.

/*!
 *	History
 *  March 2012, Phil CK added/created file
 */


/*!
 * 	About
 *	A generic logger.
 *	There are some default policies in /Dead/Log/LoggerPolicies.hpp
 *	This class allows you to output to files, console or anything else you require.
 */


#ifndef DEAD_LOG_LOGGER_INCLUDED
#define DEAD_LOG_LOGGER_INCLUDED


namespace Dead {


template<typename OutputPolicy>
class Logger : public OutputPolicy
{

	using OutputPolicy::out;

public:

	template<class T>
    Logger & operator<<(T const & log)
    {
        out(log);
        return *this;
    }

    template<class T>
    Logger log(T const & log)
    {
    	out(log);
    	return *this;
    }

}; // class Logger


} // namespace Dead


#endif // #ifndef DEAD_LOGGER_INCLUDED