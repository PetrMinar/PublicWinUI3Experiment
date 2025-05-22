#include "pch.h"
#include "TestViewModel.h"
#if __has_include("TestViewModel.g.cpp")
#include "TestViewModel.g.cpp"
#endif

namespace winrt::XamlIslands::implementation
{
    int32_t TestViewModel::MyProperty()
    {
        throw 0;
    }

    void TestViewModel::MyProperty(int32_t value)
    {
    }
}
