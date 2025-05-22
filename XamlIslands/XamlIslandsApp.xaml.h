#pragma once
#include "XamlIslandsApp.xaml.g.h"
#include <winrt/Microsoft.UI.Xaml.Hosting.h>

namespace winrt::XamlIslands::implementation
{
	struct XamlIslandApp : AppT<XamlIslandApp>
	{
		XamlIslandApp()
			: m_windowsXamlManager(winrt::Microsoft::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread())
		{ }

		void OnLaunched(winrt::Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

	private:
		winrt::Microsoft::UI::Xaml::Hosting::WindowsXamlManager m_windowsXamlManager{ nullptr };
	};
}
