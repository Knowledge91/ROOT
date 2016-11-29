#include "Minuit2/Minuit2Minimizer.h"
#include "Math/Functor.h"

double RosenBrock(const double *xx )
{
    const double_t x = xx[0];
    const double_t y = xx[1];
    const double_t tmp1 = y-x*x;
    const double_t tmp2 = 1-x;
    return 100*tmp1*tmp1+tmp2*tmp2;
}

int main()
{
    // Choose method upon creation between:
    // kMigrad, kSimplex, kCombined,
    // kScan, kFumili
    
    ROOT::Minuit2::Minuit2Minimizer min ( ROOT::Minuit2::kMigrad );
    
    min.SetMaxFunctionCalls(1000000);
    min.SetMaxIterations(100000);
    min.SetTolerance(0.001);
    
    ROOT::Math::Functor f(&RosenBrock,2);
    double step[2] = {0.01,0.01};
    double variable[2] = { -1.,1.2};
    
    min.SetFunction(f);
    
    // Set the free variables to be minimized!
    min.SetVariable(0,"x",variable[0], step[0]);
    min.SetVariable(1,"y",variable[1], step[1]);
    
    min.Minimize();
    
    const double *xs = min.X();
    std::cout << "Minimum: f(" << xs[0] << "," << xs[1] << "): "
    << RosenBrock(xs) << std::endl;
    
    return 0;
}
