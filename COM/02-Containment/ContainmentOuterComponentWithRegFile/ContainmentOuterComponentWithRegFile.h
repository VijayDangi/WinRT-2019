#pragma once
#include<Windows.h>
class ISum : public IUnknown
{
	public:
		//ISum specific method declarations
		virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
};
class ISubtract : public IUnknown
{
	public:
		//ISubtract specific method declarations
		virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

//CLSID of SumSubtract component // {E11D2D3E-BB98-4DC7-8239-154D03F87258}
const CLSID CLSID_SumSubtract = { 0xe11d2d3e, 0xbb98, 0x4dc7, 0x82, 0x39, 0x15, 0x4d, 0x3, 0xf8, 0x72, 0x58 };

//IID of ISum Interface // {3DED8D46-9A44-47F6-BC10-DEF82CED47BD}
const IID IID_ISum = { 0x3ded8d46, 0x9a44, 0x47f6, 0xbc, 0x10, 0xde, 0xf8, 0x2c, 0xed, 0x47, 0xbd };

//IID of ISubtract Interface // {72A0018A-A7E0-456B-A632-31630ADF2A0F}
const IID IID_ISubtract = { 0x72a0018a, 0xa7e0, 0x456b, 0xa6, 0x32, 0x31, 0x63, 0xa, 0xdf, 0x2a, 0xf };
