#ifndef DEBUG_TOOLS_H
	#define DEBUG_TOOLS_H
	#define DEBUG_PRIORITY 3

	#define STD_ERROR_PRIORITY 1
	#define STD_WARN_PRIORITY 2
	#define STD_INFO_PRIORITY 3

#include <fstream>
#include <iostream>

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

		/* Log a message to the console (+1 overloads):
		char* text : The message to be displayed (exclude WARNING, ERROR and INFO prefix).
		LogType type : The type of message to be displayed, determines the prefix. */
		static void Log(char* text, LogType type);

		/* Log a message to the console (+1 overloads):
		char* text : The message to be displayed (exclude WARNING, ERROR and INFO prefix).
		LogType type : The type of message to be displayed, determines the prefix.
		int priority : Override the standard priorities, lower = higher priority. */
		static void Log(char* text, LogType type, int priority);

	private:
		/* Parse the message type into a resultant priority. 
			LogType t : The type to be parsed. */
		static int TypeToPriority(LogType t);
		
		/* Return a message prefix based on the priority value.
			int priority : The priority to be used. */
		static char* PriorityToPrefix(int priority);
};

#endif