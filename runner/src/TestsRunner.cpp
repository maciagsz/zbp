#include <runner/TestsRunner.hpp>
#include <runner/config/Config.hpp>

#include <zbp/poli_dynamic/ifc/IOperation.hpp>
#include <zbp/poli_dynamic/Addition.hpp>
#include <zbp/poli_dynamic/Hashing.hpp>

#include <zbp/poli_static/ifc/IOperation.hpp>
#include <zbp/poli_static/Addition.hpp>
#include <zbp/poli_static/Hashing.hpp>

#include <iostream>
#include <memory>
#include <cstdio>

#define ZBP_DBG_INFO
// #define ZBP_INIT_TAB

using namespace zbp;

TestsRunner::TestsRunner() : tab_a(std::make_unique<int[]>(config::size)),
                             tab_b(std::make_unique<int[]>(config::size)),
                             tab_result(std::make_unique<int[]>(config::size))
{
}

void TestsRunner::run()
{
#ifdef ZBP_DBG_INFO
    printf("%s: single tab size: %ld MB\n", __func__, config::size * sizeof(int) / (1024 * 1024));
#endif
#ifdef ZBP_INIT_TAB
    initTab(tab_a.get(), config::size);
    initTab(tab_b.get(), config::size);
    initTab(tab_result.get(), config::size, 0);
#endif

    auto duration_static = runDynamic();

#ifdef ZBP_INIT_TAB
    initTab(tab_result.get(), config::size, 0);
#endif

    auto duration_dynamic = runStatic();

    std::cout << "Performance ratio: " << static_cast<double>(duration_dynamic.count()) / static_cast<double>(duration_static.count()) << std::endl;
}

void TestsRunner::initTab(int *tab, int size, int val /* = -1 */)
{
    if (val == -1)
    {
        for (int i = 0; i < size; ++i)
        {
            tab[i] = i;
        }
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            tab[i] = val;
        }
    }
}

std::chrono::milliseconds TestsRunner::runDynamic()
{

    std::vector<std::shared_ptr<poli_dynamic::IOperation>> op_vec;
    op_vec.emplace_back(std::make_shared<poli_dynamic::Addition>());
    op_vec.emplace_back(std::make_shared<poli_dynamic::Hashing>());

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto &op : op_vec)
    {
        for (int i = 0; i < config::size; ++i)
        {
            tab_result[i] = op->execute(tab_a[i], tab_b[i]);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("%s: Execution time: %ld ms, (~%ld s)\n", __func__, duration.count(), duration.count() / 1000);
    return duration;
}

std::chrono::milliseconds TestsRunner::runStatic()
{
    poli_static::Addition a;
    poli_static::Hashing h;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < config::size; ++i)
    {
        tab_result[i] = a.execute(tab_a[i], tab_b[i]);
    }
    for (int i = 0; i < config::size; ++i)
    {
        tab_result[i] = h.execute(tab_a[i], tab_b[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("%s: Execution time: %ld ms (~%ld s)\n", __func__, duration.count(), duration.count() / 1000);
    return duration;
}
