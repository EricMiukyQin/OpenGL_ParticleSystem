#ifndef FIREWORKCONE_H
#define FIREWORKCONE_H

#include "ParticleSystem.h"

class ShaderManager;

class FireworkCone : public ParticleSystem<FireworkParticle> {
public:
	FireworkCone(ShaderManager* shaderManager, const glm::vec3& trans, const glm::vec3& scale, const int particleNumber, const float particleLifespan, const glm::vec4& color);
	~FireworkCone();

	void Update(const float delta_t) override;

	void BuildArrays();
	void BindVBO(unsigned int programID);

private:
	void RenderParticle(FireworkParticle* particle) override;

private:
	ShaderManager* mShaderManager;
};


#endif