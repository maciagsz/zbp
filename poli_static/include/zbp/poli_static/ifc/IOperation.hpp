#pragma once

namespace zbp::poli_static
{
    template <typename Derived>
    class IOperation
    {
    public:
        int execute(int a, int b)
        {
            return static_cast<Derived *>(this)->execute_impl(a, b);
        }
    };

} // namespace zbp::poli_static
