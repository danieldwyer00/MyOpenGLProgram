#pragma once

#include <string>
#include <fstream>
#include <ctime>

static const char* extract_version(const char* full)
{
	std::string p1 = full;
	static std::string p2;
	p2.clear();
	p2 = p1.substr(
		p1.find_last_of("/\\") + 1, //after last slash
		(p1.length() - p1.find_last_of("/\\")) - (p1.length() - (p1.find_last_of(".")) + 1) // up to last dot
	);
	return p2.c_str();
}


static void write_log(const char* msg)
{
	// Get the timestamp for the current date and time
	time_t timestamp;
	time(&timestamp);

	std::ofstream logs;
	logs.open("our_log.txt", std::ofstream::app | std::ofstream::out);
	logs  << "\n[" << ctime(&timestamp) << "] " << msg;
	logs.close();
}
