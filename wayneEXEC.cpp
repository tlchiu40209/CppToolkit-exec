/*
 * wayneEXEC.cpp
 *
 *  Created on: 2023年10月19日
 *      Author: devlechain
 */

#include "wayneEXEC.hpp"
#include "wayneIO.hpp"

namespace wayne {
	namespace EXEC {
		std::vector<std::string> argvStringExtractor(int argc, char** argv, std::string targetArgv, int expectedParamAmount)
		{
			std::vector<std::string> extractedParam;
			if (argc == 0)
			{
				wayne::IO::logLn("Empty argv!", true);
				return extractedParam;
			}
			if (expectedParamAmount == 0)
			{
				wayne::IO::logLn("There is nothing to extract, if expectedParamAmount is 0", true);
				return extractedParam;
			}
			if (!isArgvStringExisted(argc, argv, targetArgv))
			{
				wayne::IO::logLn("Target Argv " + targetArgv + " does not exist in the array!", true);
				return extractedParam;
			}
			int paramAnchor = -1;
			for (int i = 0; i < argc; i++)
			{
				if (paramAnchor != -1 && expectedParamAmount != 0)
				{
					std::string paramElement(argv[i]);
					//char* paramElement = new char[std::strlen(argv[i])];
					//std::strncpy(paramElement, argv[i], std::strlen(argv[i]));
					extractedParam.push_back(paramElement);
					expectedParamAmount--;
				}
				if (std::strcmp(argv[i], targetArgv.c_str()) == 0)
				{
					paramAnchor = i;
					if (paramAnchor + expectedParamAmount >= argc)
					{
						wayne::IO::logLn("Parameter(s) unreachable.", true);
						exit(1);
					}
				}
			}
			return extractedParam;
		}

		std::vector<char*> argvCStringExtractor(int argc, char** argv, const char* targetArgv, int expectedParamAmount)
		{
			std::vector<char*> extractedParam;
			if (argc == 0)
			{
				wayne::IO::logLn("Empty argv!", true);
				return extractedParam;
			}
			if (expectedParamAmount == 0)
			{
				wayne::IO::logLn("There is nothing to extract, if expectedParamAmount is 0", true);
				return extractedParam;
			}
			if (!isArgvStringExisted(argc, argv, targetArgv))
			{
				wayne::IO::logLn("Target Argv does not exist in the array!", true);
				return extractedParam;
			}
			int paramAnchor = -1;
			for (int i = 0; i < argc; i++)
			{
				if (paramAnchor != -1 && expectedParamAmount != 0)
				{
					//std::string paramElement(argv[i]);
					char* paramElement = new char[std::strlen(argv[i])];
					std::strncpy(paramElement, argv[i], std::strlen(argv[i]));
					extractedParam.push_back(paramElement);
					expectedParamAmount--;
				}
				if (std::strcmp(argv[i], targetArgv) == 0)
				{
					paramAnchor = i;
					if (paramAnchor + expectedParamAmount >= argc)
					{
						wayne::IO::logLn("Parameter(s) unreachable.", true);
						exit(1);
					}
				}
			}
			return extractedParam;
		}

		std::string* argvStringExtractorStatic(int argc, char** argv, std::string targetArgv, int expectedParamAmount)
		{
			std::vector<std::string> toHandle = argvStringExtractor(argc, argv, targetArgv, expectedParamAmount);
			if (toHandle.size() == 0)
			{
				wayne::IO::logLn("Cannot convert empty dynamic array to static array", true);
				return nullptr;
			}
			else
			{
				std::string* toReturn = new std::string[toHandle.size()];
				for (size_t i = 0; i < toHandle.size(); i++)
				{
					toReturn[i] = toHandle[i];
				}
				return toReturn;
			}
		}

		char** argvCStringExtractorStatic(int argc, char** argv, const char* targetArgv, int expectedParamAmount)
		{
			std::vector<char*> toHandle = argvCStringExtractor(argc, argv, targetArgv, expectedParamAmount);
			if (toHandle.size() == 0)
			{
				wayne::IO::logLn("Cannot convert empty dynamic array to static array", true);
				return nullptr;
			}
			else
			{
				char** toReturn = new char*[toHandle.size()];
				for (size_t i = 0; i < toHandle.size(); i++)
				{
					toReturn[i] = toHandle[i];
				}
				return toReturn;
			}
		}

		bool isArgvStringExisted(int argc, char** argv, std::string targetArgv)
		{
			return isArgvCStringExisted(argc, argv, targetArgv.c_str());
		}

		bool isArgvCStringExisted(int argc, char** argv, const char* targetArgv)
		{
			if (argc < 2)
			{
				wayne::IO::logLn("Empty argv!", true);
				return false; /*argv[0] = program itself. If argc < 2, that means to argv, other than the program's name itself*/
			}
			for (int i = 0; i < argc; i++)
			{
				if (std::strcmp(argv[i], targetArgv) ==  0)
				{
					return true;
				}
			}
			return false;
		}

		std::string getStringExecName()
		{
			return std::filesystem::path(getCStringExecAbsolutePath()).filename().string();
		}
		char* getCStringExecName()
		{
			char *toReturn = new char[getStringExecName().length()];
			std::strncpy(toReturn, getStringExecName().c_str(), getStringExecName().length());
			return toReturn;
		}

		std::string getStringExecLocation()
		{
			return std::filesystem::path(getCStringExecAbsolutePath()).parent_path().string();
		}

		char* getCStringExecLocation()
		{
			char *toReturn = new char[getStringExecLocation().length()];
			std::strncpy(toReturn, getStringExecLocation().c_str(), getStringExecLocation().length());
			return toReturn;
		}

		std::string getStringExecAbsolutePath()
		{
			char result[PATH_MAX];
#ifdef __linux__
			ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
#elif __FreeBSD__
			ssize_t count = readlink("/proc/curproc/file", result, PATH_MAX);
#elif _WIN32
			GetModuleFileNameA(NULL, result, PATH_MAX);
			return std::string(result);
#endif
			return std::string(result, (count > 0) ? count : 0);
			/*https://gist.github.com/yingzm/cfb33b03ceaf3320031adc986ab76810*/
		}
		char* getCStringExecAbsolutePath()
		{
			char* toReturn = new char[getStringExecAbsolutePath().length()];
			std::strncpy(toReturn, getStringExecAbsolutePath().c_str(), getStringExecAbsolutePath().length());
			return toReturn;
		}
	} /* namespace EXEC */
} /* namespace wayne */
