#include <iostream>
#include <string>

#include "ParabolicValley.hpp"
#include "QuarticFunction.hpp"
#include "BealesFunction.hpp"

int main()
{
    const std::string tab = "   ";
    std::cout << "DOWNHILL-SIMPLEX-METHOD" << std::endl;
    std::cout << std::endl;

    std::cout << tab << "Parabolic Valley:" << std::endl;
    ParabolicValley pv;
    pv.optimize( ParabolicValley::ParamsT( -1.2, 1 ) );
    std::cout << tab << tab << pv.getResultIterations() << "/" << pv.getMaximumIterations() << " iterations" << std::endl;
    std::cout << tab << tab << pv.getResultError() << "/" << pv.getEpsilon() << " epsilon" << std::endl;
    std::cout << tab << tab << "Result: " << pv.getResultParams() << std::endl;

    std::cout << std::endl;

    std::cout << tab << "Beale's Function:" << std::endl;
    BealesFunction bf = BealesFunction();
    bf.optimize( BealesFunction::ParamsT( 1, 1 ) );
    std::cout << tab << tab << bf.getResultIterations() << "/" << bf.getMaximumIterations() << " iterations" << std::endl;
    std::cout << tab << tab << bf.getResultError() << "/" << bf.getEpsilon() << " epsilon" << std::endl;
    std::cout << tab << tab << "Result: " << bf.getResultParams() << std::endl;

    std::cout << std::endl;

    std::cout << tab << "Quartic Function:" << std::endl;
    QuarticFunction qf;
    qf.optimize( QuarticFunction::ParamsT( 3, -1, 0, 1 ) );
    std::cout << tab << tab << qf.getResultIterations() << "/" << qf.getMaximumIterations() << " iterations" << std::endl;
    std::cout << tab << tab << qf.getResultError() << "/" << qf.getEpsilon() << " epsilon" << std::endl;
    std::cout << tab << tab << "Result: " << qf.getResultParams() << std::endl;

    return 0;
}
