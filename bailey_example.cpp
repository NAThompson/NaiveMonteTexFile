#include <iostream>
#include <iomanip>
#include <boost/math/quadrature/naive_monte_carlo.hpp>

void display_progress(double progress,
                      double error_estimate,
                      double current_estimate,
                      std::chrono::duration<double> estimated_time_to_completion)
{
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] "
              << int(progress * 100.0)
              << "%, E = "
              << std::setprecision(3)
              << error_estimate
              << ", time to completion: "
              << estimated_time_to_completion.count()
              << " seconds, estimate: "
              << std::setprecision(5)
              << current_estimate
              << "     \r";

    std::cout.flush();
}


using boost::math::quadrature::naive_monte_carlo;

template<class Real>
void calcE2()
{
    auto f = [](std::vector<Real> const & x)
    {
        return (2*std::sqrt(x[0]*x[0] + x[1]*x[1]) + std::sqrt(1+(x[0] - x[1])*(x[0]-x[1])))/3;
    };
    std::vector<std::pair<Real, Real>> bounds{{0.0, 1.0}, {0.0, 1.0}};
    Real error_goal = 0.000001;
    naive_monte_carlo<Real, decltype(f)> mc(f, bounds, error_goal, false, 2);
    auto task = mc.integrate();
    while (task.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
    {
        display_progress(mc.progress(),
                         mc.current_error_estimate(),
                         mc.current_estimate(),
                         mc.estimated_time_to_completion());
    }
    std::cout << std::endl;

    Real E2 = task.get();
    std::cout << std::setprecision(std::numeric_limits<Real>::digits10+2);
    std::cout << "E_2 (estimated) = " << E2 << std::endl;
    Real exact = 0.86900905527453446388497059;
    std::cout << "E_2 (exact)     = " << exact << std::endl;
    std::cout << "Error      = " << E2 - exact << std::endl;
    std::cout << "Error goal = " << error_goal << std::endl;
}

template<class Real>
void calc_pi()
{
    auto f = [](std::vector<Real> const & x)->Real
    {
        Real r = x[0]*x[0] + x[1]*x[1];
        if (r <= 1) {
          return 4;
        }
        return 0;
    };
    std::vector<std::pair<Real, Real>> bounds{{0.0, 1.0}, {0.0, 1.0}};
    Real error_goal = 0.00001;
    naive_monte_carlo<Real, decltype(f)> mc(f, bounds, error_goal, false, 2);
    auto task = mc.integrate();
    while (task.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
    {
        display_progress(mc.progress(),
                         mc.current_error_estimate(),
                         mc.current_estimate(),
                         mc.estimated_time_to_completion());
    }
    std::cout << std::endl;

    Real E2 = task.get();
    std::cout << std::setprecision(std::numeric_limits<Real>::digits10+2);
    std::cout << "E_2 (estimated) = " << E2 << std::endl;
    Real exact = 3.1415926535897932384626433;
    std::cout << "E_2 (exact)     = " << exact << std::endl;
    std::cout << "Error      = " << E2 - exact << std::endl;
    std::cout << "Error goal = " << error_goal << std::endl;
}


template<class Real>
void calc_close_to_avg()
{
    auto f = [](std::vector<Real> const & x)->Real
    {
        Real r = 100*std::numeric_limits<Real>::epsilon()*std::sin(2*M_PI*10*x[0]);
        return r;
    };
    std::vector<std::pair<Real, Real>> bounds{{0.0, 1.0}};
    Real error_goal = 0.0000000001;
    naive_monte_carlo<Real, decltype(f)> mc(f, bounds, error_goal, false);
    auto task = mc.integrate();
    while (task.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
    {
        display_progress(mc.progress(),
                         mc.current_error_estimate(),
                         mc.current_estimate(),
                         mc.estimated_time_to_completion());
    }
    std::cout << std::endl;

    Real E2 = task.get();
    std::cout << std::setprecision(std::numeric_limits<Real>::digits10+2);
    std::cout << "E_2 (estimated) = " << E2 << std::endl;
    Real exact = 1.0;
    std::cout << "E_2 (exact)     = " << exact << std::endl;
    std::cout << "Error      = " << E2 - exact << std::endl;
    std::cout << "Error goal = " << error_goal << std::endl;
    std::cout << "Calls" << mc.calls() << std::endl;
}

int main()
{
  //calcE2<double>();
  //calcE2<float>();
  //calc_pi<float>();
  calc_close_to_avg<float>();
}
