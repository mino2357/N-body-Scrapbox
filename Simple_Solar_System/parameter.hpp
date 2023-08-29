#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>

namespace mp = boost::multiprecision; // for sqrt

using float_mp = mp::number<mp::cpp_dec_float<24>>;

namespace mino2357 {
	constexpr size_t body = 9;
	constexpr size_t num = 4*body; // body [n]*2[dim]*2[pos, vel]
	auto max_dt = float_mp("2.0e-1");
	auto tol = float_mp("1.0e-10");
	auto dt = float_mp("1.0e-6");
	auto intv = float_mp("1.0") * float_mp("2.0") * float_mp("3.1415"); // x * 1 day
	auto write_time = float_mp("0.0"); // zero
	auto time = float_mp("0.0"); // zero
	auto end_time =  float_mp("10000000000.0") * float_mp(2.0) * float_mp("3.1415");
}

