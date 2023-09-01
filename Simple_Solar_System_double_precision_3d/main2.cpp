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
	float_mp(0.1307 / 19885000.0),
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
	x.vec[0]  = 0.0 / au; // sol
	x.vec[1]  = 0.0 / au;
	x.vec[2]  = 0.0 / au;
	x.vec[3]  = 4.749853696679540E+07 / au; // sui X = 4.749853696679540E+07 Y =-3.737724061730301E+07 Z =-7.411266476235436E+06
	x.vec[4]  = -3.737724061730301E+07 / au;
	x.vec[5]  = -7.411266476235436E+06 / au;
	x.vec[6]  = 1.067832390650615E+08 / au; // kinn X = 1.067832390650615E+08 Y =-1.974951870317106E+07 Z =-6.432625455056737E+06
	x.vec[7]  = -1.974951870317106E+07 / au;
	x.vec[8]  = -6.432625455056737E+06 / au;
	x.vec[9]  = 1.400066731258702E+08 / au; // ti X = 1.400066731258702E+08 Y =-5.656864340673850E+07 Z = 2.358117319162935E+03
	x.vec[10]  = -5.656864340673850E+07 / au;
	x.vec[11]  = 2.358117319162935E+03 / au;
	x.vec[12]  = -2.317149312291399E+08 / au; // ka X =-2.317149312291399E+08 Y =-7.301765439010516E+07 Z = 4.153589884319007E+06
	x.vec[13]  = -7.301765439010516E+07 / au;
	x.vec[14]  = 4.153589884319007E+06 / au;
	x.vec[15]  = 6.125858099714541E+08 / au; // moku X = 6.125858099714541E+08 Y = 4.198544407080007E+08 Z =-1.544953710371283E+07
	x.vec[16]  = 4.198544407080007E+08 / au;
	x.vec[17]  = -1.544953710371283E+07 / au;
	x.vec[18]  = 1.309454381823805E+09 / au; // do X = 1.309454381823805E+09 Y =-6.485533471689560E+08 Z =-4.083518400133377E+07
	x.vec[19]  = -6.485533471689560E+08 / au;
	x.vec[20]  = -4.083518400133377E+07 / au;
	x.vec[21]  = 1.891786630777107E+09 / au; // ten X = 1.891786630777107E+09 Y = 2.246534492281295E+09 Z =-1.618145404476953E+07
	x.vec[22]  = 2.246534492281295E+09 / au;
	x.vec[23]  = -1.618145404476953E+07 / au;
	x.vec[24]  = 4.461097261292484E+09 / au; // kai X = 4.461097261292484E+09 Y =-3.255589171394691E+08 Z =-9.610267007640028E+07
	x.vec[25]  = -3.255589171394691E+08 / au;
	x.vec[26]  = -9.610267007640028E+07 / au;
	x.vec[27]  = 2.523199306620363E+09 / au; // mei X = 2.523199306620363E+09 Y =-4.554189299791788E+09 Z =-2.421678207220302E+08
	x.vec[28]  = -4.554189299791788E+09 / au;
	x.vec[29]  = -2.421678207220302E+08 / au;
 
	// velocity [au/day]
	x.vec[30] = 0.0 / au; // sol
	x.vec[31] = 0.0 / au;
	x.vec[32] = 0.0 / au;
	x.vec[33] = 1.772352879533610E+06 / au / (2.0 * PI) * year; // sui VX= 1.772352879533610E+06 VY= 3.503420726740979E+06 VZ= 1.237342409601002E+05
	x.vec[34] = 3.503420726740979E+06 / au / (2.0 * PI) * year;
	x.vec[35] = 1.237342409601002E+05 / au / (2.0 * PI) * year;
	x.vec[36] = 5.355688919820316E+05 / au / (2.0 * PI) * year; // kinn VX= 5.355688919820316E+05 VY= 2.961698410495598E+06 VZ= 9.767588002410719E+03
	x.vec[37] = 2.961698410495598E+06 / au / (2.0 * PI) * year;
	x.vec[38] = 9.767588002410719E+03 / au / (2.0 * PI) * year;
	x.vec[39] = 9.220286795888582E+05 / au / (2.0 * PI) * year; // ti VX= 9.220286795888582E+05 VY= 2.375474361150964E+06 VZ=-2.180159483080331E+02
	x.vec[40] = 2.375474361150964E+06 / au / (2.0 * PI) * year;
	x.vec[41] = -2.180159483080331E+02 / au / (2.0 * PI) * year;
	x.vec[42] = 7.072649115996205E+05 / au / (2.0 * PI) * year; // ka VX= 7.072649115996205E+05 VY=-1.817932890099840E+06 VZ=-5.544867514259787E+04
	x.vec[43] = -1.817932890099840E+06 / au / (2.0 * PI) * year;
	x.vec[44] = -5.544867514259787E+04 / au / (2.0 * PI) * year;
	x.vec[45] = -6.520016889714854E+05 / au / (2.0 * PI) * year; // moku VX=-6.520016889714854E+05 VY= 9.852604412872446E+05 VZ= 1.049049729723986E+04
	x.vec[46] = 9.852604412872446E+05 / au / (2.0 * PI) * year;
	x.vec[47] = 1.049049729723986E+04 / au / (2.0 * PI) * year;
	x.vec[48] = 3.236801726147626E+05 / au / (2.0 * PI) * year; // do VX= 3.236801726147626E+05 VY= 7.473526635600305E+05 VZ=-2.592763479803463E+04
	x.vec[49] = 7.473526635600305E+05 / au / (2.0 * PI) * year;
	x.vec[50] = -2.592763479803463E+04 / au / (2.0 * PI) * year;
	x.vec[51] = -4.550220547965139E+05 / au / (2.0 * PI) * year; // ten VX=-4.550220547965139E+05 VY= 3.526668388808242E+05 VZ= 7.193044943207628E+03
	x.vec[52] = 3.526668388808242E+05 / au / (2.0 * PI) * year;
	x.vec[53] = 7.193044943207628E+03 / au / (2.0 * PI) * year;
	x.vec[54] = 3.057160253033973E+04 / au / (2.0 * PI) * year; // kai VX= 3.057160253033973E+04 VY= 4.723624786308346E+05 VZ=-1.040664801597096E+04
	x.vec[55] = 4.723624786308346E+05 / au / (2.0 * PI) * year;
	x.vec[56] = -1.040664801597096E+04 / au / (2.0 * PI) * year;
	x.vec[57] = 4.215862004260509E+05 / au / (2.0 * PI) * year; // mei VX= 4.215862004260509E+05 VY= 1.243989357680785E+05 VZ=-1.368765412288774E+05
	x.vec[58] = 1.243989357680785E+05 / au / (2.0 * PI) * year;
	x.vec[59] = -1.368765412288774E+05 / au / (2.0 * PI) * year;

	/*
	for(size_t i=0; i<mino2357::num/2; i+=3){
		auto r_x = x.vec[i];
		auto r_y = x.vec[i+1];
		auto r_z = x.vec[i+2];
		auto v_x = x.vec[i+mino2357::num/2];
		auto v_y = x.vec[i+1+mino2357::num/2];
		auto v_z = x.vec[i+2+mino2357::num/2];
		std::cout << sqrt(r_x*r_x + r_y*r_y + r_z*r_z) << " " << sqrt(v_x*v_x + v_y*v_y + v_z*v_z)  << std::endl;
		auto [e_x, e_y, e_z] = eccentricity_vector<float_mp>(r_x, r_y, r_z, v_x, v_y, v_z);
		std::cout << sqrt(e_x * e_x + e_y * e_y + e_z * e_z) << std::endl;
	}
	*/

	mino2357::RKF78<float_mp> rkf78(mino2357::tol, mino2357::tol);

	for(size_t i=0;;i++){
		rkf78.Integrate(mino2357::time, mino2357::dt, x);
		if(i%mino2357::intv == 0){
			// time
			std::cerr << mino2357::time / (float_mp(2.0) * float_mp(PI)) << std::endl; // (float_mp(2.0) * float_mp(PI));
			std::cout << mino2357::time / (float_mp(2.0) * float_mp(PI)) << " "; // (float_mp(2.0) * float_mp(PI));
			// eccentricity_vector
			for(size_t i=0; i<mino2357::num/2; i+=3){
				auto r_x = x.vec[i];
				auto r_y = x.vec[i+1];
				auto r_z = x.vec[i+2];
				//auto v_x = x.vec[i+mino2357::num/2];
				//auto v_y = x.vec[i+mino2357::num/2+1];
				//auto v_z = x.vec[i+mino2357::num/2+2];
				std::cout << r_x << " " << r_y << " " << r_z << " "; // << v_x << " " << v_y << " " << v_z;
				//auto [e_x, e_y, e_z] = eccentricity_vector<float_mp>(r_x, r_y, r_z, v_x, v_y, v_z);
				//std::cout << " " << sqrt(e_x * e_x + e_y * e_y + e_z * e_z);
			}
			std::cout << std::endl;
			//auto [l_x, l_y, l_z] = angular_momentum<float_mp>(x);
			//std::cout << " " << l_x << " " << l_y << " " << l_z << " " << sqrt(l_x*l_x+l_y*l_y+l_z*l_z) << std::endl;
			//for(size_t i=0; i<mino2357::num; i++){
			//	std::cerr << x.vec[i] << " ";
			//}
			//std::cerr << std::endl;
		}
	}
}
