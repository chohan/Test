#include "stdafx.h"
#include "Log.h"
#include <fstream>
#include <string>

#include <sstream>
#include <iostream>
#include "time.h"



CLog::CLog()
{
	init();
	std::mutex mutex_io;
//	std::condition_variable cond;
//	InitializeCriticalSection(&m_crsLog);
}

CLog::~CLog()
{
//	DeleteCriticalSection(&m_crsLog);
}

void CLog::init()
{
	//presumption:
	// ini file has same name as that of program
	// ini file is in the same folder where this program is tarting

	//ini file path
	std::string str(__targv[0]);
	int pos = str.find_last_of("\\");
	std::string sAppFolder	= str.substr(0, pos+1);
	std::string sAppFile	= str.substr(pos+1);
	std::string sLogFolder	= sAppFolder + "log\\";
	m_sLogFilePath			= sLogFolder + sAppFile.substr(0, sAppFile.size()-4);
	system(std::string("mkdir " + sLogFolder).c_str());	// if log folder does not exists, create it

	std::cout << "\n";
	std::cout << "App folder:" << sAppFolder << std::endl;
	std::cout << "App file:"   << sAppFile   << std::endl;
	std::cout << "Log folder:" << sLogFolder << std::endl;
	std::cout << "Log file:"   << m_sLogFilePath<< std::endl;

	//m_sLogFilePath		= U::iniReadString (tsPath.c_str(), _T("Log"), _T("Log.FilePath"), _T("C:/Log"));
	m_bLogType[eINFO]	= true;
	m_bLogType[eWARN]	= true;
	m_bLogType[eERRR]	= true;
	m_bLogType[eTRCE]	= true;
	m_bLogType[eEXCP]	= true;
	m_bLogType[eDBUG]	= true;
	strcpy_s(m_szLogTypes[eINFO], "INFO");
	strcpy_s(m_szLogTypes[eWARN], "WARN");
	strcpy_s(m_szLogTypes[eERRR], "ERRR");
	strcpy_s(m_szLogTypes[eTRCE], "TRCR");
	strcpy_s(m_szLogTypes[eEXCP], "EXCP");
	strcpy_s(m_szLogTypes[eDBUG], "DBUG");
}

void CLog::log(const char* szMethod)
{
	log(szMethod, eTRCE, "called");
}

void CLog::log(const char* szMethod, const char* szDetail)
{
	log(szMethod, eINFO, szDetail);
}

void CLog::log(const char* szMethod, const int eLogType, const char* szDetail)
{
	if(m_bLogType[eLogType] == false)
		return;

	time_t	tNow;
	tm		tmNow;
	char	szDate[80];
	char	szTime[80];
	char	szPath[255];
	time(&tNow);
	localtime_s(&tmNow, &tNow);
	strftime(szDate, 80, "%Y%m%d", &tmNow);
	strftime(szTime, 80, "%H:%M:%S", &tmNow);

	std::string sLogFilePath;
	//U::tstring2string(m_sLogFilePath, sLogFilePath);
	sprintf_s(szPath, "%s_%s.log", m_sLogFilePath.c_str(), szDate);

	//EnterCriticalSection(&m_crsLog);
	std::ofstream fout(szPath, std::ios::app);
	if(szDetail!=NULL)
		fout << szTime << " " << m_szLogTypes[eLogType] << " " << szMethod << " " << szDetail << std::endl;
	else
		fout << szTime << " " << m_szLogTypes[eLogType] << " " << szMethod << std::endl;

	fout.close();
	//LeaveCriticalSection(&m_crsLog);
}

void CLog::log(const char* szDetail, const int eLogType, const char* szMethod, const char* szFile, const int nLine)
{
	std::ostringstream oss;
	oss << szMethod << " " << szFile << "(" << nLine << ") ";
	log(oss.str().c_str(), eLogType, szDetail);
}

void CLog::dlog(const std::ostringstream& oss)
{
	std::string sLogFilePath = std::string("D:\\Projects\\ACCS\\runtime\\log\\ACCSServer");
	time_t	tNow;
	tm		tmNow;
	char	szDate[80];
	char	szTime[80];
	char	szPathOut[255];
	::time(&tNow);
	localtime_s(&tmNow, &tNow);
	strftime(szDate, 80, "%Y%m%d", &tmNow);
	strftime(szTime, 80, "%H:%M:%S ", &tmNow);
	sprintf_s(szPathOut, "%s_%s.log", sLogFilePath.c_str(), szDate);

	std::ofstream fout(szPathOut, std::ios::app);
	std::cout << szTime << oss.str().c_str() << std::endl;
	fout << szTime << oss.str().c_str() << std::endl;
	fout.close();
}

void CLog::dlog(const std::string& sFilePath, const std::ostringstream& oss)
{
	if(sFilePath.empty())
	{
		dlog(oss);
		return;
	}
	//std::string sLogFilePath = std::string("D:\\Projects\\ACCS\\runtime\\log\\ACCSServer");
	time_t	tNow;
	tm		tmNow;
	//char	szDate[80];
	char	szTime[80];
	//char	szPathOut[255];
	::time(&tNow);
	localtime_s(&tmNow, &tNow);
	//strftime(szDate, 80, "%Y%m%d", &tmNow);
	strftime(szTime, 80, "%H:%M:%S ", &tmNow);
	//sprintf_s(szPathOut, "%s_%s.log", sLogFilePath.c_str(), szDate);

	std::ofstream fout(sFilePath, std::ios::app);
	std::cout << szTime << oss.str().c_str() << std::endl;
	fout << szTime << oss.str().c_str() << std::endl;
	fout.close();
}

////////////////////////////////////////////////////////////////////////
void CLog::log2(const int eLogType, const char* szDetail, const char* szFunction, const char* szFile, const int nLine)
{
	if(m_bLogType[eLogType] == false)
		return;

	time_t	tNow;
	tm		tmNow;
	char	szDate[80];
	char	szTime[80];
	char	szPath[255];
	time(&tNow);
	localtime_s(&tmNow, &tNow);
	strftime(szDate, 80, "%Y%m%d", &tmNow);
	strftime(szTime, 80, "%H:%M:%S", &tmNow);

	std::string sLogFilePath;
	//U::tstring2string(m_sLogFilePath, sLogFilePath);
	sprintf_s(szPath, "%s_%s.log", m_sLogFilePath.c_str(), szDate);

	//EnterCriticalSection(&m_crsLog);
	{
		std::unique_lock<std::mutex> loc(m_mutex_io);
		std::ofstream fout(szPath, std::ios::app);
		if(szDetail!=NULL)
			fout << szTime << " " << m_szLogTypes[eLogType] << " " << szFunction << " " << szFile << ":" << nLine << " " << szDetail << std::endl;
		else
			fout << szTime << " " << m_szLogTypes[eLogType] << " " << szFunction << " " << szFile << ":" << nLine << " " << std::endl;

		fout.close();
	}
	//LeaveCriticalSection(&m_crsLog);
}

void CLog::log2(const int eLogType, const std::ostringstream& oss, const char* szFunction, const char* szFile, const int nLine)
{
	if(m_bLogType[eLogType] == false)
		return;

	log2(eLogType, oss.str().c_str(), szFunction, szFile, nLine);
}

void CLog::dlog2(const std::ostringstream& oss, const char* szLogFilePath)
{
	std::string sLogFilePath(szLogFilePath);
	if(sLogFilePath.empty())
		sLogFilePath = std::string("D:\\Projects\\ACCS\\runtime\\log\\ACCSServer_debug.log");

	time_t	tNow;
	tm		tmNow;
	//char	szDate[80];
	char	szTime[80];
	//char	szPathOut[255];
	::time(&tNow);
	localtime_s(&tmNow, &tNow);
	//strftime(szDate, 80, "%Y%m%d", &tmNow);
	strftime(szTime, 80, "%H:%M:%S ", &tmNow);
	//sprintf_s(szPathOut, "%s_%s.log", sLogFilePath.c_str(), szDate);

	std::ofstream fout(sLogFilePath, std::ios::app);
	std::cout << szTime << oss.str().c_str() << std::endl;
	fout << szTime << oss.str().c_str() << std::endl;
	fout.close();
}
