#ifndef debugtools_h_defined
#define debugtools_h_defined
#define DEBUG_PRIORITY 5

#define STD_ERROR_PRIORITY 1
#define STD_WARN_PRIORITY 2
#define STD_INFO_PRIORITY 3

#include <fstream>
#include <iostream>
#include <string>

class DebugTools
{
	public:
		// Enumerator for the message type.
		enum LogType
		{
			Info,
			Warn,
			Error
		};

		/* Log a message to the console:
			char* text : The message to be displayed (exclude WARNING, ERROR and INFO prefix).
			LogType type : The type of message to be displayed, determines the prefix.
			int indent : The number of indents to be prefixed to the message. (default:0)*/
		static void Log(std::string text, LogType type, int indent = 0);

		/* Output a section break to the console. */
		static void SectionBreak();

	private:
		/* Parse the message type into a resultant priority. 
			LogType t : The type to be parsed. */
		static int TypeToPriority(LogType t);
		
		/* Return a message prefix based on the priority value.
			int priority : The priority to be used. */
		static char* PriorityToPrefix(int priority);
};

#endif