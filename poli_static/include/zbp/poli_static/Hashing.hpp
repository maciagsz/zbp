#pragma once

#include <zbp/poli_static/ifc/IOperation.hpp>

namespace zbp::poli_static
{
    class Hashing : public IOperation<Hashing>
    {
    public:
        int execute_impl(int a, int b);
    };

} // namespace zbp::poli_static
