#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "vector.hpp"
#include "ERK.hpp"

namespace mp = boost::multiprecision;

int main() {
    std::cout << std::fixed << std::setprecision(std::numeric_limits<mp::cpp_dec_float_100>::digits10 + 1);

	mino2357::vector<mp::cpp_dec_float_100> a(100);

	a.vec[1]= mp::cpp_dec_float_100("1.00");

	auto tol = mp::cpp_dec_float_100("1.0e-12");
	auto dt = mp::cpp_dec_float_100("1.0e-6");
	auto time = mp::cpp_dec_float_100("0.0");
	auto end_time = mp::cpp_dec_float_100("1.0e2");
	mino2357::RKF78<mp::cpp_dec_float_100> rkf78(tol, tol);

	for(;;){
		std::cout /*<< dt << " "*/ << time << " " << mp::log10(mp::abs(a.vec[1] - mp::cos(time))) << std::endl;
		rkf78.Integrate(time, dt, a);
		if(time > end_time) {
			break;
		}
	}

	std::cout << time << " " << a.vec[1] << std::endl;
}
