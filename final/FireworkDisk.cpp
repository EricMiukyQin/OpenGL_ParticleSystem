#if defined(__APPLE__)
#  include <OpenGL/gl3.h> // defines OpenGL 3.0+ functions
#else
#  if defined(WIN32)
#    define GLEW_STATIC 1
#  endif
#  include <GL/glew.h>
#endif

#include "FireworkDisk.h"
#include "ShaderManager.h"


FireworkDisk::FireworkDisk(ShaderManager* shaderManager, const glm::vec3& trans, const glm::vec3& scale, const int particleNumber, const float particleLifespan, const glm::vec4& color)
	: ParticleSystem(trans, scale, particleNumber), mShaderManager{ shaderManager } {
	for (int i = 0; i < particleNumber; ++i) {
		FireworkParticle* fireworkParticle = new FireworkParticle(particleLifespan, Util::RandFloat(1.f, 10.f), color);
		CreateParticle(fireworkParticle);
	}
}


FireworkDisk::~FireworkDisk() {}


void FireworkDisk::Update(const float delta_t) {
	for (int i = 0; i < mParticlePool.size(); ++i) {
		if (Util::LessOrEqual(mParticlePool[i]->lifespan, 0.f))
			continue;


		// phase 1
		if (Util::Equal(mParticlePool[i]->velocity.x, 0.f) && Util::Equal(mParticlePool[i]->velocity.z, 0.f)) {
			/*if (Util::LessOrEqual(mParticlePool[i]->velocity.y, 40.f)) {*/
			if (Util::GreaterOrEqual(mParticlePool[i]->position.y, 300.f) && Util::RandFloat(-4.f, 1.f) > 0) {
				// assign a phase 2 velocity
				mParticlePool[i]->velocity = glm::vec3{
					30.f * cosf(2.f * i * PI / mParticlePool.size()) + Util::RandFloat(-2.5f, 2.5f),
					15.f + Util::RandFloat(-5.f, 5.f),
					30.f * sinf(2.f * i * PI / mParticlePool.size()) + Util::RandFloat(-2.5f, 2.5f)
				};
			}
			else {
				// in phase 1
				// update phase1 velocity y
				mParticlePool[i]->velocity.y += mParticlePool[i]->gravity * delta_t;

				// Wrong but Diao De Yi Bi. Try this. 
				mParticlePool[i]->position.x += 1.f * cosf(i * 2 * PI / mParticlePool.size());
				mParticlePool[i]->position.y += mParticlePool[i]->velocity.y * delta_t + .5f * mParticlePool[i]->gravity * powf(delta_t, 2);
				mParticlePool[i]->position.z += 1.f * sinf(i * 2 * PI / mParticlePool.size());
			}
		}
		else {
			// phase 2
			// random acceleration on x and z axis
			float acc_x = Util::RandFloat(-.5f, -.1f), acc_z = Util::RandFloat(-.5f, -.1f);

			// update velocity
			mParticlePool[i]->velocity.x += acc_x * delta_t;
			mParticlePool[i]->velocity.y += mParticlePool[i]->gravity * delta_t;
			mParticlePool[i]->velocity.z += acc_z * delta_t;

			// update position
			mParticlePool[i]->position.x += mParticlePool[i]->velocity.x * delta_t + .5f * acc_x * powf(delta_t, 2) + Util::RandFloat(-0.4f, 0.4f);
			mParticlePool[i]->position.y += mParticlePool[i]->velocity.y * delta_t + .5f * mParticlePool[i]->gravity * powf(delta_t, 2);
			mParticlePool[i]->position.z += mParticlePool[i]->velocity.z * delta_t + .5f * acc_z * powf(delta_t, 2) + Util::RandFloat(-0.4f, 0.4f);

			// update lifespan
			mParticlePool[i]->lifespan -= mParticlePool[i]->decay * delta_t;
		}
	}
}


void FireworkDisk::BuildArrays() {
	for (const auto& particle : mParticlePool)
		particle->sphere->BuildArrays();
}

void FireworkDisk::BindVBO(unsigned int programID) {
	for (const auto& particle : mParticlePool)
		particle->sphere->BindVBO(programID);
}


void FireworkDisk::RenderParticle(FireworkParticle* particle) {
	glm::mat4 transformMatrix = glm::mat4(1);
	transformMatrix = glm::scale(transformMatrix, scale);
	transformMatrix = glm::translate(transformMatrix, particle->position);
	transformMatrix = glm::translate(transformMatrix, trans);
	glUniformMatrix4fv(glGetUniformLocation(mShaderManager->program, "myTransformMatrix"), 1, false, glm::value_ptr(transformMatrix));
	particle->sphere->RenderVBO();
}