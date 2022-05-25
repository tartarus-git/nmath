#pragma once

#include "Vector3f.h"

namespace nmath {
	class Vector4f {
	public:
		float x;
		float y;
		float z;
		float w;

		constexpr Vector4f() = default;
		constexpr Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
		constexpr Vector4f(nmath::Vector3f baseVector, float w) : x(baseVector.x), y(baseVector.y), z(baseVector.z), w(w) { }
	};
}
