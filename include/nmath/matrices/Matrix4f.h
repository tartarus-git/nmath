#pragma once

#include "../vectors/Vector3f.h"

#include <cstdint>

namespace nmath {
	// SIDE-NOTE: Just so you remember, normal functions and normal (non-const and non-constexpr and non-static and non-inline) global variables have external linkage.
	// With variables, you have to use "extern" keyword to link to them from somewhere else though, because declaring the variable like you would a function header actually initializes it
	// instead of just telling the compiler that it should link to the variable. extern solves this issue.
	// That basically means declaring global variables in headers causes multiple definition errors unless you use extern on some of them.
	// Obviously you can use static or inline to fix the issue as well, which one you use depends on your situation.

	class Matrix4f {
	public:
		float data[16];

		constexpr float& operator()(uint8_t x, uint8_t y) { return data[y * 4 + x]; }
		constexpr float& operator[](uint8_t i) { return data[i]; }

		/*
	
		NOTE: It is recommended by Visual Studio and the C++ community in general (I think it may also be in some guidelines document somewhere, idk), that you put noexcept on your move constructors and move assignment operators. The reason is pretty dumb.
		It's harder to recover from a failed move because the objects are in weird states. Like when you resize a vector and it moves the objects from one list into another, bigger list. If a move operator fails in that case, half the list is going to be moved (that isn't a big problem, you could theoretically move them back) and the
		other half isn't (also not the main problem). The problem is whatever object you were currently working on while the move operator threw. It'll be half moved and half unmoved, which std::vector has no way of recovering from. That means the new list and the old list are in invalid states and your std::vector is messed up.
		The way std::vector solves this is by using move_if_noexcept, which only moves if you've declared your move operators to be noexcept (noexcept --> doesn't throw, or terminates the program if an exception is thrown inside the function). If not, it copies, giving the user a potentially huge performance hit.
		The way this should have been done in my opinion is not at all. If your vector is messed up after throwing in a move operator, then so be it. Anyone who cares about that will make their move operators throw after setting the object back to a usable, completely fine state.
		It shouldn't be std::vector's responsibility to deal with the users suboptimal code.
		If your not using your class in a vector-like thing then this doesn't matter, I guess you wouldn't have to put noexcept on it.

		*/

		constexpr Matrix4f operator*(Matrix4f& other) noexcept {
			Matrix4f result;
			for (uint8_t y = 0; y < 16; y += 4) {
				for (uint8_t x = 0; x < 4; x++) {
					result[y + x] = (*this)[y] * other(x, 0) + (*this)[y + 1] * other(x, 1) + (*this)[y + 2] * other(x, 2) + (*this)[y + 3] * other(x, 3);
				}
			}
			return result;
		}

		static Matrix4f createRotation(float x, float y, float z) noexcept;			// NOTE: Can't be constexpr because built-in trig functions are not constexpr. You could use if consteval or something inside the body to use custom made, constexpr trig functions at compile time. TODO
		static Matrix4f createRotation(nmath::Vector3f rot) noexcept;
	};
}
