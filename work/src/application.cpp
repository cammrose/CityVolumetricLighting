
// std
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

// project
#include "application.hpp"
#include "cgra/cgra_geometry.hpp"
#include "cgra/cgra_gui.hpp"
#include "cgra/cgra_image.hpp"
#include "cgra/cgra_shader.hpp"
#include "cgra/cgra_wavefront.hpp"
#include "cgra/cgra_shadows.hpp"


using namespace std;
using namespace cgra;
using namespace glm;

//Global Variables
vec2 guiCitySize = vec2(1.5, 1.5);
vec2 citySize = vec2(1.5, 1.5);
vec2 buildingHeightRange = vec2(20, 300);
vec2 subdivisionSizeRange = vec2(120, 220);
float roadWidthGUI = 35;
float roadWidth = 0.03;
vector<float> buildingHeights;
vector<float> roadLinesX;
vector<float> roadLinesY;
int vertCount = 0;
int polyCount = 0;
int fc=0;


void basic_model::draw(const glm::mat4 &view, const glm::mat4 proj) {
	mat4 modelview = view * modelTransform;

	glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-200, 200, -200, 200, -200, 200);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * modelTransform;
	
	glUseProgram(shader); // load shader and variables
	//glUniformMatrix4fv(glGetUniformLocation(shader, "uProjectionMatrix"), 1, false, value_ptr(proj));
	//glUniformMatrix4fv(glGetUniformLocation(shader, "uModelViewMatrix"), 1, false, value_ptr(modelview));
	glUniformMatrix4fv(glGetUniformLocation(shader, "depthMVP"), 1, false, value_ptr(depthMVP));
	//glUniform3fv(glGetUniformLocation(shader, "uColor"), 1, value_ptr(color));
    
    //drawSphere();
    
	drawCube(mesh);
    //modelview = scale(modelview, vec3(baseSize.x, 0.0001, baseSize.y));
    //glUniformMatrix4fv(glGetUniformLocation(shader, "uModelViewMatrix"), 1, false, value_ptr(modelview));

    //drawCube();

	mesh.draw(); // draw
}

vector<basic_model> Application::buildScene() {
	vector<basic_model> models;

	polyCount = 0;
	vertCount = 0;

	vec3 globalScale = vec3(10, 10, 10);

	//Green plane
	basic_model greenPlane;
	greenPlane.color = vec3(0.2, 0.5, 0.3);
	greenPlane.modelTransform = scale(greenPlane.modelTransform, globalScale);
	greenPlane.modelTransform = translate(greenPlane.modelTransform, vec3(0, -0.006, 0));
	greenPlane.modelTransform = scale(greenPlane.modelTransform, vec3(10000, 0.0001, 10000));
	greenPlane.mesh = m_cubeMesh;
	//models.push_back(greenPlane);

	//White plane
	basic_model whitePlane;
	whitePlane.color = vec3(0, 1, 0);
	whitePlane.modelTransform = scale(whitePlane.modelTransform, globalScale);
	whitePlane.modelTransform = translate(whitePlane.modelTransform, vec3(0, 0, 0));
	whitePlane.modelTransform = scale(whitePlane.modelTransform, vec3(citySize.x, 0.0001, citySize.y));
	whitePlane.mesh = m_cubeMesh;
	models.push_back(whitePlane);

    pair<vec2,vec2> pos1 = getSubdivision(0,0);
    pair<vec2,vec2> pos2 = getSubdivision(roadLinesX.size()-1,roadLinesY.size()-1);
    
    basic_model road;
    road.color = vec3(0, 0, 0);
    road.modelTransform = scale(road.modelTransform, globalScale);
    road.modelTransform = translate(road.modelTransform, vec3(0, 0.001, 0));
    road.modelTransform = scale(road.modelTransform, vec3(citySize.x, 0.0001,citySize.y));
    road.mesh = m_cubeMesh;
    models.push_back(road);

	//getRandom(0.0f, 100.0f);

	//Buildings
	int buildingNumber = 0;
	for (int y = 0; y<roadLinesX.size() - 1; y++) {
		for (int x = 0; x<roadLinesY.size() - 1; x++) {
			pair<vec2, vec2> subdivision = getSubdivision(y, x);
			vec2 centrePoint = subdivision.first;
			vec2 subdSize = subdivision.second;

			float buildingWidth = subdSize[0] / 3;
			float buildingLength = subdSize[1] / 3;
            float buildingSize = std::min(buildingWidth, buildingLength);
            
            //vector<vec3> buildingSegments;
            //buildingSegments.push_back(vec3());
            
            //Base
            basic_model building;
            building.color = vec3(0.5);
            building.modelTransform = scale(building.modelTransform, globalScale);
            building.modelTransform = translate(building.modelTransform, vec3(centrePoint.x - (citySize.x / 2), 0, centrePoint.y - (citySize.y / 2)));
            building.modelTransform = scale(building.modelTransform, vec3(subdSize[0], 0.002, subdSize[1]));
            building.mesh = m_cubeMesh;
            models.push_back(building);


			for (int i = 0; i<3; i++) {
				for (int j = 0; j<3; j++) {
                    float buildingHeight = buildingHeights[buildingNumber];
                    float prevBuildingWidth = 0;
                    float prevBuildingLength = 0;
                    
                    while (buildingHeight > 0.02) {
                        
                        basic_model building;
                        building.color = vec3(0.5);
                        building.modelTransform = scale(building.modelTransform, globalScale);
                        building.modelTransform = translate(building.modelTransform, vec3((subdSize[0] / 2 - buildingWidth / 2) - (buildingWidth)*i + getRandom(-0.005, 0.005), 0, subdSize[1] / 2 - buildingLength / 2 - (buildingLength)*j + getRandom(-0.005, 0.005))); //Building
                        
                        building.modelTransform = translate(building.modelTransform, vec3(centrePoint.x - (citySize.x / 2), 0, centrePoint.y - (citySize.y / 2))); //Subdivision
                        
                        float buildingWidth = getRandom(0.01, buildingSize);
                        float buildingLength = getRandom(0.01, buildingSize);
                        while (buildingLength < prevBuildingLength-0.1 || buildingWidth < prevBuildingWidth-0.1) {
                            buildingWidth = getRandom(0.01, buildingSize);
                            buildingLength = getRandom(0.01, buildingSize);
                        }
                        
                        building.modelTransform = scale(building.modelTransform, vec3(buildingWidth, buildingHeight, buildingLength));
                        float prevBuildingWidth = buildingWidth;
                        float prevBuildingLength = buildingLength;
                        building.mesh = m_cubeMesh;
                        models.push_back(building);
                        
                        buildingHeight = getRandom(buildingHeight/3, buildingHeight);
                    }
                    
                    basic_model building;
                    building.color = vec3(0.5);
                    building.modelTransform = scale(building.modelTransform, globalScale);
                    building.modelTransform = translate(building.modelTransform, vec3((subdSize[0] / 2 - buildingWidth / 2) - (buildingWidth)*i, 0, subdSize[1] / 2 - buildingLength / 2 - (buildingLength)*j));
                    building.modelTransform = translate(building.modelTransform, vec3(centrePoint.x - (citySize.x / 2), 0, centrePoint.y - (citySize.y / 2)));
                    building.modelTransform = scale(building.modelTransform, vec3(buildingSize, 0.004, buildingSize));
                    building.mesh = m_cubeMesh;
                    models.push_back(building);


					buildingNumber++;
					if (buildingNumber > 50 * 50) {
						buildingNumber = 0;
					}
				}
			}
		}
	}

	return models;
}


Application::Application(GLFWwindow *window) : m_window(window) {
	shader_builder sb;

    sb.set_shader(GL_VERTEX_SHADER, CGRA_SRCDIR + std::string("//res//shaders//depth_vert.glsl"));
	sb.set_shader(GL_FRAGMENT_SHADER, CGRA_SRCDIR + std::string("//res//shaders//depth_frag.glsl"));
	m_depthShader = sb.build();

	sb.set_shader(GL_VERTEX_SHADER, CGRA_SRCDIR + std::string("//res//shaders//shadow_vert.glsl"));
	sb.set_shader(GL_FRAGMENT_SHADER, CGRA_SRCDIR + std::string("//res//shaders//shadow_frag.glsl"));
	m_shadowShader = sb.build();

	cgra::gl_mesh teapotMesh = load_wavefront_data(CGRA_SRCDIR + std::string("/res//assets//teapot.obj")).build();

	m_cubeMesh = load_wavefront_data(CGRA_SRCDIR + std::string("/res//assets//cube.obj")).build();

	setVariables(); //Sets the variables when the program is initially run

	m_biasMatrix = mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);
	m_ditherMatrix = mat4(
		0.0, 0.5, 0.125, 0.625,
		0.75, 0.22, 0.875, 0.375,
		0.1875, 0.6875, 0.0625, 0.5625,
		0.9375, 0.4375, 0.8125, 0.3125
	) * mat4(
		1.0, 0.0, 0.0, -1.5,
		0.0, 1.0, 0.0, -1.5,
		0.0, 0.0, 1.0, -1.5,
		0.0, 0.0, 0.0, 1.0
	);
	m_ditherMatrix = mat4(1);

	m_lightPos = vec3(5, 3, 20);
	m_fogColor = vec3(0.8, 0.8, 0.8);
	m_lightColor = vec3(0.95, 0.95, 0.95);
	m_fogIntensity = 3.75f;
	m_fogHeight = 45.0f;
	m_fogSpread = 1.0f;

	m_cascadeLengths[0] = 0.1;
	m_cascadeLengths[1] = 0.3;
	m_cascadeLengths[2] = 1;
}


void Application::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	polyCount = 0;
	vertCount = 0;

	// retrieve the window hieght
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	// projection matrix
	float fov = 1.0f;
	float aspect = float(width) / height;
	float nearPlaneDist = 0.1f;
	float farPlaneDist = 200.0f;

	// view matrix
	mat4 cameraView = translate(mat4(1), vec3(0, 0, -m_distance))
		* rotate(mat4(1), m_pitch, vec3(1, 0, 0))
		* rotate(mat4(1), m_yaw, vec3(0, 1, 0));
	mat4 cameraProj = perspective(fov, aspect, nearPlaneDist, farPlaneDist);

	vec3 cameraPos = vec3(inverse(cameraView) * vec4(0, 0, 0, 1));
	vec3 cameraDir = normalize(-cameraPos); //* nearPlaneDist;

	vec3 lightPos = m_lightPos;
	vec3 lightDir = normalize(-m_lightPos);

	float lightNearPlane = -50;
	float lightFarPlane = 100;

	vec3 right = normalize(cross(cameraDir, vec3(0, 1, 0)));
	vec3 up = normalize(cross(right, cameraDir));

	right = -right;

	float cameraFrustumLength = farPlaneDist - nearPlaneDist;

	mat4 lightView = lookAt(lightPos, vec3(0, 0, 0), vec3(0, 1, 0));
	
	//for (int i = 1; i < 2; i++) {
	for (int i = 0; i < m_shadowMaps; i++) {
		shadow_mapper& shadowMapper = m_shadowMappers[i];

		float start = i > 0 ? m_cascadeLengths[i - 1] : 0.0f;
		float end = m_cascadeLengths[i];

		float startDist = nearPlaneDist + cameraFrustumLength * start;
		float endDist = nearPlaneDist + cameraFrustumLength * end;

		vec3 startCenter = cameraPos + cameraDir * startDist;
		float startHalfHeight = tan(fov / 2.0f) * startDist;
		float startHalfWidth = startHalfHeight * aspect;

		vec3 endCenter = cameraPos + cameraDir * endDist;
		float endHalfHeight = tan(fov / 2.0f) * endDist;
		float endHalfWidth = endHalfHeight * aspect;

		vector<vec3> frustumPoints;
		frustumPoints.push_back(startCenter - right * startHalfWidth + up * startHalfHeight);
		frustumPoints.push_back(startCenter + right * startHalfWidth + up * startHalfHeight);
		frustumPoints.push_back(startCenter - right * startHalfWidth - up * startHalfHeight);
		frustumPoints.push_back(startCenter + right * startHalfWidth - up * startHalfHeight);

		frustumPoints.push_back(endCenter - right * endHalfWidth + up * endHalfHeight);
		frustumPoints.push_back(endCenter + right * endHalfWidth + up * endHalfHeight);
		frustumPoints.push_back(endCenter - right * endHalfWidth - up * endHalfHeight);
		frustumPoints.push_back(endCenter + right * endHalfWidth - up * endHalfHeight);

		vec4 min = vec4(std::numeric_limits<float>::infinity()), max = vec4(-std::numeric_limits<float>::infinity());
		for (int j = 0; j < frustumPoints.size(); j++) {
			vec4 lightSpacePosition = lightView * vec4(frustumPoints.at(j), 1);

			min = minVec(min, lightSpacePosition);
			max = maxVec(max, lightSpacePosition);
		}

		mat4 lightProj = ortho<float>(min.x, max.x, min.y, max.y, -100, 100);
		m_lightProj[i] = lightProj;

		mat4 lightViewProj = lightProj * lightView;

		// use the depth shader to create the shadow map
		shadowMapper.bindFramebuffer();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glUseProgram(m_depthShader);

		for (int j = 0; j < m_models.size(); j++) {
			basic_model& model = m_models.at(j);

			mat4 lightMVP = lightViewProj * model.modelTransform;

			glUniformMatrix4fv(glGetUniformLocation(m_depthShader, "lightMVP"), 1, false, value_ptr(lightMVP));

			model.mesh.draw();
		}
	}

	//return;

	// return to window
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_windowsize = vec2(width, height); // update window size
	glViewport(0, 0, width, height); // set the viewport to draw to the entire window

	// clear the back-buffer
	glClearColor(m_fogColor.x * m_lightColor.x, 
		m_fogColor.y * m_lightColor.y, 
		m_fogColor.z * m_lightColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// enable flags for normal/forward rendering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// helpful draw options
	if (m_show_grid) drawGrid(cameraView, cameraProj);
	if (m_show_axis) drawAxis(cameraView, cameraProj);
	glPolygonMode(GL_FRONT_AND_BACK, (m_showWireframe) ? GL_LINE : GL_FILL);
    
	// draw using the shadow shader
	glUseProgram(m_shadowShader);

	glUniformMatrix4fv(glGetUniformLocation(m_shadowShader, "cameraView"), 1, false, value_ptr(cameraView));
	glUniform3fv(glGetUniformLocation(m_shadowShader, "cameraPos"), 1, value_ptr(cameraPos));
	glUniform3fv(glGetUniformLocation(m_shadowShader, "lightInvDir"), 1, value_ptr(m_lightPos));
	glUniform3fv(glGetUniformLocation(m_shadowShader, "fogColor"), 1, value_ptr(m_fogColor));
	glUniform3fv(glGetUniformLocation(m_shadowShader, "lightColor"), 1, value_ptr(m_lightColor));
	glUniform1f(glGetUniformLocation(m_shadowShader, "fogIntensity"), m_fogIntensity);
	glUniform1fv(glGetUniformLocation(m_shadowShader, "cascadeLengths"), m_shadowMaps, m_cascadeLengths);
	glUniform1f(glGetUniformLocation(m_shadowShader, "nearPlaneDist"), nearPlaneDist);
	glUniform1f(glGetUniformLocation(m_shadowShader, "farPlaneDist"), farPlaneDist);
	glUniform1f(glGetUniformLocation(m_shadowShader, "fogHeight"), m_fogHeight);
	glUniform1f(glGetUniformLocation(m_shadowShader, "fogSpread"), m_fogSpread);
	glUniformMatrix4fv(glGetUniformLocation(m_shadowShader, "ditherMatrix"), 1, false, value_ptr(m_ditherMatrix));

	glUniform1i(glGetUniformLocation(m_shadowShader, "shadowMap0"), 0);
	glUniform1i(glGetUniformLocation(m_shadowShader, "shadowMap1"), 1);
	glUniform1i(glGetUniformLocation(m_shadowShader, "shadowMap2"), 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_shadowMappers[0].getDepthTexture());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_shadowMappers[1].getDepthTexture());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_shadowMappers[2].getDepthTexture());

	for (int i = 0; i < m_models.size(); i++) {
		basic_model& model = m_models.at(i);
        vertCount += 8;
        polyCount += 12;

		mat4 VP = cameraProj * cameraView;
		mat4 MVP = VP * model.modelTransform;
		mat4 inverseMVP = inverse(MVP); 
		
		mat4 depthBiasVPs[m_shadowMaps];
		for (int j = 0; j < m_shadowMaps; j++) {
			depthBiasVPs[j] = m_biasMatrix * m_lightProj[j] * lightView;
		}

		glUniformMatrix4fv(glGetUniformLocation(m_shadowShader, "M"), 1, false, value_ptr(model.modelTransform));
		glUniformMatrix4fv(glGetUniformLocation(m_shadowShader, "MVP"), 1, false, value_ptr(MVP));
		glUniformMatrix4fv(glGetUniformLocation(m_shadowShader, "depthBiasVPs"), m_shadowMaps, false, value_ptr(depthBiasVPs[0]));

		vec3 ambient = model.color / 4.0f;
		glUniform3fv(glGetUniformLocation(m_shadowShader, "ambientColor"), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(m_shadowShader, "diffuseColor"), 1, value_ptr(model.color));

		model.mesh.draw();
	}
    
    //Camera Animation
    /*
    if(m_yaw<3.10){
        m_yaw+=0.01;
    }
    else if(m_lightPos.y > -4){
        m_lightPos.y -= 0.05;
        m_lightColor -= vec3(0, 0.0016, 0.002);
    }
    else{
        m_lightColor = vec3(0.95, 0.95, 0.95);
        m_yaw+=0.01;
    }
    
    if(m_leftMouseDown && fc > 10){
        setVariables();
        fc =0;
    }

    fc++;
    */
    
    //m_yaw+=0.01;
}

void Application::renderScene(const mat4 &view, const mat4 &proj) {
	// draw the models
	for (int i = 0; i < m_models.size(); i++) {
		m_models.at(i).draw(view, proj);
        
	}
}


void Application::renderGUI() {

	// setup window
	ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiSetCond_Once);
	ImGui::Begin("Options", 0);

	// display current camera parameters
	ImGui::Text("Application %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Polygons: %d\t\tVertices:  %d", polyCount, vertCount);
	ImGui::SliderFloat("Pitch", &m_pitch, -pi<float>() / 2, pi<float>() / 2, "%.2f");
	ImGui::SliderFloat("Yaw", &m_yaw, -pi<float>(), pi<float>(), "%.2f");
	ImGui::SliderFloat("Distance", &m_distance, 0, 100, "%.2f", 2.0f);
	

	// helpful drawing options
	ImGui::Checkbox("Show axis", &m_show_axis);
	ImGui::SameLine();
	ImGui::Checkbox("Show grid", &m_show_grid);
	ImGui::Checkbox("Wireframe", &m_showWireframe);
	ImGui::SameLine();
	if (ImGui::Button("Screenshot")) rgba_image::screenshot(true);
    
    ImGui::Separator();
    
    ImGui::TextColored(ImVec4(0.15, 0.6, 1, 1), "Volumetric Lighting");
    
    ImGui::SliderFloat3("Light Position", &m_lightPos[0], -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat3("Light Color", &m_lightColor[0], 0.0f, 1.0f, "%.2f");
	ImGui::SliderFloat3("Fog Color", &m_fogColor[0], 0.0f, 1.0f, "%.2f");
	ImGui::SliderFloat("Fog Intensity", &m_fogIntensity, 0.0f, 10.0f, "%.2f");
	ImGui::SliderFloat("Fog Height", &m_fogHeight, 0.0f, 100.0f, "%.2f");
	ImGui::SliderFloat("Fog Spread", &m_fogSpread, 0.0f, 5.0f, "%.2f");

	ImGui::SliderFloat2("Cascade Lengths", m_cascadeLengths, 0.0f, 1.0f, "%.2f");
	for (int i = 1; i < 3; i++) {
        m_cascadeLengths[i] = std::max(m_cascadeLengths[i], m_cascadeLengths[i - 1]);
	}

	ImGui::Separator();

	ImGui::TextColored(ImVec4(0.15, 0.6, 1, 1), "City Generation");
	ImGui::SliderFloat("City Length", &guiCitySize[0], 0.5, 5.0, "%.2fkm");
	ImGui::SliderFloat("City Width", &guiCitySize[1], 0.5, 5.0, "%.2fkm");

	ImGui::DragFloatRange2("Building Height Range", &buildingHeightRange[0], &buildingHeightRange[1], 0.25f, 10.0f, 300.0f, "Min: %.1fm", "Max: %.1fm");
    ImGui::DragFloatRange2("Subdivision Size Range", &subdivisionSizeRange[0], &subdivisionSizeRange[1], 0.25f, 40.0f, 400.0f, "Min: %.1fm", "Max: %.1fm");
    ImGui::SliderFloat("Road Width", &roadWidthGUI, 4.0f, 40.0f, "%.2fm");

	if (ImGui::Button("Generate")) {
		setVariables();
	}

	// example of how to use input boxes

	// finish creating window
	ImGui::End();
}


void Application::cursorPosCallback(double xpos, double ypos) {
	if (m_leftMouseDown) {
		vec2 whsize = m_windowsize / 2.0f;

		// clamp the pitch to [-pi/2, pi/2]
		m_pitch += float(acos(glm::clamp((m_mousePosition.y - whsize.y) / whsize.y, -1.0f, 1.0f))
			- acos(glm::clamp((float(ypos) - whsize.y) / whsize.y, -1.0f, 1.0f)));
		m_pitch = float(glm::clamp(m_pitch, -pi<float>() / 2, pi<float>() / 2));

		// wrap the yaw to [-pi, pi]
		m_yaw += float(acos(glm::clamp((m_mousePosition.x - whsize.x) / whsize.x, -1.0f, 1.0f))
			- acos(glm::clamp((float(xpos) - whsize.x) / whsize.x, -1.0f, 1.0f)));
		if (m_yaw > pi<float>()) m_yaw -= float(2 * pi<float>());
		else if (m_yaw < -pi<float>()) m_yaw += float(2 * pi<float>());
	}

	// updated mouse position
	m_mousePosition = vec2(xpos, ypos);
}


void Application::mouseButtonCallback(int button, int action, int mods) {
	(void)mods; // currently un-used

	// capture is left-mouse down
	if (button == GLFW_MOUSE_BUTTON_LEFT)
		m_leftMouseDown = (action == GLFW_PRESS); // only other option is GLFW_RELEASE
}


void Application::scrollCallback(double xoffset, double yoffset) {
	(void)xoffset; // currently un-used
	m_distance *= pow(1.1f, -yoffset);
}


void Application::keyCallback(int key, int scancode, int action, int mods) {
    setVariables();
	(void)key, (void)scancode, (void)action, (void)mods; // currently un-used
}


void Application::charCallback(unsigned int c) {
	(void)c; // currently un-used
}
float getRandom(float min, float max) {
	if (min == max) {
		max += 0.0001;
	}
	float random = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return random;
}

void basic_model::drawCube(cgra::gl_mesh mesh) {
	mesh.draw();
	vertCount += 8;
	polyCount += 12;

}

void Application::setVariables() {
	buildingHeights.clear();
	roadLinesX.clear();
	roadLinesY.clear();
    m_models.clear();

    roadWidth = roadWidthGUI/1000;
    
	citySize = vec2(guiCitySize[0], guiCitySize[1]);

	for (int i = 0; i<50; i++) {
		for (int j = 0; j<50; j++) {
			buildingHeights.push_back(getRandom(buildingHeightRange[0] / 1000, buildingHeightRange[1] / 1000));
		}
	}
    
    float streetX=0;
    while(streetX < citySize.x){
        streetX = getRandom(streetX + subdivisionSizeRange[0]/1000, streetX + subdivisionSizeRange[1]/1000);
        if(streetX < citySize.x){
            roadLinesX.push_back(streetX);
        }
    }
    
    float streetY=0;
    while(streetY < citySize.y){
        streetY = getRandom(streetY + subdivisionSizeRange[0]/1000, streetY + subdivisionSizeRange[1]/1000);
        if(streetY < citySize.y){
            roadLinesY.push_back(streetY);
        }
    }
	
	vector<basic_model> models = buildScene();
	for (int i = 0; i < models.size(); i++) {
		m_models.push_back(models.at(i));
	}
}

std::pair<vec2, vec2> getSubdivision(int x, int y) {

	vec2 currentPoint = vec2(roadLinesX[x], roadLinesY[y]);
	vec2 middlePoint;
	middlePoint.x = (currentPoint.x + roadLinesX[x + 1]) / 2;
	middlePoint.y = (currentPoint.y + roadLinesY[y + 1]) / 2;

	vec2 subdSize = vec2(abs(roadLinesX[x] - roadLinesX[x + 1]) - roadWidth, abs(roadLinesY[y] - roadLinesY[y + 1]) - roadWidth);

	pair<vec2, vec2> pair;
	pair.first = middlePoint;
	pair.second = subdSize;
	return pair;
}

glm::vec4 Application::minVec(glm::vec4 v1, glm::vec4 v2) {
	return vec4(glm::min(v1.x, v2.x), glm::min(v1.y, v2.y),
		glm::min(v1.z, v2.z), glm::min(v1.w, v2.w));
}

glm::vec4 Application::maxVec(glm::vec4 v1, glm::vec4 v2) {
	return vec4(glm::max(v1.x, v2.x), glm::max(v1.y, v2.y),
		glm::max(v1.z, v2.z), glm::max(v1.w, v2.w));
}
