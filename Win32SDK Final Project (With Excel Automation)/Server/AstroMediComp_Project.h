//Employee Details structure
struct EmployeeDetails
{
	char  firstName[127];
	char  lastName[127];
	char  email_id[127];
	char  mobile_no[12];
	char  gender[7];
	char  address[255];
	char  dateOfBirth[12];
	char  dateOfJoining[12];
	char  department_name[50];
	char  employeeId[12] ;
	struct EmployeeDetails *nextDetails;
};

//Seach Category
#define SEARCH_NONE               -1
#define SEARCH_BY_FIRST_NAME       0
#define SEARCH_BY_LAST_NAME        1
#define SEARCH_BY_EMAIL_ID         2
#define SEARCH_BY_MOBILE_NUMBER    3
#define SEARCH_BY_DATE_OF_BIRTH    4
#define SEARCH_BY_DATE_OF_JOINING  5
//#define SEARCH_BY_EMPLOYEE_ID      6


//Department name
const char* Department_WM_CREATE      = "WM_CREATE";
const char* Department_WM_LBUTTONDOWN = "WM_LBUTTONDOWN";
const char* Department_WM_SIZE        = "WM_SIZE";
const char* Department_WM_KEYUP       = "WM_KEYUP";
const char* Department_WM_KEYDOWN     = "WM_KEYDOWN";
const char* Department_WM_COMMAND     = "WM_COMMAND";
const char* Department_WM_DRAWITEM    = "WM_DRAWITEM";
const char* Department_WM_PAINT       = "WM_PAINT";
const char* Department_WM_CHAR        = "WM_CHAR";
const char* Department_WM_DESTROY     = "WM_DESTROY";
const char* Department_WM_SETFOCUS    = "WM_SETFOCUS";
const char* Department_WM_ENABLE      = "WM_ENABLE";
const char* Department_WM_MOUSEMOVE   = "WM_MOUSEMOVE";
const char* Department_WM_RBUTTONDOWN = "WM_RBUTTONDOWN";

//Department Id
#define ID_WM_CREATE          501
#define ID_WM_LBUTTONDOWN     502
#define ID_WM_SIZE            503
#define ID_WM_KEYUP           504
#define ID_WM_KEYDOWN         505
#define ID_WM_COMMAND         506
#define ID_WM_DRAWITEM        507
#define ID_WM_PAINT           508
#define ID_WM_CHAR            509
#define ID_WM_DESTROY         510
#define ID_WM_SETFOCUS        511
#define ID_WM_ENABLE          512
#define ID_WM_MOUSEMOVE       513
#define ID_WM_RBUTTONDOWN     514

class IReadRecordFile : public IUnknown
{
	public:
		/**
		 * @param {char*} departmentName (IN parameter) 
		 *				departmentName from which record has to be read. (if 'NULL' all employee records has to be read)
		 *
		 * @param {short} searchCategory (IN parameter)
		 *
		 * @param {char*} searchString (IN parameter)
     *        the string which has to be searched. (NULL if no string is searched).
		 *
		 * @param {struct EmployeeDetails*} employeeRecords (OUT parameter)
		 *	      the employees record is return from this parameter.
		 *
		 * @param {int*}  lengthOfRecords (OUT parameter)
		 *				number of records returns;
		 */
		virtual HRESULT __stdcall ReadRecord(const char*, short, char*, struct EmployeeDetails **, int*) = 0;
};

class IWriteRecordFile : public IUnknown
{
	public:
		/**
		 * @param {char*} departmentName (IN parameter)
		 *        the record is belongs to which department
		 *
		 * @param {struct EmployeeDetails*} (IN parameter)
		 *				the actual record which has to be save
		 *
		 * @param {int*} (IN parameter)
		 *				number of records are present in EmployeeDetails struct
		 */
		virtual HRESULT __stdcall WriteRecord(const char*, struct EmployeeDetails *, int*) = 0;
};

//CLSID of RecordFile
// {75D811F9-91D4-49AF-A32E-BFD58F5B7993}
//IMPLEMENT_OLECREATE(<<class>>, <<external_name>>, 
//0x75d811f9, 0x91d4, 0x49af, 0xa3, 0x2e, 0xbf, 0xd5, 0x8f, 0x5b, 0x79, 0x93);
const CLSID CLSID_RecordFile = { 0x75d811f9, 0x91d4, 0x49af, 0xa3, 0x2e, 0xbf, 0xd5, 0x8f, 0x5b, 0x79, 0x93 };

//IID of IReadRecordFile
// {C21F5627-D3BD-4725-9870-C83C04AACA70}
//IMPLEMENT_OLECREATE(<<class>>, <<external_name>>, 
//0xc21f5627, 0xd3bd, 0x4725, 0x98, 0x70, 0xc8, 0x3c, 0x4, 0xaa, 0xca, 0x70);
const IID IID_IReadRecordFile = { 0xc21f5627, 0xd3bd, 0x4725, 0x98, 0x70, 0xc8, 0x3c, 0x4, 0xaa, 0xca, 0x70 };

//IID of IWriteRecordFile
// {2CC96AC3-A2D1-4F50-9EC8-4119BF16F7BA}
//IMPLEMENT_OLECREATE(<<class>>, <<external_name>>, 
//0x2cc96ac3, 0xa2d1, 0x4f50, 0x9e, 0xc8, 0x41, 0x19, 0xbf, 0x16, 0xf7, 0xba);
const IID IID_IWriteRecordFile = { 0x2cc96ac3, 0xa2d1, 0x4f50, 0x9e, 0xc8, 0x41, 0x19, 0xbf, 0x16, 0xf7, 0xba };
