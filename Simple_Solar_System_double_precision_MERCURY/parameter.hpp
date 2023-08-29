#pragma once

using float_mp = double;

namespace mino2357 {
	constexpr size_t body = 9;
	constexpr size_t num = 4*body; // body [n]*2[dim]*2[pos, vel]
	constexpr size_t intv = 100;
	auto max_dt = float_mp(4.0e-4);
	auto tol = float_mp(4.0e-11);
	auto dt = float_mp(1.0e-6);
	auto write_time = float_mp(0.0); // zero
	auto time = float_mp(0.0); // zero
}

