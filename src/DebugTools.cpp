#include "DebugTools.h"

/* PUBLIC */
void DebugTools::Log(char* text, LogType type, int indent)
{
	int priority = TypeToPriority(type);
	if ((priority + indent) <= DEBUG_PRIORITY)
	{
		std::string tabs(indent * 3, ' ');
		std::cout << PriorityToPrefix(priority) << tabs.c_str() << text << std::endl;
	}
}
/* PRIVATE */
int DebugTools::TypeToPriority(LogType t)
{
	switch (t)
	{
		case LogType::Error:
			return STD_ERROR_PRIORITY;
		case LogType::Warn:
			return STD_WARN_PRIORITY;
		case LogType::Info:
			return STD_INFO_PRIORITY;
		default:
			return -1;
	}
}

char* DebugTools::PriorityToPrefix(int priority)
{
	switch (priority)
	{
		case 1:
			return "[ERROR] : ";
		case 2:
			return "[WARN] : ";
		case 3:
			return "[INFO] : ";
		default:
			return "[NULL] : ";
	}
}