#pragma once

#include "TestViewModel.g.h"

namespace winrt::ZXamlIslands::implementation
{
    struct TestViewModel : TestViewModelT<TestViewModel>
    {
        TestViewModel() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::ZXamlIslands::factory_implementation
{
    struct TestViewModel : TestViewModelT<TestViewModel, implementation::TestViewModel>
    {
    };
}
