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
		uint_t cielRoot = integer_sqrt(input) + 1;
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
			result.insert(result.end(), highResult.begin(), highResult.end());
			return result;
		}
		result.reserve(lowResult.size() + highResult.size());
		result.insert(result.end(), lowResult.begin(), lowResult.end());
		result.insert(result.end(), highResult.begin(), highResult.end());
		return result;
	}

	template <typename uint_t>
	constexpr std::pair<uint_t, uint_t> calcSmallestBoundingBox(uint_t area) {
		static_assert(std::is_unsigned<uint_t>{}, "calcSmallestBoundingBox failed: area must be of unsigned integral type");
		std::vector<uint_t> sortedFactors = calcSortedIntFactorsOf(area);
		// TODO: If the square root inside calcSortedIntFactorsOf turns out round, you can just return it as width and height. You're going to have to rewrite a lot of code and not do this function call inside here, or else you won't be able to get the data.
		uint_t length = sortedFactors.size();
		uint_t middle = length / 2;
		uint_t width = sortedFactors[middle];
		if (length % 2 == 0) { return std::make_pair(width, sortedFactors[middle + 1]); }			// TODO: This check will be unnecessary since it will always be even if you reimplement the other code here. This will happen because you can join the high and low list while potentially repeating the middle thing. So always even. Is better.
		return std::make_pair(width, width);
	}
}