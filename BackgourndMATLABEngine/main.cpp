#include"BackgroundMATLABEngine.h"
#include<Windows.h>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main(int argc, char* argv[])
{
	if (BackgroundMatlabEngine::InitMatlabEngine())
	{
		MessageBox(NULL, TEXT("MATLAB background engine initialized."), TEXT("Notice"), MB_OK);
		Sleep(INFINITE);
	}
	else
	{
		MessageBox(NULL, TEXT("MATLAB background engine initialize faild."), TEXT("Error"), MB_OK);
	}
	return 0;
}