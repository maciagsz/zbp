#pragma once

#include <memory>
#include <chrono>

namespace zbp
{
    class TestsRunner
    {
    public:
        TestsRunner();
        void run();

    private:
        std::unique_ptr<int[]> tab_a;
        std::unique_ptr<int[]> tab_b;
        std::unique_ptr<int[]> tab_result;

        void initTab(int *tab, int size, int val = -1);

        inline std::chrono::milliseconds runDynamic();
        inline std::chrono::milliseconds runStatic();
    };

} // !namespace zbp
