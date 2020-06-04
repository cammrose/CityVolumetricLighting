#pragma once

// std
#include <iostream>
#include <vector>

// glm
#include <glm/glm.hpp>

// project
#include <opengl.hpp>

namespace cgra {
	class shadow_mapper {
	private:
		GLuint m_framebufferName, m_depthTexture;

	public: 
		shadow_mapper();

		GLuint getDepthTexture();

		void bindFramebuffer();
	};
}
