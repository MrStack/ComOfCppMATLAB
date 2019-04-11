#pragma once
#include"MatlabEngine.hpp"
#include"MatlabDataArray.hpp"
#include<iostream>
#include<Windows.h>

class SharedMATLABEngine
{
private:
	SharedMATLABEngine(void) {}
public:
	static bool InitMatlabEngine(void)
	{
		STARTUPINFO StartupInfo{};
		PROCESS_INFORMATION ProcessInfo{};
		StartupInfo.cb = sizeof(StartupInfo);
		wchar_t CommandLine[]{ L"matlab -automation -r \"matlab.engine.shareEngine('LocalEngine')\"" };
		if (!CreateProcess(NULL,   // No module name (use command line)
			CommandLine,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&StartupInfo,            // Pointer to STARTUPINFO structure
			&ProcessInfo)           // Pointer to PROCESS_INFORMATION structure
			)
		{
			std::cout << "Starting MATLAB faild. " << "Error code:" << GetLastError();
			return false;
		}
		else
		{
			return true;
		}

		// Wait until child process exits.
		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

		// Close process and thread handles. 
		CloseHandle(ProcessInfo.hProcess);
		CloseHandle(ProcessInfo.hThread);


		//if (!EngineInitialized)
		//{
		//	EngineNames = matlab::engine::findMATLAB();
		//	if (0 != EngineNames.size())
		//	{
		//		return true;
		//	}

		//	StartupOptions.push_back(u"-automation");//Set startup options
		//	try
		//	{
		//		Engine = matlab::engine::startMATLAB(StartupOptions);
		//		Engine->eval(u"matlab.engine.shareEngine('LocalEngine')");
		//		EngineNames = matlab::engine::findMATLAB();
		//	}
		//	catch (matlab::engine::Exception& excep)
		//	{
		//		std::cout << excep.what() << std::endl;
		//	}
		//	EngineInitialized = true;
		//}
		//return EngineInitialized;
	}
	static std::vector<std::u16string> GetEngineNames(void)
	{
		return EngineNames;
	}
private:
	static bool EngineInitialized;
	static std::unique_ptr<matlab::engine::MATLABEngine> Engine;
	static std::vector<std::u16string> EngineNames;
	static std::vector<std::u16string> StartupOptions;
};
bool SharedMATLABEngine::EngineInitialized{ false };
std::unique_ptr<matlab::engine::MATLABEngine> SharedMATLABEngine::Engine{};
std::vector<std::u16string> SharedMATLABEngine::EngineNames{};
std::vector<std::u16string> SharedMATLABEngine::StartupOptions{};