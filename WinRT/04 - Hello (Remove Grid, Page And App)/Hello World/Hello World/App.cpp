#include"pch.h"
#include "App.h"

using namespace Windows::UI::Xaml;  //for "ApplicationInitializationCallbackParams"
using namespace Windows::UI::Xaml::Controls; //for "TextBlock"

void MyApplicationCallback(ApplicationInitializationCallbackParams ^params)
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
	TextBlock^ textBlock = ref new TextBlock();

	textBlock->Text                = "Hello World";
	textBlock->FontFamily          = ref new Windows::UI::Xaml::Media::FontFamily("Lucida Sans Typewriter");
	textBlock->FontSize            = 120;
	textBlock->FontStyle           = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight          = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground          = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Gold);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment   = Windows::UI::Xaml::VerticalAlignment::Center;

	Window::Current->Content = textBlock;
	Window::Current->Activate();
}
