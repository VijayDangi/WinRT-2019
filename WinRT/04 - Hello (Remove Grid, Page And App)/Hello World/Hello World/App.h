#pragma once
#include "pch.h"

using namespace Platform;  //for "ref" , "sealed", "^"
using namespace Windows::ApplicationModel::Activation; //for "LaunchActivatedEventArgs"


ref class App sealed : public Windows::UI::Xaml::Application
{
	public:
		virtual void OnLaunched(LaunchActivatedEventArgs^ args) override; //override means "=0"
};
