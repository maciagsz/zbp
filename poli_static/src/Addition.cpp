#include <zbp/poli_static/ifc/IOperation.hpp>
#include <zbp/poli_static/Addition.hpp>

using namespace zbp::poli_static;

int Addition::execute_impl(int a, int b)
{
    return a + b;
}
