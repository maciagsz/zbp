#include <zbp/poli_dynamic/ifc/IOperation.hpp>
#include <zbp/poli_dynamic/Addition.hpp>

#include <zbp/poli_static/ifc/IOperation.hpp>
#include <zbp/poli_static/Addition.hpp>

#include <iostream>
#include <memory>
#include <chrono>

namespace config
{
    constexpr int size = INT_MAX;
}

void initTab(int *tab, int size, int val = -1)
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

int main()
{
    std::unique_ptr<int[]> tab_a = std::make_unique<int[]>(config::size);
    std::unique_ptr<int[]> tab_b = std::make_unique<int[]>(config::size);
    std::unique_ptr<int[]> tab_result = std::make_unique<int[]>(config::size);

    initTab(tab_a.get(), config::size);
    initTab(tab_b.get(), config::size);
    initTab(tab_result.get(), config::size, 0);

    std::shared_ptr<zbp::poli_dynamic::IOperation> dyn_op;
    dyn_op = std::make_shared<zbp::poli_dynamic::Addition>();

    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < config::size; ++i)
    {
        tab_result[i] = dyn_op->execute(tab_a[i], tab_b[i]);
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration_dynamic = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "DYNAMIC Execution time: " << duration_dynamic.count() << " ms" << std::endl;

    initTab(tab_result.get(), config::size, 0);

    zbp::poli_static::Addition static_add;
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < config::size; ++i)
    {
        tab_result[i] = static_add.execute(tab_a[i], tab_b[i]);
    }
    end_time = std::chrono::high_resolution_clock::now();

    auto duration_static = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "STATIC Execution time: " << duration_static.count() << " ms" << std::endl;

    std::cout << "Performance ratio: " << (static_cast<double>(duration_dynamic.count()) / static_cast<double>(duration_static.count())) << std::endl;

    return 0;
}
