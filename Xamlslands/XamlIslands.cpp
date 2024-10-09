#include "pch.h"
#include "XamlIslands.h"
#include "XamlIslandsApp.xaml.h" // for 'winrt::make<winrt::ZXamlIslands::implementation::XamlIslandApp>()'
#include <Microsoft.UI.Dispatching.Interop.h> // for ContentPreTranslateMessage

namespace XamlIslands
{
	bool& XxxInitialized()
	{
		static thread_local bool Initialized = false;
		return Initialized;
	}

	static auto& XxxIslandApp()
	{
		static auto MyIslandApp{ winrt::make<winrt::ZXamlIslands::implementation::XamlIslandApp>() };
		// NOTE: Intentionally not thread_local

		// NOTE: DO NOT call winrt::Microsoft::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread() directly. It installs "built in"
		// application. And there can be only one application per process so our XamlIslandApp fails....
		// NOTE: winrt::make needs that during / after XamlIslandApp creation (probably InitializeComponent?) the framework is already InitializeForCurrentThread()-ed...
		// so we need to do it in XamlIslandApp constructor itself. Here is too late!
		return MyIslandApp;
	}

	static auto& XxxDispatcherQueueController()
	{
		static thread_local auto DQC = winrt::Microsoft::UI::Dispatching::DispatcherQueueController::CreateOnCurrentThread();
		return DQC;
	}

	static HRESULT XxxInitializeForCurrentThread()
	{
		//	ASSERT(::WindowsAppRuntime::SelfContained::IsSelfContained())
		static thread_local const HRESULT OneTimeInit = []
			{
				// Island-support: Call init_apartment to initialize COM and WinRT for the thread.
				winrt::init_apartment(winrt::apartment_type::single_threaded);

				// Island-support: We must start a DispatcherQueueController before we can create an island or use Xaml.
				XxxDispatcherQueueController();

				// Island-support: Create our custom Xaml App object. This is needed to properly use the controls and metadata in Microsoft.ui.xaml.controls.dll.
				XxxIslandApp();

				XxxInitialized() = true;

				return S_OK;
			}();
		return OneTimeInit;
	}

	class IslandWndT
	{
		winrt::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource m_DesktopSource{ nullptr };

	public:
		static HRESULT Create(
			_Out_ IslandWndPtrT& Island,
			_In_ HWND Parent,
			_In_ PageT Page)
		{
			Island = {};

			if(!Parent)
				return E_INVALIDARG;

			if(HRESULT hr = XxxInitializeForCurrentThread(); FAILED(hr))
				return hr;

			auto LocalIsland = std::make_shared<IslandWndT>();
			
			LocalIsland->m_DesktopSource = {};
			LocalIsland->m_DesktopSource.Initialize(winrt::Microsoft::UI::GetWindowIdFromWindow(Parent));

			switch(Page)
			{
			case PageT::NonXamlPage:
				{
					winrt::Microsoft::UI::Xaml::Controls::StackPanel xamlContainer;
					xamlContainer.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Microsoft::UI::Colors::LightGray() });

					winrt::Microsoft::UI::Xaml::Controls::TextBlock tb;
					tb.Text(L"Hello World from Xaml Islands!");
					tb.VerticalAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Center);
					tb.HorizontalAlignment(winrt::Microsoft::UI::Xaml::HorizontalAlignment::Center);
					tb.FontSize(48);

					xamlContainer.Children().Append(tb);
					xamlContainer.UpdateLayout();
					LocalIsland->m_DesktopSource.Content(xamlContainer);
				}
				break;

			case PageT::TestPage:
				LocalIsland->m_DesktopSource.Content(winrt::ZXamlIslands::TestPage{});
				break;

			default:
				return E_NOTIMPL;
			}

			LocalIsland->m_DesktopSource.SiteBridge().Show();

			Island = std::move(LocalIsland);
			return S_OK;
		}

		HRESULT MoveAndResize(_In_ const RECT& Rect)
		{
			m_DesktopSource.SiteBridge().MoveAndResize({ Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top });
			return S_OK;
		}
	};

	void Shutdown()
	{
		if(XxxInitialized())
		{
			// Release our reference to App (one more reference is held by xaml framework that will release it in DispatcherQueueController(::ShutdownQueue)
			auto& App = XxxIslandApp();
			App = nullptr;

			// Shutting down dispatcher queue runs all xaml elements destructors (= does garbage collecting and releases resources such as ZpsContextT that would block further app exit)
			// Island-support: To properly shut down after using a DispatcherQueue, call ShutdownQueue[Aysnc]().
			auto& DQC = XxxDispatcherQueueController();
			DQC.ShutdownQueue();
			DQC = nullptr;

			XxxInitialized() = false;

#if(0)
#ifdef _DEBUG
			// When DispatcherQueueController::ShutdownQueue releases its reference to app it stores its WeakRefPtr into g_previousApplicationWeak global variable
			// So it can reuse it should the caller reinitialize xaml core. The final release is done in FrameworkApplication::GlobalDeinit() function 
			// in FrameworkApplication_Partial.cpp. But there is a catch.... according to comments from the function:
			// 
			//		Properly releasing the weakptr here requires vccorlib to be loaded, because it's handled
			//		by vccorlib140[d]!Platform::Details::ControlBlock.  But this function is called during DLL
			//		unload, and vccorlib isn't always around.  So for now we just leak the IWeakReference.
			//		http://task.ms/39377823 XAML can fully unload its own DLL and dependencies after use
			// 
			// the WeakRefPtr is leaked (32 bytes) and the only workaround I found is reinitializing whole xaml core....
			{
				auto DQC2 = winrt::Microsoft::UI::Dispatching::DispatcherQueueController::CreateOnCurrentThread();
				auto WXM = winrt::Microsoft::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread();
				WXM.Close();
				DQC2.ShutdownQueue();
			}
#endif
#endif

		}
	}

	bool PreTranslateMessage(
		const MSG& msg)
	{
		// It's important to call ContentPreTranslateMessage in the event loop so that WinAppSDK can be aware of
		// the messages.  If you don't need to use an accelerator table, you could just call DispatcherQueue.RunEventLoop
		// to do the message pump for you (it will call ContentPreTranslateMessage automatically).
		return ::ContentPreTranslateMessage(&msg);
	}

	HRESULT Create(
		_Out_ IslandWndPtrT& Island,
		_In_ HWND Parent,
		_In_ PageT Page)
	{
		return IslandWndT::Create(Island, Parent, Page);
	}

	HRESULT MoveAndResize(
		_In_ const IslandWndPtrT& Island,
		_In_ const RECT& Rect)
	{
		if(!Island)
			return E_INVALIDARG;

		return Island->MoveAndResize(Rect);
	}
}