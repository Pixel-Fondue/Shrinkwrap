#ifndef MODO_SIMPLELOG_H
#define MODO_SIMPLELOG_H

/*
* ----------------------------------------------------------------
* Logging implementation, put this in the beginning of your cpp under your includes/defines...
* ----------------------------------------------------------------
*/
#include "lx_log.hpp"
#include <string>
#include <utility>

#include <iostream>
using namespace std;



struct Simple_log : CLxUser_Log {

	explicit Simple_log() : CLxUser_Log{ "logsys" } { }

	explicit Simple_log(const char* sys) : CLxUser_Log{ sys } { }

	explicit Simple_log(unsigned i)
	{
		CLxUser_LogService log_svc;
		unsigned count{};
		log_svc.SubSystemCount(&count);
		log_svc.GetSubSystem(i < count ? i : 0u, *this);
	}

	template <typename... Args>
	bool operator()(const char* msg, const Args&... args)
	{
		return Message(LXe_INFO, msg, args...);
	}

	bool operator()(const std::string& msg)
	{
		return Message(LXe_INFO, msg.c_str());
	}

	template <typename T, typename = decltype(std::to_string(std::declval<T>()))>
	bool operator()(T x)
	{
		return Message(LXe_INFO, std::to_string(x).c_str());
	}

	bool operator()(...)
	{
		return Message(LXe_INVALIDARG, "-???-");
	}
};

#endif