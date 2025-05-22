#pragma once
#include <memory>

namespace XamlIslands
{
	class IslandWndT;
	using IslandWndPtrT = std::shared_ptr<IslandWndT>;

	enum class PageT
	{
		NonXamlPage,
		TestPage,
	};

	__declspec(dllexport) void Shutdown();

	__declspec(dllexport) bool PreTranslateMessage(
		const MSG& msg);

	__declspec(dllexport) HRESULT Create(
		_Out_ IslandWndPtrT& Island,
		_In_ HWND Parent,
		_In_ PageT Page);

	__declspec(dllexport) HRESULT MoveAndResize(
		_In_ const IslandWndPtrT& Island,
		_In_ const RECT& Rect);
}
