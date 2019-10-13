#pragma once
#include<Windows.h>

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

// CLSID of MultiplicationDivision Component // {8CCDC957-01ED-4B8F-849A-DDF1363BA783}
const CLSID CLSID_MultiplicationDivision = { 0x8ccdc957, 0x1ed, 0x4b8f, 0x84, 0x9a, 0xdd, 0xf1, 0x36, 0x3b, 0xa7, 0x83 };

//IID of IID_IMultiplication // {F7649F4C-9059-4F3D-B165-21055A3BDD64}
const IID IID_IMultiplication = { 0xf7649f4c, 0x9059, 0x4f3d, 0xb1, 0x65, 0x21, 0x5, 0x5a, 0x3b, 0xdd, 0x64 };

//IID of IID_IDivision // {78CABA36-31B6-42D8-9F21-8D6E855748A2}
const IID IID_IDivision = { 0x78caba36, 0x31b6, 0x42d8, 0x9f, 0x21, 0x8d, 0x6e, 0x85, 0x57, 0x48, 0xa2 };
