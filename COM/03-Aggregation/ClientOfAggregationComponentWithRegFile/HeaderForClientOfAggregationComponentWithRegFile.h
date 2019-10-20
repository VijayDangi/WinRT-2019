class ISum: public IUnknown
{
	public:
		//ISum specific method declarations
		virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class ISubtract: public IUnknown
{
	public:
		//ISubtract specific method declarations
		virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class IMultiplication: public IUnknown
{
	public:
		//IMultiplication specific method declarations
		virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class IDivision: public IUnknown
{
	public:
		//IDivision specific method declarations
		virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0; //pure virtual
};

//CLSID of SumSubtract Component // {1B23C698-4459-4A72-9DB8-E289AF22621A}
const CLSID CLSID_CSumSubtract = { 0x1b23c698, 0x4459, 0x4a72, 0x9d, 0xb8, 0xe2, 0x89, 0xaf, 0x22, 0x62, 0x1a };

//IID of ISum Interface // {F6D312CE-7A6F-4DE3-AA4D-A7753D123F40}
const IID IID_ISum = { 0xf6d312ce, 0x7a6f, 0x4de3, 0xaa, 0x4d, 0xa7, 0x75, 0x3d, 0x12, 0x3f, 0x40 };

//IID of ISubtract Interface // {A36E492A-7107-4A7C-946B-2BADF4BC1549}
const IID IID_ISubtract = { 0xa36e492a, 0x7107, 0x4a7c, 0x94, 0x6b, 0x2b, 0xad, 0xf4, 0xbc, 0x15, 0x49 };

//IID of IID_IMultiplcation Interface // {2A4AE9C2-9DA0-4AB3-A171-0A953CE160E7}
const IID IID_IMultiplication = { 0x2a4ae9c2, 0x9da0, 0x4ab3, 0xa1, 0x71, 0xa, 0x95, 0x3c, 0xe1, 0x60, 0xe7 };

//IID of IID_IDivision Interface // {8F2202A8-F8EE-452C-9E7D-2B1E81C7B916}
const IID IID_IDivision = { 0x8f2202a8, 0xf8ee, 0x452c, 0x9e, 0x7d, 0x2b, 0x1e, 0x81, 0xc7, 0xb9, 0x16 };
