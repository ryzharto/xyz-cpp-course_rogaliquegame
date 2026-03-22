#include "Debug.h"

namespace Ryzharto_RogaliqueGame
{
	void EnableConsole()
	{
		AllocConsole();

		FILE* fDummy;
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);

		std::ios::sync_with_stdio();

		std::cout << "Console activated!" << std::endl;
	}

	void Debug(float value, const std::string& comment)
	{
		std::cout << comment << ": " << value << std::endl;
	}

	void DebugWithLogger(float value, const std::string& comment)
	{
		static DebugLogger logger;
		logger.entries.emplace_back(comment, value);
	}
}