#include <iostream>
#include <iomanip>
#include <cmath>

template<class Real>
void test_nokahan()
{
    std::cout << std::setprecision(std::numeric_limits<Real>::digits10+4) << std::fixed;
    size_t k = 0;
    auto f = [&]()->Real { ++k; if (k < 2/(std::numeric_limits<Real>::epsilon())) { return 2;} return 1; };


    size_t max_k = (size_t) ceil(4.0/std::numeric_limits<Real>::epsilon());
    std::cout << max_k << std::endl;
    Real m = 0;
    size_t j = 1;
    while (j < max_k)
    {
        m += (f() - m)/j;
        ++j;
    }
    std::cout << "(No kahan) m = " << m << std::endl;
}

template<class Real>
void test_kahan()
{
    std::cout << std::setprecision(std::numeric_limits<Real>::digits10+4) << std::fixed;
    size_t k = 0;
    auto f = [&]()->Real { ++k; if (k < 2/(std::numeric_limits<Real>::epsilon())) { return 2;} return 1; };


    size_t max_k = (size_t) ceil(4.0/std::numeric_limits<Real>::epsilon());
    std::cout << max_k << std::endl;
    Real m = 0;
    Real e = 0;
    size_t j = 1;
    while (j < max_k)
    {
        Real temp = m;
        Real xi = ((f() - m))/j;
        Real y = xi + e;
        m = temp + y;
        e = (temp - m)  + y;
        ++j;
    }
    std::cout << "(Kahan): m = " << m << std::endl;
}

int main()
{
  test_nokahan<float>();
  test_kahan<float>();
}
