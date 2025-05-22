#pragma once

#include "TestPage.g.h"

namespace winrt::XamlIslands::implementation
{
    struct TestPage : TestPageT<TestPage>
    {
		TestPage();

		winrt::event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
		void PropertyChanged(winrt::event_token const& token);

		hstring PersonName();
		void PersonName(hstring const& value);
		hstring PersonTitle();
		void PersonTitle(hstring const& value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

	private:
		winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_PropertyChanged;
		winrt::hstring m_PersonName;
		winrt::hstring m_PersonTitle;
    };
}

namespace winrt::XamlIslands::factory_implementation
{
    struct TestPage : TestPageT<TestPage, implementation::TestPage>
    {
    };
}
