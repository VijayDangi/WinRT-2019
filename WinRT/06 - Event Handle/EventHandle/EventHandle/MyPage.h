#pragma once

#include "pch.h"

using namespace Platform; //"Object"
using namespace Windows::UI::Xaml::Controls; //for "Page"
using namespace Windows::UI::Core;  //for "CoreWindow" and "KeyEventArgs"
using namespace Windows::UI::Xaml; //for "RoutedEventArgs"

ref class MyPage sealed : public Page
{
	private:
		TextBlock^ textBlock;
	public:
		MyPage();
		void OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args);
		void OnButtonClick(Object^ sender, RoutedEventArgs^ args);
};
