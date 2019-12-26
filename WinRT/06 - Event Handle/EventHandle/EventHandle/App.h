#pragma once

#include "pch.h"

using namespace Platform;
using namespace Windows::ApplicationModel::Activation;  // for "LaunchActivatedEventArg"

ref class App sealed : public Windows::UI::Xaml::Application
{
	public:
		virtual void OnLaunched(LaunchActivatedEventArgs^ args) override;
};
