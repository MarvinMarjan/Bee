#pragma once

#include <Windows.h>

namespace util
{
	inline MEMORYSTATUSEX get_mem_stat()
	{
		MEMORYSTATUSEX stat;
		stat.dwLength = sizeof(stat);

		GlobalMemoryStatusEx(&stat);

		return stat;
	}


}