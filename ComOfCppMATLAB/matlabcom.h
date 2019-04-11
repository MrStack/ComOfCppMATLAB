#pragma once

#include"MatlabEngine.hpp"
#include"MatlabDataArray.hpp"
#include"../BackgourndMATLABEngine/BackgroundMATLABEngine.h"
#include"ConsoleController.h"
#include<iostream>
#include<memory>

class MatlabEnginInterface
{
private:
	std::string ConvertUTF16ToUTF8(std::u16string& String)
	{
		return matlab::engine::convertUTF16StringToUTF8String(String);
	}
	std::u16string ConvertUTF8ToUTF16(std::string& String)
	{
		return matlab::engine::convertUTF8StringToUTF16String(String);
	}
	bool EngineExist(void)
	{
		return EngineNames.size() != 0;
	}
	void ConnectToEngine(void)
	{
		Engine = matlab::engine::connectMATLAB();
		if (Engine == nullptr)
		{
			throw std::exception{ "Connection faild." };
		}
	}
public:
	MatlabEnginInterface(void) :Output{ std::make_shared<std::basic_stringbuf<char16_t>>() },
		Error{ std::make_shared<std::basic_stringbuf<char16_t>>() }
	{
		if (!FindEngine())
		{
			throw std::exception{ "Matlab engine not found." };
		}
		else
		{
			std::cout << "Matlab engine found." << std::endl;
			std::cout << "Connecting..." << std::endl;
			try
			{
				ConnectToEngine();
			}
			catch (matlab::engine::Exception& excep)
			{
				std::cout << excep.what() << std::endl;
			}
			if (EngineExist())
			{
				std::cout << "Connected to:" << ConvertUTF16ToUTF8(EngineNames.front())
					<< std::endl << "Now working." << std::endl << std::endl;
			}
		}
	}
	bool FindEngine(void)
	{
		if (!EngineExist())
		{
			EngineNames = matlab::engine::findMATLAB();
		}
		if (EngineExist())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Eval(std::string Command)
	{
		try
		{
			std::cout << "Input:" << std::endl << std::endl;
			std::cout << Command << std::endl << std::endl;
			Engine->eval(ConvertTo(Command), Output, Error);
			std::cout << "Output:" << std::endl;
			std::cout << ConvertTo(Output->str()) << std::endl;
		}
		catch (...)
		{
			ConsoleCtrl.SetTextColor(TEXT_COLOR::BRIGHT_RED);
			std::cout << std::endl << ConvertTo(Error->str()) << std::endl;
			ConsoleCtrl.SetDefaultColor();
		}
	}
	std::u16string ConvertTo(std::string Str)
	{
		return ConvertUTF8ToUTF16(Str);
	}
	std::string ConvertTo(std::u16string Str)
	{
		return ConvertUTF16ToUTF8(Str);
	}
private:
	std::unique_ptr<matlab::engine::MATLABEngine> Engine;
	std::vector<std::u16string> EngineNames;
	std::shared_ptr<std::basic_stringbuf<char16_t>> Output;
	std::shared_ptr<std::basic_stringbuf<char16_t>> Error;
	ConsoleController ConsoleCtrl;
};