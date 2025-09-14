#pragma once
#include <sstream>
#include <iostream>
#include <mutex>

class CLog
{
public:

	//log types as mentioned by the caller of Log method
	enum ELogType
	{
		eINFO = 0,
		eWARN = 1,
		eERRR = 2,
		eTRCE = 3,
		eEXCP = 4,
		eDBUG = 5,
	};

	CLog();
	~CLog();
	void init();
	void log(const char* szMethod);
	void log(const char* szMethod, const char* szDetail);
	void log(const char* szMethod, const int eLogType, const char* szDetail);
	void log(const char* szDetail, const int eLogType, const char* szMethod, const char* szFile, const int nLine);
	static void dlog(const std::ostringstream& oss);
	static void dlog(const std::string& sFilePath, const std::ostringstream& oss);


	void log2(const int eLogType, const char* szDetail, const char* szFunction, const char* szFile, const int nLine);
	void log2(const int eLogType, const std::ostringstream& oss, const char* szFunction, const char* szFile, const int nLine);
	static void dlog2(const std::ostringstream& oss, const char* szLogFilePath="");

private:
	bool m_bLogType[6];	//log entry types, Configuration read from configuration file (ACCSServer.ini)
	char m_szLogTypes[6][5];// initialized in init()

	std::string m_sLogFilePath;
//	CRITICAL_SECTION m_crsLog;
	std::mutex m_mutex_io;
};
