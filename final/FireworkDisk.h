#ifndef FIREWORKDISK_H
#define FIREWORKDISK_H

#include "ParticleSystem.h"

class ShaderManager;

class FireworkDisk : public ParticleSystem<FireworkParticle> {
public:
	FireworkDisk(ShaderManager* shaderManager, const glm::vec3& trans, const glm::vec3& scale, const int particleNumber, const float particleLifespan, const glm::vec4& color);
	~FireworkDisk();

	void Update(const float delta_t) override;

	void BuildArrays();
	void BindVBO(unsigned int programID);

private:
	void RenderParticle(FireworkParticle* particle) override;

private:
	ShaderManager* mShaderManager;
};


#endif