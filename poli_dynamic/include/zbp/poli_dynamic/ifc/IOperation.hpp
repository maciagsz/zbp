#pragma once

namespace zbp::poli_dynamic
{
    class IOperation
    {
    public:
        virtual ~IOperation() = default;

        virtual int execute(int a, int b) = 0;
    };

} // namespace zbp::poli_dynamic
