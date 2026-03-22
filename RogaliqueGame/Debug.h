#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#define DEBUG(x) Debug(x, #x)

namespace Ryzharto_RogaliqueGame
{
	struct DebugLogger
	{
		std::vector<std::pair<std::string, float>> entries;

		~DebugLogger()
		{
			for (const auto& entry : entries)
				std::cout << entry.first << ": " << entry.second << std::endl;
		}
	};

	void EnableConsole();

	void Debug(float value, const std::string& comment);

	void DebugWithLogger(float value, const std::string& comment);
}