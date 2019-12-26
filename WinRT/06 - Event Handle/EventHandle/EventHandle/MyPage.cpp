#include "pch.h"
#include "MyPage.h"

using namespace Windows::Foundation; //for "TypedEventHandler"
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::System;  //for "VirtualKey"

MyPage::MyPage()
{
	Window::Current->CoreWindow->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &MyPage::OnKeyDown);

	Grid^ grid = ref new Grid();

	textBlock = ref new TextBlock();

	textBlock->Text = "Press Space Bar...";
	textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Lucida Sans Typewriter");
	textBlock->FontSize = 120;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Gold);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	grid->Children->Append(textBlock);

	//Button
	Button^ redButton = ref new Button();
	redButton->Content = "Red";
	redButton->Width = 400;
	redButton->Height = 200;
	redButton->BorderThickness = 12;
	redButton->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	redButton->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
	redButton->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Times New Roman");
	redButton->FontSize = 48;
	redButton->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	redButton->FontWeight = Windows::UI::Text::FontWeights::Bold;
	redButton->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	redButton->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom;

	redButton->Click += ref new RoutedEventHandler(this, &MyPage::OnButtonClick);

	grid->Children->Append(redButton);

	this->Content = grid;
}


//OnKeyDown
void MyPage::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args)
{
	if (args->VirtualKey == VirtualKey::Space)
	{
		static unsigned int keyDown = 0;
		keyDown++;
		if (keyDown == 1)
		{
			textBlock->Text = "Hello World";
		}
		else
		{
			textBlock->Text = "Press Space Bar....";
			keyDown = 0;
		}
	}
}


//OnButtonClick
void MyPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
	textBlock->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
}
