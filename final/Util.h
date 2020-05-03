#ifndef UTIL_H
#define UTIL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <random>
#include <vector>
#include <unordered_set>

#define PI 3.14159265359f
#define SEGMENT_X 8
#define SEGMENT_Y 8

#define DEFAULT_PARTICLE_NUMBER 10000

static const std::vector<glm::vec4> COLORS {
	glm::vec4{255 / 255.f, 0 / 255.f, 188 / 255.f, 1.f},
	glm::vec4{196 / 255.f, 0 / 255.f, 255 / 255.f, 1.f},
	glm::vec4{0 / 255.f, 77 / 255.f, 188 / 255.f, 1.f},
	glm::vec4{0 / 255.f, 162 / 255.f, 255 / 255.f, 1.f},
	glm::vec4{0 / 255.f, 255 / 255.f, 230 / 255.f, 1.f},
	glm::vec4{0 / 255.f, 255 / 255.f, 102 / 255.f, 1.f},
	glm::vec4{247 / 255.f, 255 / 255.f, 0 / 255.f, 1.f},
	glm::vec4{255 / 255.f, 0 / 255.f, 0 / 255.f, 1.f},
	glm::vec4{196 / 255.f, 255 / 255.f, 0 / 255.f, 1.f},
	glm::vec4{255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f},
};

static const std::unordered_set<int> FIREWORK_TIMES {
	0, 30, 100, 150, 290, 350, 400, 490, 526, 599, 649, 700, 720, 770, 841, 890, 910
};

static const float DELTA_T = .015f;

enum class FireworkType {
	FIREWORK_REGULAR,
	FIREWORK_CONE,
	FIREWORK_CYLINDER,
	FIREWORK_DISK
};

namespace Util {
	static auto Equal = [](const float num, const float target) -> bool {
		static float epsilon = (float)1e-10;
		return (target - epsilon < num) && (num < target + epsilon) ? true : false;
	};

	static auto LessOrEqual = [](const float num, const float target) -> bool {
		return num < target || Equal(num, target);
	};

	static auto GreaterOrEqual = [](const float num, const float target) -> bool {
		return num > target || Equal(num, target);
	};

	static auto RandFloat = [](const float LO, const float HI) -> float {
		return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	};

	static auto RandInt = [](const int min, const int max) ->int {
		return min + (rand() % static_cast<int>(max - min + 1));
	};

	static auto RandFireworkType = []() -> FireworkType {
		return static_cast<FireworkType>(RandInt(0, 3));
	};

	static auto RandColor = []() -> glm::vec4 {
		return COLORS[RandInt(0, 9)];
	};

	template<typename T>
	static auto Clamp = [](const T& target, const T& l, const T& h) -> T {
		if (target < l) return l;
		else if (target > h) return h;
		else return target;
	};

	static auto NormalDistributionGen = [](const float u, const float sigma, const float l, const float h) -> float {
		static std::default_random_engine generator;
		std::normal_distribution<float> distribution(u, sigma);
		float num;
		while(1) {
			num = distribution(generator);
			if (Util::LessOrEqual(l, num) && Util::LessOrEqual(num, h))
				break;
		}
		return num;
	};
}


#endif
