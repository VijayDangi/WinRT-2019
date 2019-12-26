//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Hello_World;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	
	//create Grid
	Grid ^ grid = ref new Grid();


	//create text block
	TextBlock ^textBlock = ref new TextBlock();
	textBlock->Text = "Hello World";
	textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Lucida Sans Typewriter");
	textBlock->FontSize = 120;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Gold);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	//add textBlock in grid
	grid->Children->Append(textBlock);

	//add grid to the page
	this->Content = grid;
}
