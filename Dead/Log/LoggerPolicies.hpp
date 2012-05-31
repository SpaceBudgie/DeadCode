// Copyright DeadEnd Games.


/*!
 *	History
 *  March 2012, Phil CK added/created file
 */


/*!
*	About
 *	These are some default loggin policies for the logger.
 *	You may use these ones or create a specific one for you needs.
 */


#ifndef DEAD_LOG_LOGGER_POLICIES_INCLUDED
#define DEAD_LOG_LOGGER_POLICIES_INCLUDED

#include <fstream>
#include <iostream>


namespace Dead {



// *** CONSOLE OUTPUT POLICY **** //

//! Outputs contents to the console.
class ConsoleOutput
{
public:

	~ConsoleOutput() {
		out("\n");
	}

	template<typename T>
	void out(T const & output) {
		std::cout << output;
	}
}; // class ConsoleOutput



// *** FILE OUTPUT POLICY **** //

//! Outputs contents to a file.
class FileOutput
{

	std::ofstream logFile;

public:

	FileOutput() {
	  	logFile.open ("LoggerOutput.txt");
	}

	~FileOutput() {
		out("\n");
		logFile.close();
	}

	template<typename T>
	void out(T const & output)
	{
		logFile << output;
	}

}; // class FileOutput



// *** NO OUTPUT POLICY **** //

//! No output
class NoOutput
{
public:

	void out() {}
}; // class NoOutput



} // namespace Dead

#endif // #ifndef DEAD_LOGGER_POLICIES_INCLUDED
