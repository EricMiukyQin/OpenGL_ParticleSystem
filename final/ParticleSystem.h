#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Util.h"
#include "Sphere.h"

struct FireworkParticle {
	FireworkParticle(float lifespan = 0.f, float decay = 0.f, const glm::vec4& color = glm::vec4{ 1.f, 1.f, 1.f, 1.f })
		: lifespan{ lifespan }, decay{ decay } {
		sphere = new Sphere(color);
	}
	~FireworkParticle() { delete sphere; }

	Sphere* sphere;									  // shape
	glm::vec3 position = glm::vec3{ 0.f, 0.f, 0.f };  // object space position
	glm::vec3 velocity = glm::vec3{ 0.f, 100.f * Util::NormalDistributionGen(1.f, .075f, 0.f, 1.f), 0.f };
	float gravity = -9.8f;
	float lifespan;
	float decay;									  // decay speed of lifetime
};

template<typename ParticleType>
class ParticleSystem {
public:
	ParticleSystem(const glm::vec3& trans, const glm::vec3& scale, const int particleNumber = DEFAULT_PARTICLE_NUMBER)
		: trans{ trans }, scale{ scale }, mParticleNumber(particleNumber)
	{}

	virtual ~ParticleSystem() {
		for (int i = 0; i < mParticlePool.size(); ++i)
			delete mParticlePool[i];
		typename std::vector<ParticleType*>().swap(mParticlePool);
	}

	void Render() {
		for (int i = 0; i < mParticleNumber; ++i) {
			if (Util::LessOrEqual(mParticlePool[i]->lifespan, 0.f))
				continue;
			RenderParticle(mParticlePool[i]);
		}
	}

	virtual void Update(const float delta_t) = 0;

protected:
	void CreateParticle(ParticleType* particle) {
		if (mParticlePool.size() < mParticleNumber)
			mParticlePool.push_back(particle);
	}

private:
	virtual void RenderParticle(ParticleType* particle) = 0;

protected:
	typename std::vector<ParticleType*> mParticlePool;
	int mParticleNumber;

	// initial translate and scale for whole particlesystem
	glm::vec3 trans, scale;
};


#endif
