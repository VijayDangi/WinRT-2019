#include "pch.h"
#include "App.h"
#include "MyPage.h"

using namespace Windows::UI::Xaml;  //for "ApplicationInitializationCallbackParams", "ApplicationInitializationCallback"

void MyApplicationCallback(ApplicationInitializationCallbackParams^ params)
{
	App^ app = ref new App();
}

int main(Array<String^>^ args)
{
	ApplicationInitializationCallback^ callback = ref new ApplicationInitializationCallback(MyApplicationCallback);

	Application::Start(callback);

	return(0);
}

void App::OnLaunched(LaunchActivatedEventArgs^ args)
{
	MyPage^ myPage = ref new MyPage();

	Window::Current->Content = myPage;
	Window::Current->Activate();
}
