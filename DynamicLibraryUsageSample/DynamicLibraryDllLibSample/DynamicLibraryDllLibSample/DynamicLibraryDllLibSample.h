// Read this carefully https://manski.net/2011/11/creating-a-dll-project/

//#ifndef DYNAMICLIBRARYDLLLIBSAMPLE_DLL_H
//#define DYNAMICLIBRARYDLLLIBSAMPLE_DLL_H
#pragma once

#ifdef DYNAMICLIBRARYDLLLIBSAMPLE_EXPORTS // add this define-value to "Properties -> C\C++ -> Preprocessor Definitions" and add "DYNAMICLIBRARYDLLONLYSAMPLE_EXPORTS;"
#define FUNCSDLL_API __declspec(dllexport)
#else   
// (!!!!!) With the next 2 Lines we force the App-Project to use .LIB-File (!!!!!)
#pragma message("automatic link to DynamicLibraryDllLibSample.LIB") 
#pragma comment(lib, "DynamicLibraryDllLibSample.lib")
#define FUNCSDLL_API __declspec(dllimport)
#endif

#include <string>
#include <windows.h>


///////////////////////////////////////////////////////////////////////////////
// Description of function-POINTERS on the exported functions.
namespace our_dll
{
	// ALL THEESE 3 ARE THE SAME ... A POINTER:
	//typedef int(__stdcall *pfnPlus21)(int);
	//typedef int(__stdcall* pfnPlus21)(int);
	//typedef int(*__stdcall pfnPlus21)(int);

	typedef int(*pfnPlus11)(int);
	//typedef int(__stdcall *pfnPlus11)(int, int); // such redefinition of a pointer is not allowed
	//typedef int(*__stdcall pfnPlus13)(int);
	typedef int(__stdcall* pfnPlus13)(int);
	//typedef int(__stdcall *pfnPlus13)(int);
	typedef int(__stdcall *pfnPlus14)(int);
	typedef int(__stdcall *pfnPlus15)(int);
			   
	typedef int(*pfnPlus21)(int);
	//typedef int(__stdcall *pfnPlus21)(int, int);
	typedef int(__stdcall *pfnPlus23)(int);
	typedef int(__stdcall *pfnPlus24)(int);

	typedef void* (__stdcall *pfnCreate1)(int);
	typedef void(__stdcall *pfnDestroy1)(void*);
	typedef int(__stdcall *pfnGetCpuSpeed1)(void*);

	typedef void* (__stdcall *pfnCreate2)(int);
	typedef void(__stdcall *pfnDestroy2)(void*);
	typedef int(__stdcall *pfnGetCpuSpeed2)(void*);
	//*/
}

///////////////////////////////////////////////////////////////////////////////
// Description of functions for external usage.

// (+) No method-name corruption (but we can't use more than one method with the same name)
//(--) Compilation error
// (-) Dependency Walker can't see it (not exported <=> has no "__declspec(dllexport)" prefix)
//(~~) Large NAME MANGLING for exported method, discribing ret value and every parameter
// (~) Short NAME MANGLING Adds "_" at the beginning of the exported method name
//     and "@number" to the end of the method => "_myFunc@4"

// (*) To see how mangling names look like 1) on WINDOWS: put the ".dll"-file into "Dependency Walker"
//                                         2) on Linux:   put the ".so"-file into binscan / ELF Library Viewer
// (**)you can go to https://demangler.com and demangle the mangled names of exported methods 

///////////////////////////////////////////////////////////////////////////////
int Plus10_Dll(int _a); // (-)
FUNCSDLL_API int Plus11_Dll(int _a); // (~~) 
FUNCSDLL_API int Plus11_Dll(int _a, int _b); // (~~)
int __stdcall Plus12_Dll(int _a); // (-)
FUNCSDLL_API int __stdcall Plus13_Dll(int _a); // (~~)
extern FUNCSDLL_API int __stdcall Plus14_Dll(int _a); // (~~) 
extern "C" FUNCSDLL_API int __stdcall Plus15_Dll(int _a); // (~)

////////////////////// CTest1  ///////////////////////////////
class FUNCSDLL_API CTest1
{
public:
	CTest1();
	int GetCpuSpeed();
};

//void* __stdcall Create1();
//void __stdcall Destroy1(void* _objPtr);
//int __stdcall GetCpuSpeed1(void* _objPtr);

FUNCSDLL_API void* __stdcall Create1();
FUNCSDLL_API void __stdcall Destroy1(void* _objPtr);
FUNCSDLL_API int __stdcall GetCpuSpeed1(void* _objPtr);


#ifdef __cplusplus
extern "C"
{
#endif
	///////////////////////////////////////////////////////////////////////////////
	int Plus20_Dll(int _a); // (-)
	FUNCSDLL_API int Plus21_Dll(int _a); // (+)
	//FUNCSDLL_API int Plus21_Dll(int _a, int _b); // (--) - in C linkage of overloaded function is not allowed
	int __stdcall Plus22_Dll(int _a); // (-)
	FUNCSDLL_API int __stdcall Plus23_Dll(int _a); // (~)
	extern FUNCSDLL_API int __stdcall Plus24_Dll(int _a); // (~)

	////////////////////// CTest2  ///////////////////////////////
	class FUNCSDLL_API CTest2
	{
	public:
		CTest2();
		int GetCpuSpeed();
	};

	//void* __stdcall Create2();
	//void __stdcall Destroy2(void* _objPtr);
	//int __stdcall GetCpuSpeed2(void* _objPtr);

	FUNCSDLL_API void* __stdcall Create2();
	FUNCSDLL_API void __stdcall Destroy2(void* _objPtr);
	FUNCSDLL_API int __stdcall GetCpuSpeed2(void* _objPtr);

#ifdef __cplusplus
}
#endif
//*/

////////////////////////////// template class ///////////////////////////////////
// I was only able to resolve this by manually importing the already instantiated template from the dll.
template<int T> // impossible to place inside an "extern "C""-BLOCk
class FUNCSDLL_API PrintableInt
{
public:
	PrintableInt(int _value); // Constructor   
	std::string toString() const; // Converts the int into a string.
private:
	int m_value;
};

////////////// class inside a namespace to export from dll  ///////////////////
namespace MathFuncs
{
	class MyMathFuncs
	{
	public:
		static FUNCSDLL_API double Add(double _a, double _b); // Returns a + b
		static FUNCSDLL_API double Subtract(double _a, double _b); // Returns a - b
		static FUNCSDLL_API double Multiply(double _a, double _b); // Returns a * b
		static FUNCSDLL_API double Divide(double _a, double _b); // Returns a / b
		// Throws exeption message if b is 0
	};
}

//#endif // DYNAMICLIBRARYDLLLIBSAMPLE_DLL_H
