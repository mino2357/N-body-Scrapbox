#include <iostream>
#include <iomanip>
#include <tuple>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "vector.hpp"
#include "parameter.hpp"
#include "ERK.hpp"

constexpr double PI=3.1415926535897932384626433832795028841971;

const std::vector<float_mp> m = {
	float_mp(1.0),
	float_mp(3.302 / 19885000.0),
	float_mp(48.685 / 19885000.0),
	float_mp(59.7219 / 19885000.0),
	float_mp(6.4171 / 19885000.0),
	float_mp(18981.8722 / 19885000.0),
	float_mp(5683.4 / 19885000.0),
	float_mp(868.13 / 19885000.0),
	float_mp(1024.09 / 19885000.0),
	float_mp(5.0289163e-18 / 19885000.0), // 10^13
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
        for(size_t i=num/2; i<num; i+=3){
            ret.vec[i] = float_mp(0.0);
            ret.vec[i+1] = float_mp(0.0);
			ret.vec[i+2] = float_mp(0.0);
            for(size_t j=num/2; j<num; j+=3){
                if(j!=i){
				    auto m_j = m[(j-num/2)/3];
                    auto x = u.vec[i-num/2] - u.vec[j-num/2];
                    auto y = u.vec[i+1-num/2] - u.vec[j+1-num/2];
					auto z = u.vec[i+2-num/2] - u.vec[j+2-num/2];
                    auto r = sqrt(x*x + y*y + z*z);
                    ret.vec[i]   += - m_j * x / (r * r * r);
                    ret.vec[i+1] += - m_j * y / (r * r * r);
		    		ret.vec[i+2] += - m_j * z / (r * r * r);
                }
            }
        }
        return ret;
    }
}


template <typename T>
inline std::tuple<T, T, T> eccentricity_vector(const T& pos_x, const T& pos_y, const T& pos_z, const T& vel_x, const T& vel_y, const T& vel_z) noexcept {
	T r = sqrt(pos_x * pos_x + pos_y * pos_y + pos_z * pos_z);
	T v = sqrt(vel_x * vel_x + vel_y * vel_y + vel_z * vel_z);
	T mu = T(1.0);
	T rv = pos_x * vel_x + pos_y * vel_y + pos_z * vel_z;
	T ret_x = (v * v / mu - T(1.0) / r) * pos_x - (rv / mu) * vel_x;
	T ret_y = (v * v / mu - T(1.0) / r) * pos_y - (rv / mu) * vel_y;
	T ret_z = (v * v / mu - T(1.0) / r) * pos_z - (rv / mu) * vel_z;
	return {ret_x, ret_y, ret_z};
}

template <typename T>
inline std::tuple<T, T, T> angular_momentum(const mino2357::vector<T>& x) noexcept {
	auto ret_x = T(0.0);
	auto ret_y = T(0.0);
	auto ret_z = T(0.0);
	for(size_t i=0; i<mino2357::num/2; i+=3){
		auto r_x = x.vec[i];
		auto r_y = x.vec[i+1];
		auto r_z = x.vec[i+2];
		auto v_x = x.vec[i+mino2357::num/2];
		auto v_y = x.vec[i+mino2357::num/2+1];
		auto v_z = x.vec[i+mino2357::num/2+2];
		auto m_m   = m[i/3];
		ret_x += r_y * m_m * v_z - r_z * m_m * v_y;
		ret_y += r_z * m_m * v_x - r_x * m_m * v_z;
		ret_z += r_x * m_m * v_y - r_y * m_m * v_x;
	}
	return {ret_x, ret_y, ret_z};
}

int main() {
	std::cout << std::fixed << std::setprecision(std::numeric_limits<float_mp>::digits10 + 1);
	std::cerr << std::fixed << std::setprecision(std::numeric_limits<float_mp>::digits10 + 1);

	mino2357::vector<float_mp> x(mino2357::num);
	
	auto au = 149597870.700; // [km]
	auto year = 365.25636; //365.24218944;

	// position
	x.vec[0] = 0.0 / au;
	x.vec[1] = 0.0 / au;
	x.vec[2] = 0.0 / au;
	x.vec[3] = -1.404774254690487E+07 / au;
	x.vec[4] = -6.825208888976701E+07 / au;
	x.vec[5] = -4.289153234359771E+06 / au;
	x.vec[6] = 4.608792459711022E+07 / au;
	x.vec[7] = -9.859187757812914E+07 / au;
	x.vec[8] = -4.013349395839728E+06 / au;
	x.vec[9] = 1.330220204950462E+08 / au;
	x.vec[10] = 6.704428213911822E+07 / au;
	x.vec[11] = -4.869615619417280E+03 / au;
	x.vec[12] = 6.649302608051282E+07 / au;
	x.vec[13] = 2.186169120955794E+08 / au;
	x.vec[14] = 2.950343934283048E+06 / au;
	x.vec[15] = 2.385041315415040E+08 / au;
	x.vec[16] = 7.182563535822021E+08 / au;
	x.vec[17] = -8.319703965834230E+06 / au;
	x.vec[18] = 1.406365269217089E+09 / au;
	x.vec[19] = -3.235355848531194E+08 / au;
	x.vec[20] = -5.034784972917840E+07 / au;
	x.vec[21] = 1.696652737323582E+09 / au;
	x.vec[22] = 2.385017003636673E+09 / au;
	x.vec[23] = -1.314104590030003E+07 / au;
	x.vec[24] = 4.469410600175806E+09 / au;
	x.vec[25] = -1.293917449213956E+08 / au;
	x.vec[26] = -1.003300431929548E+08 / au;
	x.vec[27] = 9.755484379394056E+07 / au;
	x.vec[28] = -5.078485333345367E+06 / au;
	x.vec[29] = 3.513104848711042E+07 / au;

	// velocity
	x.vec[30] = 0.0 / au;
	x.vec[31] = 0.0 / au;
	x.vec[32] = 0.0 / au;
	x.vec[33] = 3.277813191168440E+06 / au / (2.0 * PI) * year;
	x.vec[34] = -6.360278146631564E+05 / au / (2.0 * PI) * year;
	x.vec[35] = -3.526256010095223E+05 / au / (2.0 * PI) * year;
	x.vec[36] = 2.720842478216296E+06 / au / (2.0 * PI) * year;
	x.vec[37] = 1.271078843814805E+06 / au / (2.0 * PI) * year;
	x.vec[38] = -1.395383786068834E+05 / au / (2.0 * PI) * year;
	x.vec[39] = -1.199359489952496E+06 / au / (2.0 * PI) * year;
	x.vec[40] = 2.288045813113915E+06 / au / (2.0 * PI) * year;
	x.vec[41] = -1.848630523101974E+02 / au / (2.0 * PI) * year;
	x.vec[42] = -1.923719964482550E+06 / au / (2.0 * PI) * year;
	x.vec[43] = 7.871516467196010E+05 / au / (2.0 * PI) * year;
	x.vec[44] = 6.367679199693510E+04 / au / (2.0 * PI) * year;
	x.vec[45] = -1.085443281912170E+06 / au / (2.0 * PI) * year;
	x.vec[46] = 4.092938588278859E+05 / au / (2.0 * PI) * year;
	x.vec[47] = 2.258591609536928E+04 / au / (2.0 * PI) * year;
	x.vec[48] = 1.401829990042232E+05 / au / (2.0 * PI) * year;
	x.vec[49] = 8.122858624024559E+05 / au / (2.0 * PI) * year;
	x.vec[50] = -1.976963001796068E+04 / au / (2.0 * PI) * year;
	x.vec[51] = -4.848243855055465E+05 / au / (2.0 * PI) * year;
	x.vec[52] = 3.142563737252478E+05 / au / (2.0 * PI) * year;
	x.vec[53] = 7.456670936695803E+03 / au / (2.0 * PI) * year;
	x.vec[54] = 9.552707840392186E+03 / au / (2.0 * PI) * year;
	x.vec[55] = 4.728243111876977E+05 / au / (2.0 * PI) * year;
	x.vec[56] = -9.988672364090331E+03 / au / (2.0 * PI) * year;
	x.vec[57] = 1.913451980110258E+06 / au / (2.0 * PI) * year;
	x.vec[58] = -2.739124864901621E+06 / au / (2.0 * PI) * year;
	x.vec[59] = 2.814734584202529E+06 / au / (2.0 * PI) * year;

	mino2357::RKF78<float_mp> rkf78(mino2357::tol, mino2357::tol);

	for(size_t i=0;;i++){
		rkf78.Integrate(mino2357::time, mino2357::dt, x);
		if(i%mino2357::intv == 0){
			// time
			std::cerr << mino2357::time / (float_mp(2.0) * float_mp(PI)) << std::endl; // (float_mp(2.0) * float_mp(PI));
			std::cout << mino2357::time / (float_mp(2.0) * float_mp(PI)) << " "; // (float_mp(2.0) * float_mp(PI));
			// eccentricity_vector
			for(size_t i=0; i<mino2357::num/2; i+=3){
				auto r_x = x.vec[i] - x.vec[0];
				auto r_y = x.vec[i+1] - x.vec[1];
				auto r_z = x.vec[i+2] - x.vec[2];
				auto v_x = x.vec[i+mino2357::num/2];
				auto v_y = x.vec[i+mino2357::num/2+1];
				auto v_z = x.vec[i+mino2357::num/2+2];
				std::cout << " " << r_x << " " << r_y << " " << r_z << " " << v_x << " " << v_y << " " << v_z;
				auto [e_x, e_y, e_z] = eccentricity_vector<float_mp>(r_x, r_y, r_z, v_x, v_y, v_z);
				std::cout << " " << e_x << " " << e_y << " " << e_z << " " << sqrt(e_x * e_x + e_y * e_y + e_z * e_z);
			}
			auto [l_x, l_y, l_z] = angular_momentum<float_mp>(x);
			std::cout << " " << l_x << " " << l_y << " " << l_z << " " << sqrt(l_x*l_x+l_y*l_y+l_z*l_z) << std::endl;
		}
	}
}
