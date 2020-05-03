#ifndef FIREWORKCYLINDER_H
#define FIREWORKCYLINDER_H

#include "ParticleSystem.h"

class ShaderManager;

class FireworkCylinder : public ParticleSystem<FireworkParticle> {
public:
	FireworkCylinder(ShaderManager* shaderManager, const glm::vec3& trans, const glm::vec3& scale, const int particleNumber, const float particleLifespan, const glm::vec4& color);
	~FireworkCylinder();

	void Update(const float delta_t) override;

	void BuildArrays();
	void BindVBO(unsigned int programID);

private:
	void RenderParticle(FireworkParticle* particle) override;

private:
	ShaderManager* mShaderManager;
};


#endif