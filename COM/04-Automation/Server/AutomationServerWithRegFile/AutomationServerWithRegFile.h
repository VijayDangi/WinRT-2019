class IMyMath : public IDispatch
{
	public:
		virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
		virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

//CLSID of MyMath Component {3B352E7B-82D4-4395-AE93-80D7E9845DEC}
const CLSID CLSID_MyMath = { 0x3b352e7b, 0x82d4, 0x4395, 0xae, 0x93, 0x80, 0xd7, 0xe9, 0x84, 0x5d, 0xec };

//IID of IMyMath interface // {ECC16BC3-CE3E-470F-B728-A26DBB448EAB}
const IID IID_IMyMath = { 0xecc16bc3, 0xce3e, 0x470f, 0xb7, 0x28, 0xa2, 0x6d, 0xbb, 0x44, 0x8e, 0xab };
