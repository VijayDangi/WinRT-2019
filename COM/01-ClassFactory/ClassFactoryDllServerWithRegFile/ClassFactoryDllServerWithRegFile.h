#include <Windows.h>

class ISum : public IUnknown 
{
	public:
		//ISum specific method decalration
		/**
		* @param
		*	int  => IN PARAMETER
		*	int  => IN PARAMETER
		*	int* => OUT PARAMETER
		*/
		virtual HRESULT __stdcall SumOfTwoInteger(int, int, int *) = 0;  //pure virtual function
};

class ISubtract : public IUnknown
{
	public:
		//ISubtract specific method decalration
		/**
		* @param
		*	int  => IN PARAMETER
		*	int  => IN PARAMETER
		*	int* => OUT PARAMETER
		*/
		virtual HRESULT __stdcall SubtractOfTwoInteger(int, int, int *) = 0;  //pure virtual function
};

//CLSID of SumSubtract component {B1472830-4173-4E27-A739-7A83843EEBCE}
/*IMPLEMENT_OLECREATE(<< class >> , << external_name >> ,
	0xb1472830, 0x4173, 0x4e27, 0xa7, 0x39, 0x7a, 0x83, 0x84, 0x3e, 0xeb, 0xce);*/
const CLSID CLSID_SumSubtract = { 0xb1472830, 0x4173, 0x4e27, 0xa7, 0x39, 0x7a, 0x83, 0x84, 0x3e, 0xeb, 0xce };

//IID of Isum {12942BED-A4F1-4BCC-BCC9-335C2CB8E67D}
/*IMPLEMENT_OLECREATE(<< class >> , << external_name >> ,
	0x12942bed, 0xa4f1, 0x4bcc, 0xbc, 0xc9, 0x33, 0x5c, 0x2c, 0xb8, 0xe6, 0x7d);*/
const IID IID_ISum = { 0x12942bed, 0xa4f1, 0x4bcc, 0xbc, 0xc9, 0x33, 0x5c, 0x2c, 0xb8, 0xe6, 0x7d };

//IID of ISubtract {BCCD13F9-5B08-48AA-9C86-41370E807958}
/*IMPLEMENT_OLECREATE(<< class >> , << external_name >> ,
	0xbccd13f9, 0x5b08, 0x48aa, 0x9c, 0x86, 0x41, 0x37, 0xe, 0x80, 0x79, 0x58);*/
const IID IID_ISubtract = { 0xbccd13f9, 0x5b08, 0x48aa, 0x9c, 0x86, 0x41, 0x37, 0xe, 0x80, 0x79, 0x58 };

#pragma once
