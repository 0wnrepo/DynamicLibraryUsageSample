//DynamicLibraryDllOnlySample.cpp

#include "DynamicLibraryDllOnlySample.h"
#include <stdexcept>

// Файл определения модуля (DEF - файл) — это текстовый файл,
// содержащий один или несколько операторов модуля, описывающих
// различные атрибуты библиотеки DLL. Если для экспорта функций библиотеки DLL
// не используется ключевое слово __declspec(dllexport), то для библиотеки DLL потребуется DEF - файл.
// При построении библиотеки DLL компоновщик использует DEF-файл
// для создания файла экспорта (EXP) и файла библиотеки импорта (LIB).

///////////////////////////////////////////////////////////////////////////////
//*
int Plus10_Dll(int _a)
{
	return _a + 10;
}

FUNCSDLL_API int Plus11_Dll(int _a)
{
	return _a + 11;
}

FUNCSDLL_API int Plus11_Dll(int _a, int _b)
{
	return _a + _b + 11;
}

int __stdcall Plus12_Dll(int _a)
{
	return _a + 12;
}

FUNCSDLL_API int __stdcall Plus13_Dll(int _a)
{
	return _a + 13;
}

extern FUNCSDLL_API int __stdcall Plus14_Dll(int _a)
{
	return _a + 14;
}

extern "C" FUNCSDLL_API int __stdcall Plus15_Dll(int _a)
{
	return _a + 15;
}
//*/

//////////////////////////////// extern "C" /////////////////////////////////////
//*
int Plus20_Dll(int _a)
{
	return _a + 20;
}

FUNCSDLL_API int Plus21_Dll(int _a)
{
	return _a + 21;
}

int __stdcall Plus22_Dll(int _a)
{
	return _a + 22;
}

//extern "C" FUNCSDLL_API int __stdcall Plus23_Dll(int _a) // this option works too
FUNCSDLL_API int __stdcall Plus23_Dll(int _a)
{
	return _a + 23;
}

extern FUNCSDLL_API int __stdcall Plus24_Dll(int _a)
{
	return _a + 24;
}
//*/

////////////////////////////// template class ///////////////////////////////////
#include <sstream>
template<int T>
PrintableInt<T>::PrintableInt(int value)
{
	m_value = value;
}

template<int T>
std::string PrintableInt<T>::toString() const
{
	std::ostringstream builder;
	builder << m_value;
	return builder.str();
}

////////////////////// class to export from dll  ///////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GetCycleCount - private function of Test1.cpp.  The static keyword ensures
//                 that this function name is not visible outside Test1.cpp.
static inline unsigned __int64 GetCycleCount()
{
	unsigned int timehi, timelo;

	// Use the assembly instruction rdtsc, which gets the current
	// cycle count (since the process started) and puts it in edx:eax.
	__asm
	{
		rdtsc
			mov timehi, edx;
		mov timelo, eax;
	}

	return ((unsigned __int64)timehi << 32) + (unsigned __int64)timelo;
}

////////////////////// CTest1  ///////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// This is the constructor of class CTest1 that has been exported;
CTest1::CTest1() { }

int CTest1::GetCpuSpeed()
{
	const unsigned __int64 ui64StartCycle = GetCycleCount();
	Sleep(1000);
	return static_cast<int>((GetCycleCount() - ui64StartCycle) / 1000000);
}

///////////////////////////////////////////////////////////////////////////////
// Create1 - create an instance of the class CTest1
//void* __stdcall Create1()
void* __stdcall Create1()
{
	return (new CTest1);
}

///////////////////////////////////////////////////////////////////////////////
// Destroy1 - free the memory for the class instance 
//void __stdcall Destroy1(void* _objPtr)
void __stdcall Destroy1(void* _objPtr)
{
	CTest1* Test1 = (CTest1*)_objPtr;
	if (Test1)
		delete Test1;
}

///////////////////////////////////////////////////////////////////////////////
// GetCpuSpeed - returns CPU speed in MHz;  for example, ~2193 will be 
//               returned for a 2.2 GHz CPU.
//int __stdcall GetCpuSpeed1(void* _objPtr)
int __stdcall GetCpuSpeed1(void* _objPtr)
{
	CTest1* Test1 = (CTest1*)_objPtr;
	if (Test1)
		return Test1->GetCpuSpeed();
	else
		return 0;
}


////////////////////// extern "C" ////////////////////////////
////////////////////// CTest2  ///////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// This is the constructor of class CTest2 that has been exported;
CTest2::CTest2() { }

int CTest2::GetCpuSpeed()
{
	const unsigned __int64 ui64StartCycle = GetCycleCount();
	Sleep(1000);
	return static_cast<int>((GetCycleCount() - ui64StartCycle) / 1000000);
}

///////////////////////////////////////////////////////////////////////////////
// Create2 - create an instance of the class CTest2
//void* __stdcall Create2()
void* __stdcall Create2()
{
	return (new CTest2);
}

///////////////////////////////////////////////////////////////////////////////
// Destroy2 - free the memory for the class instance 
//void __stdcall Destroy2(void* _objPtr)
void __stdcall Destroy2(void* _objPtr)
{
	CTest2* Test2 = (CTest2*)_objPtr;
	if (Test2)
		delete Test2;
}

///////////////////////////////////////////////////////////////////////////////
// GetCpuSpeed - returns CPU speed in MHz;  for example, ~2193 will be 
//               returned for a 2.2 GHz CPU.
//int __stdcall GetCpuSpeed1(void* _objPtr)
int __stdcall GetCpuSpeed2(void* _objPtr)
{
	CTest2* Test2 = (CTest2*)_objPtr;
	if (Test2)
		return Test2->GetCpuSpeed();
	else
		return 0;
}


////////////// class inside a namespace to export from dll  ///////////////////
namespace MathFuncs
{
	double MyMathFuncs::Add(double a, double b)
	{
		return a + b;
	}
	double MyMathFuncs::Subtract(double a, double b)
	{
		return a - b;
	}

	double MyMathFuncs::Multiply(double a, double b)
	{
		return a * b;
	}

	double MyMathFuncs::Divide(double a, double b)
	{
		if (b == 0)
			throw ("b can not be zero!");

		return a / b;
	}
}


