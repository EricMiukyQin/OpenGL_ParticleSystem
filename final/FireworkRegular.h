#ifndef FIREWORKREGULAR_H
#define FIREWORKREGULAR_H

#include "ParticleSystem.h"

class ShaderManager;

class FireworkRegular : public ParticleSystem<FireworkParticle> {
public:
	FireworkRegular(ShaderManager* shaderManager, const glm::vec3& trans, const glm::vec3& scale, const int particleNumber, const float particleLifespan, const glm::vec4& color);
	~FireworkRegular();

	void Update(const float delta_t) override;

	void BuildArrays();
	void BindVBO(unsigned int programID);

private:
	void RenderParticle(FireworkParticle* particle) override;

private:
	ShaderManager* mShaderManager;
};


#endif