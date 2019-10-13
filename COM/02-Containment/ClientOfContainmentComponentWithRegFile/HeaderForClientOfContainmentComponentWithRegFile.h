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

class IMultiplication :public IUnknown
{
public:
	//IMultiplication specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class IDivision : public IUnknown
{
public:
	//IDivision specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0; //pure virtual
};


//CLSID of SumSubtract component // {E11D2D3E-BB98-4DC7-8239-154D03F87258}
const CLSID CLSID_SumSubtract = { 0xe11d2d3e, 0xbb98, 0x4dc7, 0x82, 0x39, 0x15, 0x4d, 0x3, 0xf8, 0x72, 0x58 };

//IID of ISum Interface // {3DED8D46-9A44-47F6-BC10-DEF82CED47BD}
const IID IID_ISum = { 0x3ded8d46, 0x9a44, 0x47f6, 0xbc, 0x10, 0xde, 0xf8, 0x2c, 0xed, 0x47, 0xbd };

//IID of ISubtract Interface // {72A0018A-A7E0-456B-A632-31630ADF2A0F}
const IID IID_ISubtract = { 0x72a0018a, 0xa7e0, 0x456b, 0xa6, 0x32, 0x31, 0x63, 0xa, 0xdf, 0x2a, 0xf };

//IID of IID_IMultiplication // {F7649F4C-9059-4F3D-B165-21055A3BDD64}
const IID IID_IMultiplication = { 0xf7649f4c, 0x9059, 0x4f3d, 0xb1, 0x65, 0x21, 0x5, 0x5a, 0x3b, 0xdd, 0x64 };

//IID of IID_IDivision // {78CABA36-31B6-42D8-9F21-8D6E855748A2}
const IID IID_IDivision = { 0x78caba36, 0x31b6, 0x42d8, 0x9f, 0x21, 0x8d, 0x6e, 0x85, 0x57, 0x48, 0xa2 };

