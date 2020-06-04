#pragma once


#include <utility>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// project
#include "opengl.hpp"
#include "cgra/cgra_mesh.hpp"
#include "cgra/cgra_shadows.hpp"

// Basic model that holds the shader, mesh and transform for drawing.
// Can be copied and modified for adding in extra information for drawing
// including textures for texture mapping etc.
struct basic_model {
	GLuint shader = 0;
	cgra::gl_mesh mesh;
	glm::vec3 color{0.2};
	glm::mat4 modelTransform{1.0};
	GLuint texture;

	void draw(const glm::mat4 &view, const glm::mat4 proj);
	void drawCube(cgra::gl_mesh mesh);
};


// Main application class
//
class Application {
private:
	// window
	glm::vec2 m_windowsize;
	GLFWwindow *m_window;

	// oribital camera
    float m_pitch = .3;
    float m_yaw = -.86;
    float m_distance = 15;

	// last input
	bool m_leftMouseDown = false;
	glm::vec2 m_mousePosition;

	// drawing flags
	bool m_show_axis = false;
	bool m_show_grid = false;
	bool m_showWireframe = false;

	// geometry
	std::vector<basic_model> m_models;

	GLuint m_depthShader, m_shadowShader;

	static const int m_shadowMaps = 3;
	cgra::shadow_mapper m_shadowMappers[m_shadowMaps];
	float m_cascadeLengths[m_shadowMaps];
	glm::mat4 m_lightProj[m_shadowMaps];

	glm::mat4 m_biasMatrix, m_ditherMatrix;

	glm::vec3 m_lightPos, m_fogColor, m_lightColor;
	float m_fogIntensity, m_fogSpread, m_fogHeight;

	cgra::gl_mesh m_cubeMesh;

public:
	// setup
	Application(GLFWwindow *);

	// disable copy constructors (for safety)
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	// rendering callbacks (every frame)
	void render();
	void renderScene(const glm::mat4& view, const glm::mat4& proj);
	void renderGUI();

	void setVariables();
	std::vector<basic_model> buildScene();

	// input callbacks
	void cursorPosCallback(double xpos, double ypos);
	void mouseButtonCallback(int button, int action, int mods);
	void scrollCallback(double xoffset, double yoffset);
	void keyCallback(int key, int scancode, int action, int mods);
	void charCallback(unsigned int c);

	void drawCube(cgra::gl_mesh mesh);

	glm::vec4 minVec(glm::vec4 v1, glm::vec4 v2);
	glm::vec4 maxVec(glm::vec4 v1, glm::vec4 v2);
};

float getRandom(float min, float max);
std::pair<glm::vec2, glm::vec2> getSubdivision(int x, int y);
