#pragma once

// // Including SDKDDKVer.h defines the highest available Windows platform.
// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <unknwn.h>
#include <restrictederrorinfo.h>
#include <hstring.h>

// This tells App.xaml.g.hpp the app will define its own WinMain
#define DISABLE_XAML_GENERATED_MAIN

// To solve warning in WinRT:
// warning C4002 : too many arguments for function - like macro invocation 'GetCurrentTime'
#undef GetCurrentTime

#if(0) // XamlIslands is not using MFC now so it is not needed (I'll leave it here for future reference)
// To solve Error in WinRT
//cppwinrt\winrt\impl\Windows.Globalization.2.h(65, 5) : error C1075 : '{' : no matching token found
#undef TRY // MFC TRY conflicts with winrt::Windows::Globalization::CurrencyIdentifiers::TRY 
#endif

// Com and WinRT headers
#include <Unknwn.h>

// Some generated files, like MainPage.xaml.g.h need files such as Microsoft.UI.Xaml.Markup.h
// to already be included.  Let's just include a bunch of stuff we know we'll need here in the PCH.
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Dispatching.h>
