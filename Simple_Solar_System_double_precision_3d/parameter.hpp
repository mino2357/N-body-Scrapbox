#pragma once

using float_mp = double;

namespace mino2357 {
	constexpr size_t body = 10;
	constexpr size_t num = 6*body; // body [n]*3[dim]*2[pos, vel]
	constexpr size_t intv = 10000;
	auto max_dt = float_mp(4.0e-4);
	auto tol = float_mp(4.0e-11);
	auto dt = float_mp(1.0e-6);
	auto time = float_mp(0.0); // zero
}

