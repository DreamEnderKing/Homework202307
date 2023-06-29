#pragma once

#include "Structure.h"

#include <chrono>

namespace Displayer
{
	inline void sleep(int period)
	{
		auto p = std::chrono::system_clock::now();
		while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - p).count() <= period);
	}
	int Cover(Structure::ClassInfo& info);
	int Input(Structure::ClassInfo& info);
	int Modify(Structure::ClassInfo& info);
	int Search(Structure::ClassInfo& info);
	int Count(Structure::ClassInfo& info);
}