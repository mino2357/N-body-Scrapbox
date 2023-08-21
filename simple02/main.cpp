//
// plot "log2.log" u 1:2 w l; replot "log2.log" u 3:4 w l; replot "log2.log" u 5:6 w l; replot "log2.log" u 7:8 w l; replot "log2.log" u 9:10 w l; replot "log2.log" u 11:12 w l; replot "log2.log" u 13:14 w l; replot "log2.log" u 15:16 w l; replot "log2.log" u 17:18 w l; replot "log2.log" u 19:20 w l; replot "log2.log" u 21:22 w l; replot "log2.log" u 23:24 w l; replot "log2.log" u 25:26 w l; replot "log2.log" u 27:28 w l; replot "log2.log" u 29:30 w l; replot "log2.log" u 31:32 w l; replot "log2.log" u 33:34 w l; replot "log2.log" u 35:36 w l; replot "log2.log" u 37:38 w l; replot "log2.log" u 39:40 w l; replot "log2.log" u 41:42 w l; replot "log2.log" u 43:44 w l; replot "log2.log" u 45:46 w l; replot "log2.log" u 47:48 w l; replot "log2.log" u 49:50 w l; replot "log2.log" u 51:52 w l; replot "log2.log" u 53:54 w l; replot "log2.log" u 55:56 w l; replot "log2.log" u 57:58 w l; replot "log2.log" u 59:60 w l; replot "log2.log" u 61:62 w l; replot "log2.log" u 63:64 w l
//

#include <iostream>
#include <iomanip>
#include <random>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "vector.hpp"
#include "ERK.hpp"

namespace mp = boost::multiprecision;

float_mp angular_momentum(mino2357::vector<float_mp>& x){
	auto L = float_mp("0.0");
	auto num = x.vec.size();
	for(size_t i=0; i<num/2; i+=2){
		L += x.vec[i] * x.vec[i+num/2+1] - x.vec[i+1] * x.vec[i+num/2];
	}
	return L;
}

int main() {
	//std::cout << std::fixed << std::setprecision(std::numeric_limits<float_mp>::digits10 + 1);
	std::cerr << std::fixed << std::setprecision(50);
	std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::digits10 + 1);

	size_t n = 32;
	size_t num = 4*n; // 3[n]*2[dim]*2[pos, vel]
	mino2357::vector<float_mp> x(num);

	unsigned int seed1 = 0;
	std::mt19937 mt(seed1);
	std::uniform_real_distribution<> rand01(-1.0, 1.0);

	for(size_t i=0; i<num/2; i++){
		x.vec[i] = static_cast<float_mp>(rand01(mt));;
	}

	auto zero = float_mp("0.0");
	for(size_t i=num/2; i<num; i+=2){
		x.vec[i] = zero;
		x.vec[i+1] = zero;
	}

	auto tol = float_mp("1.0e-6");
	auto dt = float_mp("1.0e-6");
	auto time = float_mp("0.0");
	auto end_time = float_mp("1.0e2");
	mino2357::RKF78<float_mp> rkf78(tol, tol);

	for(;;){
		rkf78.Integrate(time, dt, x);
		
		auto g_x = float_mp("0.0");
		auto g_y = float_mp("0.0");
		for(size_t i=0; i<num/2; i+=2){
			g_x += x.vec[i];
			g_y += x.vec[i+1];
		}
		std::cerr << time << " " << angular_momentum(x) << " " << g_x << " " << g_y << std::endl;
		
		
		for(size_t i=0; i<num/2; i++){
			std::cout << x.vec[i] << " ";
		}
		std::cout << std::endl;
		
		if(time > end_time) {
			break;
		}
	}
}
