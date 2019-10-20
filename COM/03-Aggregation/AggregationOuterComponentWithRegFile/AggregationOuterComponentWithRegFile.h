class ISum: public IUnknown
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

//CLSID of SumSubtract Component // {1B23C698-4459-4A72-9DB8-E289AF22621A}
const CLSID CLSID_CSumSubtract = { 0x1b23c698, 0x4459, 0x4a72, 0x9d, 0xb8, 0xe2, 0x89, 0xaf, 0x22, 0x62, 0x1a };

//IID of ISum Interface // {F6D312CE-7A6F-4DE3-AA4D-A7753D123F40}
const IID IID_ISum = { 0xf6d312ce, 0x7a6f, 0x4de3, 0xaa, 0x4d, 0xa7, 0x75, 0x3d, 0x12, 0x3f, 0x40 };

//IID of ISubtract Interface // {A36E492A-7107-4A7C-946B-2BADF4BC1549}
const IID IID_ISubtract = { 0xa36e492a, 0x7107, 0x4a7c, 0x94, 0x6b, 0x2b, 0xad, 0xf4, 0xbc, 0x15, 0x49 };
