#include <iostream>
#include <iomanip>
#include <tuple>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "vector.hpp"
#include "parameter.hpp"
#include "ERK.hpp"

namespace mp = boost::multiprecision;

//          |  mass      |    r
//  Sun     |  1.0       |    0.0
//  Mercury |  1.660e-7  |    0.387
//  Venus   |  2.447e-6  |    0.723
//  Eeath   |  3.003e-6  |    1.000
//  Mars    |  3.226e-7  |    1.524
//  Jupiter |  9.543e-4  |    5.204
//  Saturn  |  2.857e-4  |    9.582
//  Uranus  |  4.365e-5  |   19.201
//  Neptune |  5.149e-5  |   30.047
//  X       |  1.000e-9  |  100.0
//
std::vector<float_mp> m = {
	float_mp("1.0"),
	float_mp("1.660e-7"),
	float_mp("2.447e-6"),
	float_mp("3.003e-6"),
	float_mp("3.226e-7"),
	float_mp("9.543e-4"),
	float_mp("2.857e-4"),
	float_mp("4.365e-5"),
	float_mp("5.149e-5"),
	float_mp("1.0e-9")
};

namespace mino2357 {
    // f: R^N -> R^N
    template <typename T>
    mino2357::vector<T> func(const mino2357::vector<T>& u){
        auto ret = u;
        auto num = u.vec.size();
	for(size_t i=0; i<num/2; ++i){
            ret.vec[i] = u.vec[i+num/2];
        }
        for(size_t i=num/2; i<num; i+=2){
            ret.vec[i] = float_mp("0.0");
            ret.vec[i+1] = float_mp("0.0");
            for(size_t j=num/2; j<num; j+=2){
                if(j!=i){
		    auto m_j = m[(j-num/2)/2];
                    auto x = u.vec[i-num/2] - u.vec[j-num/2];
                    auto y = u.vec[i+1-num/2] - u.vec[j+1-num/2];;
                    auto r = mp::sqrt(x*x + y*y);
                    ret.vec[i]   += - m_j * x / (r * r * r);
                    ret.vec[i+1] += - m_j * y / (r * r * r);
                }
            }
        }
        return ret;
    }
}


template <typename T>
std::tuple<T, T> eccentricity_vector(const T& pos_x, const T& pos_y, const T& vel_x, const T& vel_y){
        T r = mp::sqrt(pos_x * pos_x + pos_y * pos_y);
	T v = mp::sqrt(vel_x * vel_x + vel_y * vel_y);
	T mu = T("1.0");
	T rv = pos_x * vel_x + pos_y * vel_y;
	T ret_x = (v * v / mu - T("1.0") / r) * pos_x - (rv / mu) * vel_x;
	T ret_y = (v * v / mu - T("1.0") / r) * pos_y - (rv / mu) * vel_y;
	return {ret_x, ret_y};
}

template <typename T>
T angular_momentum(const mino2357::vector<T>& x){
	auto ret = T("0.0");
	for(size_t i=0; i<mino2357::num/2; i+=2){
		auto r_x = x.vec[i];
		auto r_y = x.vec[i+1];
		auto v_x = x.vec[i+mino2357::num/2];
		auto v_y = x.vec[i+mino2357::num/2+1];
		auto m_m   = m[i/2];
		ret += r_x * m_m * v_y - r_y * m_m * v_x;
	}
	return ret;
}

int main() {
	//std::cout << std::fixed << std::setprecision(std::numeric_limits<float_mp>::digits10 + 1);
	std::cerr << std::fixed << std::setprecision(20);
	std::cout << std::fixed << std::setprecision(20);

	mino2357::vector<float_mp> x(mino2357::num);

	// position
	x.vec[0]  = float_mp("0.0");
	x.vec[1]  = float_mp("0.0");
	x.vec[2]  = float_mp("0.387");
	x.vec[3]  = float_mp("0.0");
	x.vec[4]  = float_mp("0.723");
	x.vec[5]  = float_mp("0.0");
	x.vec[6]  = float_mp("1.0000");
	x.vec[7]  = float_mp("0.0");
	x.vec[8]  = float_mp("1.524");
	x.vec[9]  = float_mp("0.0");
	x.vec[10] = float_mp("5.204");
	x.vec[11] = float_mp("0.0");
	x.vec[12] = float_mp("9.582");
	x.vec[13] = float_mp("0.0");
	x.vec[14] = float_mp("19.201");
	x.vec[15] = float_mp("0.0");
	x.vec[16] = float_mp("30.047");
	x.vec[17] = float_mp("0.0");
	x.vec[18] = float_mp("100.0"); // X
	x.vec[19] = float_mp("0.0");
	// velocity
	x.vec[20] = float_mp("0.0");
	x.vec[21] = float_mp("0.0");
	x.vec[22] = float_mp("0.0");
	x.vec[23] = float_mp("1.0") / mp::sqrt(x.vec[2]);
	x.vec[24] = float_mp("0.0");
	x.vec[25] = float_mp("1.0") / mp::sqrt(x.vec[4]);
	x.vec[26] = float_mp("0.0");
	x.vec[27] = float_mp("1.0") / mp::sqrt(x.vec[6]);
	x.vec[28] = float_mp("0.0");
	x.vec[29] = float_mp("1.0") / mp::sqrt(x.vec[8]);
	x.vec[30] = float_mp("0.0");
	x.vec[31] = float_mp("1.0") / mp::sqrt(x.vec[10]);
	x.vec[32] = float_mp("0.0");
	x.vec[33] = float_mp("1.0") / mp::sqrt(x.vec[12]);
	x.vec[34] = float_mp("0.0");
	x.vec[35] = float_mp("1.0") / mp::sqrt(x.vec[14]);
	x.vec[36] = float_mp("0.0");
	x.vec[37] = float_mp("1.0") / mp::sqrt(x.vec[16]);
	x.vec[38] = float_mp("0.0"); // X
	x.vec[39] = float_mp("1.0") / mp::sqrt(x.vec[18]);

	mino2357::RKF78<float_mp> rkf78(mino2357::tol, mino2357::tol);

	for(;;){
		rkf78.Integrate(mino2357::time, mino2357::dt, x);
		if(mino2357::time > mino2357::write_time){
			// time dt
			//std::cerr << mino2357::time / (float_mp("2.0") * float_mp("3.141592653")) << " " << mino2357::dt / (float_mp("2.0") * float_mp("3.141592653")) << std::endl;
			// position
			std::cout << mino2357::time / (float_mp("2.0") * float_mp("3.141592653"));
			for(size_t i=0; i<mino2357::num/2; i+=2){
				std::cout << " " << x.vec[i] - x.vec[0] << " " << x.vec[i+1] - x.vec[1];
			}
			std::cout << std::endl;
			// eccentricity_vector
			std::cerr << mino2357::time / (float_mp("2.0") * float_mp("3.141592653"));
			for(size_t i=2; i<mino2357::num/2; i+=2){
				auto r_x = x.vec[i] - x.vec[0];
				auto r_y = x.vec[i+1] - x.vec[1];
				auto v_x = x.vec[i+mino2357::num/2] - x.vec[mino2357::num/2];
				auto v_y = x.vec[i+mino2357::num/2+1] - x.vec[mino2357::num/2+1];
				auto [e_x, e_y] = eccentricity_vector<float_mp>(r_x, r_y, v_x, v_y);
				std::cerr << " " << mp::sqrt(e_x * e_x + e_y * e_y);
			}
			std::cerr << " " << angular_momentum<float_mp>(x) - 0.00354046249445236011 << std::endl;

			mino2357::write_time = mino2357::time + mino2357::intv;
		}
		if(mino2357::time > mino2357::end_time) {
			break;
		}
	}
}
