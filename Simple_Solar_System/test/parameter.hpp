#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>

namespace mp = boost::multiprecision; // for sqrt

using float_mp = mp::number<mp::cpp_dec_float<50>>;

namespace mino2357 {
	template <typename T>
	constexpr T min_dt(){
		return static_cast<T>("1.0e-2");
	}
	constexpr size_t body = 10;
	constexpr size_t num = 4*body; // body [n]*2[dim]*2[pos, vel]
	auto tol = float_mp("1.0e-16");
	auto dt = float_mp("1.0e-6");
	auto intv = float_mp("2.7397e-2") * float_mp("2.0") * float_mp("3.1415"); // 1 day
	auto write_time = float_mp("0.1") * mino2357::min_dt<float_mp>();
	auto time = float_mp("0.0");
	auto end_time =  float_mp("16500.0") * float_mp(2.0) * float_mp("3.1415");
}

