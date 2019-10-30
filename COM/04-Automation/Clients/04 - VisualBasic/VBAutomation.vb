' for 'Form'
Imports System.Windows.Forms ' this is nothing but Windows.h in c/c++
	'.Net callable dll created by using tlbimp.exe utility
Imports AutomationServerTypeLibForDotNet

Public Class VBAutomation
	Inherits Form
	Public Sub New()	' constructor
		Dim MyIDispatch As Object  ' object is internally IUnknown
		Dim MyRef As New CMyMathClass ' Dim ===> Dimension
		MyIDispatch = MyRef
		Dim iNum1 = 175
		Dim iNum2 = 125
		Dim iSum = MyIDispatch.SumOfTwoIntegers(iNum1, iNum2)
		Dim str As String = String.Format("Sum of {0} And {1} Is {2}", iNum1, iNum2, iSum)
		MsgBox(str) 'default message box with only 1 button of 'ok'
		
		Dim iSub = MyIDispatch.SubtractionOfTwoIntegers(iNum1, iNum2)
		str = String.Format("Subtraction of {0} And {1} Is {2}", iNum1, iNum2, iSub)
		MsgBox(str)
		
		End '`End` works as DestroyWindow(hwnd)
	End Sub 'End Subroutine
	
	<STAThread()> 'Single Threaded Apartment
	Shared Sub Main() ' Shared equivalent to C/C++  static
		Application.EnableVisualStyles() 'Enable all controls of GUI
		Application.Run(New VBAutomation())
	End Sub
End Class