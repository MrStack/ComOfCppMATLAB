#include"matlabcom.h"
#include<Windows.h>
#include"SharedMATLABEngine.h"
#include<thread>

int main(int argc, char* argv[])
{
	try
	{
		MatlabEnginInterface Interface{};

		matlab::data::ArrayFactory Factory{};
		matlab::data::Array array = Factory.createArray<double>
			({ 1,5 }, { 1,2,3,4,5 });

		Interface.Eval("a = 1");
		Interface.Eval("a(2)");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}	
	


	//此处必须要先编译一个InitMatlabEngine()函数的单独进程。
	//然后再调用MatlabEnginInterface的时候再来连接MATLAB引擎。这样才能将MATLAB引擎移到后台而没有弹出窗口。
	//问题在于如何知道在另一个进程中InitMAtlabEngin()调用成功，并且另一个进程不能退出。
	//如果C++在引用MATLAB引擎进行计算的时候如果出错，错误信息该怎么显示？

	return 0;
}