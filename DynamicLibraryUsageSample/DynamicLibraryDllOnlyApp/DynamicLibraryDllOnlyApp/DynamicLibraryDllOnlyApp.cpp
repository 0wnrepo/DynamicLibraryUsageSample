// main.cpp

#include <iostream>
#include <windows.h>

//#include "../../DynamicLibraryDllOnlySample\DynamicLibraryDllOnlySample\DynamicLibraryDllOnlySample.h" //use this line if you have lost .SLN-File for this Project
#include "DynamicLibraryDllOnlySample.h"

#ifdef UNICODE //UNICODE is used by Windows headers //_UNICODE is used by C-runtime / MFC headers.
#define OUR_DLL L"DynamicLibraryDllOnlySample.dll"
#else
#define OUR_DLL "DynamicLibraryDllOnlySample.dll"
#endif

int main()
{
	/*
	double a = 7.4;
	int b = 99;

	std::cout << "a + b = " << MathFuncs::MyMathFuncs::Add(a, b) << std::endl;

	//#if 0
	//try
	//{
	std::cout << "a / 0 = " <<
	MathFuncs::MyMathFuncs::Divide(a, 0) << std::endl;
	//}
	//catch (const invalid_argument &e)
	//{
	//	std::cout << "Caught exception: " << e.what() << std::endl;
	//}
	*/

	//////////////////////////////////////////////////////////////////////////////////////////
	// (!!!) Witout .LIB file it's:
	// (+) We can ONLY instantiate template class inside a DLL and return a pointer
	// (-) BUT it's Impossible to use instances of classes and templates like this:

	//////////////////////////////////////////////////////////////////////////////////////////
	// [1] Use via direct call of exported functions (without LoadLibrary  and  GetProcAddress)
	/*
	double b = 7.4;
	int c = 99;

	std::cout << "b + c = " << MathFuncs::MyMathFuncs::Add(b, c) << std::endl;
	std::cout << "b - c = " << MathFuncs::MyMathFuncs::Subtract(b, c) << std::endl;
	std::cout << "b * c = " << MathFuncs::MyMathFuncs::Multiply(b, c) << std::endl;
	std::cout << "b / c = " << MathFuncs::MyMathFuncs::Divide(b, c) << std::endl;

	try
	{
		std::cout << "b / 0 = " << MathFuncs::MyMathFuncs::Divide(b, 0) << std::endl;
	}
	catch (...)//(const invalid_argument &e)
	{
		std::cout << "Caught exception: a devided by zero" //<< e.what() 
			<<std::endl;
	}
	*/

//*	//////////////////////////////////////////////////////////////////////////////////////////
	// [2] Use via call using dynamic linking (LoadLibrary  and  GetProcAddress)
	HINSTANCE hInstLibrary0 = LoadLibrary(OUR_DLL);
	if (hInstLibrary0) //!=NULL
	{
		// get addressses for functions we need
		typedef double(__stdcall* pfnAdd)(double, double);
		pfnAdd _Add = (pfnAdd)GetProcAddress(hInstLibrary0, ("?Add@MyMathFuncs@MathFuncs@@SANNN@Z"));
		if (!_Add) { return EXIT_FAILURE; }

		typedef double(__stdcall* pfnSub)(double, double);
		pfnSub _Sub = (pfnSub)GetProcAddress(hInstLibrary0, ("?Subtract@MyMathFuncs@MathFuncs@@SANNN@Z"));
		if (!_Sub) { return EXIT_FAILURE; }

		typedef double(__stdcall* pfnMul)(double, double);
		pfnMul _Mul = (pfnMul)GetProcAddress(hInstLibrary0, ("?Multiply@MyMathFuncs@MathFuncs@@SANNN@Z"));
		if (!_Mul) { return EXIT_FAILURE; }

		typedef double(__stdcall* pfnDiv)(double, double);
		pfnDiv _Div = (pfnDiv)GetProcAddress(hInstLibrary0, ("?Divide@MyMathFuncs@MathFuncs@@SANNN@Z"));
		if (!_Div) { return EXIT_FAILURE; }


		double b = 7.4;
		double c = 99.0;

		std::cout << "b + c = " << _Add(b, c) << std::endl;
		std::cout << "b - c = " << _Sub(b, c) << std::endl;
		std::cout << "b * c = " << _Mul(b, c) << std::endl;
		std::cout << "b / c = " << _Div(b, c) << std::endl;

		try
		{
			std::cout << "b / 0 = " << _Div(b, 0) << std::endl;
		}
		catch (...)//(const invalid_argument &e)
		{
			std::cout << "Caught exception: a devided by zero" //<< e.what() 
				<< std::endl;
		}


		FreeLibrary(hInstLibrary0);
		hInstLibrary0 = NULL;
	}
	else {
		std::cout << "LoadLibrary() failed" << std::endl;
	}
//*/


	//////////////////////////////////////////////////////////////////////////////////////////
	// (!!!) Witout .LIB file it's:
	// (+) We can ONLY instantiate template class inside a DLL and return a pointer
	// (-) BUT it's Impossible to use instances of classes and templates like this:


	/*
	int cpuSpeed = 0;

	CTest1 Tst1;
	cpuSpeed = Tst1.GetCpuSpeed();
	std::string spd1("Tst1.GetCpuSpeed() returned = ");
	spd1.append(std::to_string(cpuSpeed));
	std::cout << spd1 << std::endl;

	CTest2 Tst2;
	cpuSpeed = Tst2.GetCpuSpeed();
	std::string spd2("Tst2.GetCpuSpeed() returned = ");
	spd2.append(std::to_string(cpuSpeed));
	std::cout << spd2 << std::endl;
	*/

	//////////////////////////////////////////////////////////////////////////////////////////
	// I was only able to resolve this by manually importing the already instantiated template from the dll.
	//
	// PrintableInt<6> test(5);
	// std::cout << test.toString() << std::endl;
	//*/

	//////////////////////////////////////////////////////////////////////////////////////////
	// [1] Use via direct call of exported functions (without LoadLibrary  and  GetProcAddress)
	/*
	void* objptr1 = Create1();
	int nSpeed1 = GetCpuSpeed1(objptr1);
	std::string str1("GetCpuSpeed1() returned = ");
	str1.append(std::to_string(nSpeed1));
	std::cout << str1 << std::endl;
	Destroy1(objptr1);

	void* objptr2 = Create2();
	int nSpeed2 = GetCpuSpeed2(objptr2);
	std::string str2("GetCpuSpeed2() returned = ");
	str2.append(std::to_string(nSpeed2));
	std::cout << str2 << std::endl;
	Destroy2(objptr2);
	*/


	//////////////////////////////////////////////////////////////////////////////////////////
	// [2] Use via call using dynamic linking (LoadLibrary  and  GetProcAddress)
	HINSTANCE hInstLibrary1 = LoadLibrary(OUR_DLL);
	if (hInstLibrary1) //!=NULL
	{
		// get addressses for functions we need
		typedef void* (__stdcall* pfnCreate1)();
		pfnCreate1 _Create1 = (pfnCreate1)GetProcAddress(hInstLibrary1, ("?Create1@@YGPAXXZ"));
		if (!_Create1) { return EXIT_FAILURE; }

		typedef int(__stdcall* pfnGetCpuSpeed1)(void *);
		pfnGetCpuSpeed1 _GetCpuSpeed1 = (pfnGetCpuSpeed1)GetProcAddress(hInstLibrary1, ("?GetCpuSpeed1@@YGHPAX@Z"));
		if (!_GetCpuSpeed1) { return EXIT_FAILURE; }

		typedef void(__stdcall* pfnDestroy1)(void *);
		pfnDestroy1 _Destroy1 = (pfnDestroy1)GetProcAddress(hInstLibrary1, ("?Destroy1@@YGXPAX@Z"));
		if (!_Destroy1) { return EXIT_FAILURE; }

		void* objptr1 = _Create1();
		int nSpeed1 = _GetCpuSpeed1(objptr1);
		std::string str1("GetCpuSpeed1() returned = ");
		str1.append(std::to_string(nSpeed1));
		std::cout << str1 << std::endl;
		_Destroy1(objptr1);

		FreeLibrary(hInstLibrary1);
		hInstLibrary1 = NULL;
	}
	else {
		std::cout << "LoadLibrary() failed" << std::endl;
	}


	HINSTANCE hInstLibrary2 = LoadLibrary(OUR_DLL);
	if (hInstLibrary2) //!=NULL
	{
		// get addressses for functions we need
		typedef void* (__stdcall* pfnCreate2)();
		pfnCreate2 _Create2 = (pfnCreate2)GetProcAddress(hInstLibrary2, ("_Create2@0"));
		if (!_Create2) { return EXIT_FAILURE; }

		typedef int(__stdcall* pfnGetCpuSpeed2)(void *);
		pfnGetCpuSpeed2 _GetCpuSpeed2 = (pfnGetCpuSpeed2)GetProcAddress(hInstLibrary2, ("_GetCpuSpeed2@4"));
		if (!_GetCpuSpeed2) { return EXIT_FAILURE; }

		typedef void(__stdcall* pfnDestroy2)(void *);
		pfnDestroy2 _Destroy2 = (pfnDestroy2)GetProcAddress(hInstLibrary2, ("_Destroy2@4"));
		if (!_Destroy2) { return EXIT_FAILURE; }

		void* objptr2 = _Create2();
		int nSpeed2 = _GetCpuSpeed2(objptr2);
		std::string str2("GetCpuSpeed2() returned = ");
		str2.append(std::to_string(nSpeed2));
		std::cout << str2 << std::endl;
		_Destroy2(objptr2);

		FreeLibrary(hInstLibrary2);
		hInstLibrary2 = NULL;
	}
	else {
		std::cout << "LoadLibrary() failed" << std::endl;
	}


	//////////////////////////////////////////////////////////////////////////////////////////
	// [1] Use via direct call of exported functions (without LoadLibrary  and  GetProcAddress)
	
	int a = 0;
	/*
	//a = Plus10_Dll(10);		std::cout << "a = " << a << std::endl;
	a = Plus11_Dll(10);		std::cout << "a = " << a << std::endl;
	a = Plus11_Dll(10, 20);	std::cout << "a = " << a << std::endl;
	//a = Plus12_Dll(10);		std::cout << "a = " << a << std::endl;
	a = Plus13_Dll(10);		std::cout << "a = " << a << std::endl;
	a = Plus14_Dll(10);		std::cout << "a = " << a << std::endl;
	a = Plus15_Dll(10);		std::cout << "a = " << a << std::endl;

	//a = Plus20_Dll(10);		std::cout << "a = " << a << std::endl;
	a = Plus21_Dll(10);		std::cout << "a = " << a << std::endl;
	//a = Plus22_Dll(10);		std::cout << "a = " << a << std::endl;
	a = Plus23_Dll(10);		std::cout << "a = " << a << std::endl;
	a = Plus24_Dll(10);		std::cout << "a = " << a << std::endl;
	*/
	//////////////////////////////////////////////////////////////////////////////////////////
	// [2] Use via call using dynamic linking (LoadLibrary  and  GetProcAddress)
	HINSTANCE hLib = LoadLibrary(OUR_DLL); // We can also use a full path to the dll
	if (hLib /*!=NULL*/)
	{
		// Our DLL is loaded and ready to go. Set up our function pointers.
		our_dll::pfnPlus11 _Plus11; // Typedef functions to hold what is in the DLL
		our_dll::pfnPlus13 _Plus13;
		our_dll::pfnPlus14 _Plus14;
		our_dll::pfnPlus15 _Plus15;

		our_dll::pfnPlus21 _Plus21;
		our_dll::pfnPlus23 _Plus23;
		our_dll::pfnPlus24 _Plus24;

		_Plus11 = (our_dll::pfnPlus11)GetProcAddress(hLib, "?Plus11_Dll@@YAHH@Z"); // (*)
		if (_Plus11) // Check if _Plus11 is currently holding a function, if not don't run it.
		{
			a = _Plus11(10);
			std::cout << "a = " << a << std::endl;
		}
		else {
			std::cout << "GetProcAddress() failed" << std::endl;
		}

		_Plus13 = (our_dll::pfnPlus13)GetProcAddress(hLib, "?Plus13_Dll@@YGHH@Z");
		if (_Plus13) // Check if _Plus13 is currently holding a function, if not don't run it.
		{
			a = _Plus13(10);
			std::cout << "a = " << a << std::endl;
		}
		else {
			std::cout << "GetProcAddress() failed" << std::endl;
		}

		_Plus14 = (our_dll::pfnPlus14)GetProcAddress(hLib, "?Plus14_Dll@@YGHH@Z");
		if (_Plus14) // Check if _Plus14 is currently holding a function, if not don't run it.
		{
			a = _Plus14(10);
			std::cout << "a = " << a << std::endl;
		}
		else {
			std::cout << "GetProcAddress() failed" << std::endl;
		}

		_Plus15 = (our_dll::pfnPlus15)GetProcAddress(hLib, "_Plus15_Dll@4");
		if (_Plus15) // Check if _Plus15 is currently holding a function, if not don't run it.
		{
			a = _Plus15(10);
			std::cout << "a = " << a << std::endl;
		}
		else {
			std::cout << "GetProcAddress() failed" << std::endl;
		}

		///////////////////////////////////////////////////////////////////
		_Plus21 = (our_dll::pfnPlus21)GetProcAddress(hLib, "Plus21_Dll");
		if (_Plus21) // Check if _Plus21 is currently holding a function, if not don't run it.
		{
			a = _Plus21(10);
			std::cout << "a = " << a << std::endl;
		}
		else {
			std::cout << "GetProcAddress() failed" << std::endl;
		}

		_Plus23 = (our_dll::pfnPlus23)GetProcAddress(hLib, "_Plus23_Dll@4");
		if (_Plus23) // Check if _Plus23 is currently holding a function, if not don't run it.
		{
			a = _Plus23(10);
			std::cout << "a = " << a << std::endl;
		}
		else {
			std::cout << "GetProcAddress() failed" << std::endl;
		}

		_Plus24 = (our_dll::pfnPlus24)GetProcAddress(hLib, "_Plus24_Dll@4");
		if (_Plus24) // Check if _Plus24 is currently holding a function, if not don't run it.
		{
			a = _Plus24(10);
			std::cout << "a = " << a << std::endl;
		}
		else {
			std::cout << "GetProcAddress() failed" << std::endl;
		}


		FreeLibrary(hLib);
		hLib = NULL;
	}
	else {
		std::cout << "LoadLibrary() failed" << std::endl;
	}
	//#endif

	getchar(); //system("pause");
	return EXIT_SUCCESS;
}
