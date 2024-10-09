#include "pch.h"
#include "TestPage.xaml.h"
#if __has_include("TestPage.g.cpp")
#include "TestPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::ZXamlIslands::implementation
{
	TestPage::TestPage()
	{
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

		m_PersonName = L"Name";
		m_PersonTitle = L"Title";
	}

	winrt::event_token TestPage::PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_PropertyChanged.add(handler);
	}

	void TestPage::PropertyChanged(winrt::event_token const& token)
	{
		m_PropertyChanged.remove(token);
	}

	hstring TestPage::PersonName()
	{
		return m_PersonName;
	}

	void TestPage::PersonName(hstring const& value)
	{
		if(m_PersonName != value)
		{
			m_PersonName = value;
			m_PropertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"PersonName" });
		}
	}

	hstring TestPage::PersonTitle()
	{
		return m_PersonTitle;
	}

	void TestPage::PersonTitle(hstring const& value)
	{
		if(m_PersonTitle != value)
		{
			m_PersonTitle = value;
			m_PropertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"PersonTitle" });
		}
	}


    void TestPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));

		PersonTitle(L"Huh!");

		{
			auto Node = winrt::Microsoft::UI::Xaml::Controls::TreeViewNode{};
			Node.Content(box_value(L"Test1"));

			myTreeView().RootNodes().Append(Node);
		}

		{
			auto Node = winrt::Microsoft::UI::Xaml::Controls::TreeViewNode{};
			Node.Content(box_value(L"Test2"));
			myTreeView().RootNodes().Append(Node);
		}

    }
}
