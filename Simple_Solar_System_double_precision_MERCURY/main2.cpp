#include <iostream>
#include <iomanip>
#include <tuple>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "vector.hpp"
#include "parameter.hpp"
#include "ERK.hpp"

constexpr double PI=3.1415926535897932384626433832795028841971;

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
//  // X       |  1.000e-9  |  100.0
//

const std::vector<float_mp> m = {
	float_mp(1.0),
	float_mp(1.660e-7),
	float_mp(2.447e-6),
	float_mp(3.003e-6),
	float_mp(3.226e-7),
	float_mp(9.543e-4),
	float_mp(2.857e-4),
	float_mp(4.365e-5),
	float_mp(5.149e-5),
	//float_mp(1.0e-9)
};

namespace mino2357 {
    // f: R^N -> R^N
    template <typename T>
    inline mino2357::vector<T> func(const mino2357::vector<T>& u) noexcept {
        auto ret = u;
        auto num = u.vec.size();
	for(size_t i=0; i<num/2; ++i){
            ret.vec[i] = u.vec[i+num/2];
        }
        for(size_t i=num/2; i<num; i+=2){
            ret.vec[i] = float_mp(0.0);
            ret.vec[i+1] = float_mp(0.0);
            for(size_t j=num/2; j<num; j+=2){
                if(j!=i){
		    auto m_j = m[(j-num/2)/2];
                    auto x = u.vec[i-num/2] - u.vec[j-num/2];
                    auto y = u.vec[i+1-num/2] - u.vec[j+1-num/2];;
                    auto r = sqrt(x*x + y*y);
                    ret.vec[i]   += - m_j * x / (r * r * r);
                    ret.vec[i+1] += - m_j * y / (r * r * r);
                }
            }
        }
        return ret;
    }
}


template <typename T>
inline std::tuple<T, T> eccentricity_vector(const T& pos_x, const T& pos_y, const T& vel_x, const T& vel_y) noexcept {
        T r = sqrt(pos_x * pos_x + pos_y * pos_y);
	T v = sqrt(vel_x * vel_x + vel_y * vel_y);
	T mu = T(1.0);
	T rv = pos_x * vel_x + pos_y * vel_y;
	T ret_x = (v * v / mu - T(1.0) / r) * pos_x - (rv / mu) * vel_x;
	T ret_y = (v * v / mu - T(1.0) / r) * pos_y - (rv / mu) * vel_y;
	return {ret_x, ret_y};
}

template <typename T>
inline T angular_momentum(const mino2357::vector<T>& x) noexcept {
	auto ret = T(0.0);
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
	std::cout << std::fixed << std::setprecision(std::numeric_limits<float_mp>::digits10 + 1);
	std::cerr << std::fixed << std::setprecision(std::numeric_limits<float_mp>::digits10 + 1);

	mino2357::vector<float_mp> x(mino2357::num);

	// position
	x.vec[0]  = 0.0074398765048238;
	x.vec[1]  = 1276.6077709874462016-1276.6077709874462016;
	x.vec[2]  = 0.2499759936913019;
	x.vec[3]  = 1276.3066954216913018-1276.6077709874462016;
	x.vec[4]  = 0.7271321705317847;
	x.vec[5]  = 1276.5385237578025226-1276.6077709874462016;
	x.vec[6]  = 0.2631495377279227;
	x.vec[7]  = 1277.5744188752410082-1276.6077709874462016;
	x.vec[8]  = 1.4888682816335364;
	x.vec[9]  = 1276.9633266707101029-1276.6077709874462016;
	x.vec[10] = 3.9452556448896270;
	x.vec[11] = 1273.2279515204595555-1276.6077709874462016;
	x.vec[12] = -6.9940828839135039;
	x.vec[13] = 1283.0655807505449957-1276.6077709874462016;
	x.vec[14] = -14.3347275745383183;
	x.vec[15] = 1264.0509505305199127-1276.6077709874462016;
	x.vec[16] = 29.3322884234699899;
	x.vec[17] = 1271.0493297143764266-1276.6077709874462016;
	// velocity
	x.vec[18] = -0.0002167886536899;
	x.vec[19] = 0.0002805692567873-0.0002805692567873;
	x.vec[20] = 1.2581649881840380;
	x.vec[21] = 1.0030804449583404-0.0002805692567873;
	x.vec[22] = 0.1125031375554474;
	x.vec[23] = 1.1708874467951029-0.0002805692567873;
	x.vec[24] = -0.9669702351836751;
	x.vec[25] = 0.2563614096027937-0.0002805692567873;
	x.vec[26] = -0.1897792993285236;
	x.vec[27] = 0.7880671993199786-0.0002805692567873;
	x.vec[28] = 0.2867408525432656;
	x.vec[29] = 0.3332202844588128-0.0002805692567873;
	x.vec[30] = -0.2196827576200676;
	x.vec[31] = -0.2379240754311144-0.0002805692567873;
	x.vec[32] = 0.1503977113592879;
	x.vec[33] = -0.1725109220249797-0.0002805692567873;
	x.vec[34] = 0.0355650749990056;
	x.vec[35] = 0.1801304702798814-0.0002805692567873;

	mino2357::RKF78<float_mp> rkf78(mino2357::tol, mino2357::tol);
	auto a_m_init = angular_momentum<float_mp>(x);
	auto orbital_period = pow(x.vec[2], 1.5);

	for(size_t i=0;;i++){
		rkf78.Integrate(mino2357::time, mino2357::dt, x);
		if(i%mino2357::intv == 0){
			// position
			std::cout << mino2357::time / (float_mp(2.0) * float_mp(PI)) << " " << mino2357::time / (float_mp(2.0) * float_mp(PI)) / orbital_period; // (float_mp(2.0) * float_mp(PI));
			auto r_x = x.vec[2] - x.vec[0];
			auto r_y = x.vec[3] - x.vec[1];
			auto mag_r = sqrt(r_x * r_x + r_y * r_y);
			std::cout << " " << r_x << " " << r_y << " " << mag_r;
			// velocity
			auto v_x = x.vec[2+mino2357::num/2] - x.vec[0+mino2357::num/2];
			auto v_y = x.vec[3+mino2357::num/2] - x.vec[1+mino2357::num/2];
			std::cout << " " << v_x << " " << v_y << " " << sqrt(v_x * v_x + v_y * v_y);
			// eccentricity_vector
			std::cout << mino2357::time / (float_mp(2.0) * float_mp(PI));
			for(size_t i=2; i<3; i+=2){
				auto r_x = x.vec[i] - x.vec[0];
				auto r_y = x.vec[i+1] - x.vec[1];
				auto v_x = x.vec[i+mino2357::num/2] - x.vec[mino2357::num/2];
				auto v_y = x.vec[i+mino2357::num/2+1] - x.vec[mino2357::num/2+1];
				auto [e_x, e_y] = eccentricity_vector<float_mp>(r_x, r_y, v_x, v_y);
				std::cout << " " << sqrt(e_x * e_x + e_y * e_y);
			}
			std::cout << " " << pow(mag_r, 1.5);
			std::cout << " " << abs((angular_momentum<float_mp>(x) - a_m_init)) << std::endl;
			for(size_t i=0; i<mino2357::num; i++){
				std::cerr << x.vec[i] << " ";
			}
			std::cerr << std::endl;
		}
	}
}
