#pragma once

#include <zbp/poli_dynamic/ifc/IOperation.hpp>

namespace zbp::poli_dynamic
{
    class Addition : public IOperation
    {
    public:
        ~Addition() override = default;
        int execute(int a, int b) override;
    };

} // namespace zbp::poli_dynamic
