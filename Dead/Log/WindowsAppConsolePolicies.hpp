// *** WINDOWS CONSOLE OUTPUT POLICY **** //
// References : http://www.gamedev.net/topic/509479-routing-stdout-to-windowconsole/

//! Outputs contents to the console.
class WindowsAppConsoleOutput
{
public:

	WindowsAppConsoleOutput()
	{
		// Create a console for this application
		AllocConsole();

		// Redirect unbuffered STDOUT to the console
		HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
		FILE *COutputHandle = _fdopen(SystemOutput, "w" );
		*stdout = *COutputHandle;
		setvbuf(stdout, 0, _IONBF, 0);

		// Redirect unbuffered STDERR to the console
		HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
		int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
		FILE *CErrorHandle = _fdopen(SystemError, "w" );
		*stderr = *CErrorHandle;
		setvbuf(stderr, 0, _IONBF, 0);

		// Redirect unbuffered STDIN to the console
		HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
		FILE *CInputHandle = _fdopen(SystemInput, "r" );
		*stdin = *CInputHandle;
		setvbuf(stdin, 0, _IONBF, 0);
    
		// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
		std::ios::sync_with_stdio(true);
	}


	~WindowsAppConsoleOutput()
	{
		std::cout << std::endl << "Press any key to exit" << std::endl;

		// Disable line-based input mode so we can get a single character
		HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		SetConsoleMode(ConsoleInput, 0);

		// Read a single character
		TCHAR InputBuffer;
		DWORD CharsRead;
		ReadConsole(ConsoleInput, &InputBuffer, 1, &CharsRead, 0);
	}


	void out() {
		std::cout << "Console" << std::endl;
	}
}; // class WindowsAppConsoleOutput