#pragma once
class IMultiplication : public IUnknown
{
public:
	//IMultiplication specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class IDivision : public IUnknown
{
public:
	//IDivision specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;  //pure virtual
};

//CLSID of MultiplicationDivision Component // {120AFB44-618A-4338-9EA5-C0CB40D0FBCD}
const CLSID CLSID_MultiplicationDivision = { 0x120afb44, 0x618a, 0x4338, 0x9e, 0xa5, 0xc0, 0xcb, 0x40, 0xd0, 0xfb, 0xcd };

//IID of IID_IMultiplcation Interface // {2A4AE9C2-9DA0-4AB3-A171-0A953CE160E7}
const IID IID_IMultiplication = { 0x2a4ae9c2, 0x9da0, 0x4ab3, 0xa1, 0x71, 0xa, 0x95, 0x3c, 0xe1, 0x60, 0xe7 };

//IID of IID_IDivision Interface // {8F2202A8-F8EE-452C-9E7D-2B1E81C7B916}
const IID IID_IDivision = { 0x8f2202a8, 0xf8ee, 0x452c, 0x9e, 0x7d, 0x2b, 0x1e, 0x81, 0xc7, 0xb9, 0x16 };

