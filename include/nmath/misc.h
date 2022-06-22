#include <type_traits>
#include <vector>

namespace nmath {
	template <typename uint_t>
	constexpr uint_t integer_sqrt(uint_t input) {			// TODO: Is this the most efficient algorithm. Has to be good since it could run at runtime as well.
		static_assert(std::is_unsigned<uint_t>{}, "integer_sqrt failed: input must be of unsigned integral type");
		uint_t spanStartIndex = 0;
		uint_t spanLengthMinusOne = input;
		while (true) {
			spanLengthMinusOne /= 2;
			if (spanLengthMinusOne == 0) { return spanStartIndex; }
			uint_t half = spanStartIndex + spanLengthMinusOne;
			uint_t squareHalf = half * half;
			if (squareHalf > input) { spanLengthMinusOne--; continue; }
			if (squareHalf < input) { spanStartIndex = half; continue; }
			return half;
		}
	}

	template <typename uint_t>
	constexpr std::vector<uint_t> calcIntFactorsOf(uint_t input) {			// TODO: Does there exist a better way.
		static_assert(std::is_integral<uint_t>{}, "calcIntFactorsOf failed: input must be of unsigned integral type");
		uint_t cielRoot = integer_sqrt(input) + 1;			// TODO: I don't really understand why this must be + 1 here.
		std::vector<uint_t> result;
		for (uint_t i = 0; i < cielRoot; i++) {
			if (input % i == 0) {
				result.push_back(i);
				result.push_back(input / i);
			}
		}
		return result;
	}

	template <typename uint_t>
	constexpr std::vector<uint_t> calcSortedIntFactorsOf(uint_t input) {
		static_assert(std::is_integral<uint_t>{}, "calcSortedIntFactorsOf failed: input must be of unsigned integral type");
		uint_t cielRoot = integer_sqrt(input) + 1;
		std::vector<uint_t> lowResult;
		std::vector<uint_t> highResult;
		for (uint_t i = 0; i < cielRoot; i++) {
			if (input % i == 0) {
				lowResult.push_back(i);
				highResult.push_back(input / i);
			}
		}
		std::vector<uint_t> result;
		if (lowResult.back() == highResult.front()) {
			result.reserve(lowResult.size() - 1 + highResult.size());
			result.insert(result.end(), lowResult.begin(), lowResult.end() - 1);
			result.insert(result.end(), highResult.rbegin(), highResult.rend());
			return result;
		}
		result.reserve(lowResult.size() + highResult.size());
		result.insert(result.end(), lowResult.begin(), lowResult.end());
		result.insert(result.end(), highResult.rbegin(), highResult.rend());
		return result;
	}

	template <typename uint_t>
	constexpr std::pair<uint_t, uint_t> calcSmallestBoundingBox(uint_t area) {
		static_assert(std::is_unsigned<uint_t>{}, "calcSmallestBoundingBox failed: area must be of unsigned integral type");
		uint_t cielRoot = integer_sqrt(area);
		for (uint_t i = cielRoot; i >= 2; i--) {
			if (area % i == 0) {
				return std::make_pair(i, area / i);
			}
		}
		return std::make_pair(1, area);
	}
}