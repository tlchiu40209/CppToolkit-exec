/*
 * wayneEXEC.hpp
 *
 *  Created on: 2023年10月19日
 *      Author: devlechain
 */

#ifndef LIB_WAYNEEXEC_HPP_
#define LIB_WAYNEEXEC_HPP_

#ifdef __linux__
#include <unistd.h>
#elif __FreeBSD__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

#include <string>
#include <cstring>
#include <vector>
#include <climits>
#include <filesystem>

namespace wayne {
	namespace EXEC {
		std::vector<std::string> argvStringExtractor(int argc, char** argv, std::string targetArgv, int expectedParamAmount);
		std::vector<char*> argvCStringExtractor(int argc, char** argv, const char* targetArgv, int expectedParamAmount);
		std::string* argvStringExtractorStatic(int argc, char** argv, std::string targetArgv, int expectedParamAmount);
		char** argvCStringExtractorStatic(int argc, char** argv, const char* targetArgv, int expectedParamAmount);
		bool isArgvStringExisted(int argc, char** argv, std::string targetArgv);
		bool isArgvCStringExisted(int argc, char** argv, const char* targetArgv);

		std::string getStringExecName();
		char* getCStringExecName();
		std::string getStringExecLocation();
		char* getCStringExecLocation();
		std::string getStringExecAbsolutePath();
		char* getCStringExecAbsolutePath();
	} /* namespace EXEC */
} /* namespace wayne */

#endif /* LIB_WAYNEEXEC_HPP_ */
