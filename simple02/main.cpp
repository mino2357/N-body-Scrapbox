#include <iostream>
#include <iomanip>
#include <random>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "vector.hpp"
#include "ERK.hpp"

namespace mp = boost::multiprecision;

int main() {
    	//std::cout << std::fixed << std::setprecision(std::numeric_limits<mp::cpp_dec_float_100>::digits10 + 1);
    	std::cerr << std::fixed << std::setprecision(30);
	std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::digits10 + 1);

	size_t n = 100;
	size_t num = 4*n; // 3[n]*2[dim]*2[pos, vel]
	mino2357::vector<mp::cpp_dec_float_100> x(num);

	unsigned int seed1 = 0;
	std::mt19937 mt(seed1);
	std::uniform_real_distribution<> rand01(-1.0, 1.0);

	for(size_t i=0; i<num/2; i++){
		x.vec[i] = static_cast<mp::cpp_dec_float_50>(rand01(mt));;
	}

	auto vel =  mp::cpp_dec_float_100("0.0");
	for(size_t i=num/2; i<num; i+=2){
		x.vec[i] = - vel * x.vec[i+1-num/2];
		x.vec[i+1] = vel * x.vec[i-num/2];
	}

	auto tol = mp::cpp_dec_float_100("1.0e-12");
	auto dt = mp::cpp_dec_float_100("1.0e-6");
	auto time = mp::cpp_dec_float_100("0.0");
	auto end_time = mp::cpp_dec_float_100("1.0e2");
	mino2357::RKF78<mp::cpp_dec_float_100> rkf78(tol, tol);

	for(;;){
		rkf78.Integrate(time, dt, x);
		
		auto g_x = mp::cpp_dec_float_100("0.0");
		auto g_y = mp::cpp_dec_float_100("0.0");
		for(size_t i=0; i<6; i+=2){
			g_x += x.vec[i];
			g_y += x.vec[i+1];
		}
		std::cerr << time << " " << g_x << " " << g_y << std::endl;
		
		
		for(size_t i=0; i<num/2; i++){
			std::cout << x.vec[i] << " ";
		}
		std::cout << std::endl;
		
		if(time > end_time) {
			break;
		}
	}
}
