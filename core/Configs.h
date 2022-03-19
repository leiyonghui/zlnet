#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <list>
#include <functional>
#include <memory>
#include <assert.h>
#include "TimeHelp.h"
#include "Singleton.h"

namespace core
{
	namespace types
	{
		typedef signed char int8;
		typedef short int16;
		typedef int int32;
		typedef long long int64;
		typedef unsigned char uint8;
		typedef unsigned short uint16;
		typedef unsigned int uint32;
		typedef unsigned long long uint64;
	}
	using namespace types;

	namespace logs
	{
		template<class ...Args>
		inline void printf_log(std::string time, const char* file, int line, Args ...args)
		{
			std::cout << time << " " << file << ":" << line;
			((std::cout << " " << args), ...) << std::endl;
		}

		template<class ...Args>
		inline void printf_info(Args ...args)
		{
			((std::cout << " " << args), ...) << std::endl;
		}

		inline const char* get_short_file(const char* file, size_t size)
		{
			for (size_t i = size - 2; i >= 0; --i)
			{
				switch (file[i]) { case '/': case '\\': return file + i + 1; };
			}
			return file;
		}


#define core_log_trace(...) printf_log(TimeHelp::TimeToString(time(NULL)), get_short_file(__FILE__, sizeof(__FILE__)), __LINE__, ## __VA_ARGS__);
#define core_log_error(...) printf_log(TimeHelp::TimeToString(time(NULL)), get_short_file(__FILE__, sizeof(__FILE__)), __LINE__, "ERROR", ## __VA_ARGS__);
#define core_log_warning(...) printf_log(TimeHelp::TimeToString(time(NULL)), get_short_file(__FILE__, sizeof(__FILE__)), __LINE__, "WARNING", ## __VA_ARGS__);
#define core_log_info(...) printf_info("INFO", ## __VA_ARGS__);
	}
	using namespace logs;

}