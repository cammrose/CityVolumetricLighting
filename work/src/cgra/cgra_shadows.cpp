// std
#include <stdexcept>

// project
#include "cgra_shadows.hpp"

using namespace glm;

namespace cgra {
	shadow_mapper::shadow_mapper() {
		m_framebufferName = 0;
		glGenFramebuffers(1, &m_framebufferName);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferName);

		m_depthTexture;
		glGenTextures(1, &m_depthTexture);
		glBindTexture(GL_TEXTURE_2D, m_depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthTexture, 0);

		glDrawBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			//throw _exception();
		}
	}

	GLuint shadow_mapper::getDepthTexture() {
		return m_depthTexture;
	}

	void shadow_mapper::bindFramebuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferName);
		glViewport(0, 0, 1024, 1024);
	}
}
