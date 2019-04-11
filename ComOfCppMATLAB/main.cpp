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
	


	//�˴�����Ҫ�ȱ���һ��InitMatlabEngine()�����ĵ������̡�
	//Ȼ���ٵ���MatlabEnginInterface��ʱ����������MATLAB���档�������ܽ�MATLAB�����Ƶ���̨��û�е������ڡ�
	//�����������֪������һ��������InitMAtlabEngin()���óɹ���������һ�����̲����˳���
	//���C++������MATLAB������м����ʱ���������������Ϣ����ô��ʾ��

	return 0;
}