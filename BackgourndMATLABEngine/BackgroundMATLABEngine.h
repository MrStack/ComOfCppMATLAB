#pragma once

#include"MatlabEngine.hpp"
#include"MatlabDataArray.hpp"
#include<iostream>

class BackgroundMatlabEngine
{
private:
	BackgroundMatlabEngine(void) {}
public:
	static bool InitMatlabEngine(void)
	{
		if (!EngineInitialized)
		{
			EngineNames = matlab::engine::findMATLAB();
			if (0 != EngineNames.size())
			{
				return true;
			}

			StartupOptions.push_back(u"-automation");//Set startup options
			try
			{
				Engine = matlab::engine::startMATLAB(StartupOptions);
				Engine->eval(u"matlab.engine.shareEngine('LocalEngine')");
				EngineNames = matlab::engine::findMATLAB();
			}
			catch (matlab::engine::Exception& excep)
			{
				std::cout << excep.what() << std::endl;
			}
			EngineInitialized = true;
		}
		return EngineInitialized;
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
bool BackgroundMatlabEngine::EngineInitialized{ false };
std::unique_ptr<matlab::engine::MATLABEngine> BackgroundMatlabEngine::Engine{};
std::vector<std::u16string> BackgroundMatlabEngine::EngineNames{};
std::vector<std::u16string> BackgroundMatlabEngine::StartupOptions{};