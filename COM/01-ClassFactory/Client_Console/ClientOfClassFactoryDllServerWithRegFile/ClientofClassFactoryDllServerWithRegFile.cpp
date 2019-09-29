#include <Windows.h>
#include<stdio.h>
#include "ClassFactoryDllServerWithRegFile.h"

int main() {

	HRESULT hr;
	ISum *pISum = NULL;
	ISubtract *pISubtract = NULL;
	int iNum1, iNum2, iResult;

	iNum1 = 155;
	iNum2 = 100;

	//COM Initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr)) 
	{
		printf("COM Library Can Not Be Initialized.\nProgram Will Now Exit.\n\n\n");
		exit(0);
	}

	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);

	if (FAILED(hr))
	{
		printf("ISum Interface Can Not Be Obtained.\n\n\n\n");
		exit(0);
	}

	//call SumOfTwoInteger() of ISum to get the sum
	pISum->SumOfTwoInteger(iNum1, iNum2, &iResult);

	printf("\nSum of %d and %d is %d.\n\n\n", iNum1, iNum2, iResult);

	//call QueryInterface() on ISum, to get Isubtract's pointer
	hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
	
	if (FAILED(hr))
	{
		printf("ISubtract Interface can not be obtained.\n\n\n");
		exit(0);
	}

	//ISum now not needed onwords, release it.
	pISum->Release();
	pISum = NULL; //make released interface NULL

	//call SubtractOfTwoInteger of ISubtract to get the subtraction
	pISubtract->SubtractOfTwoInteger(iNum1, iNum2, &iResult);

	printf("\nSubract of %d and %d is %d.\n\n\n", iNum1, iNum2, iResult);

	//ISubtract now not needed onwords, release it.
	pISubtract->Release();
	pISubtract = NULL; //

	//COM Un-initialization
	CoUninitialize();

	return(0);
}
