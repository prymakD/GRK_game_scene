#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>	
#include <cmath>
#include <ctime>
#include <random>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Laser.h"
#include "SpaceShip.h"
#include "Texture.h"
#include "SOIL/SOIL.h"

#include <string>
#include "Box.cpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

#include <vector>
#include <algorithm>

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

int WIDTH = 950, HEIGHT = 950;

struct Vertex {
	float x, y, z;
};

namespace texture {
	GLuint skybox;
	GLuint sofa;
	GLuint floor;
	GLuint walls;
	GLuint ship;
	GLuint roof;
	GLuint xThing;
	GLuint table;
	GLuint tvTable;
	GLuint paintFace;
	GLuint paintBack;
	GLuint door;
	GLuint books;
	GLuint tvscreen;
	GLuint vase1;
	GLuint tv;


	GLuint paintDiffuseMap;
	GLuint paintNormalMap;
	GLuint paintHeightMap;
}

namespace models {

	Core::RenderContext sofaContext;
	Core::RenderContext booksContext;
	Core::RenderContext tvTableContext;
	Core::RenderContext tableContext;
	Core::RenderContext doorContext;
	Core::RenderContext doorFrameContext;
	//Core::RenderContext drawerContext;
	Core::RenderContext tvContext;
	Core::RenderContext tvScreen;
	Core::RenderContext xThingContext;
	Core::RenderContext planeContext;
	Core::RenderContext roomOutsideContext;
	Core::RenderContext roomInsideContext;
	Core::RenderContext roofContext;
	Core::RenderContext brokenWindowContext;

	Core::RenderContext pawnFigureContext;
	Core::RenderContext towerFigureContext;
	Core::RenderContext horseFigureContext;

	Core::RenderContext spaceshipContext;
	Core::RenderContext sphereContext;
	Core::RenderContext windowContext;
	Core::RenderContext testContext;

	Core::RenderContext paintBackContext;
	Core::RenderContext paintFaceContext;

	Core::RenderContext vase1Context;
	Core::RenderContext vase2Context;


	Core::RenderContext laserContext1;
	Core::RenderContext laserContext2;
	Core::RenderContext laserContext3;
	Core::RenderContext laserContext4;
	Core::RenderContext laserContext5;
	Core::RenderContext laserContext6;
	Core::RenderContext laserContext7;
	Core::RenderContext laserContext8;
	Core::RenderContext laserContext9;
	Core::RenderContext laserContext10;
	Core::RenderContext laserContext11;
	Core::RenderContext laserContext12;
	Core::RenderContext laserContext13;
	Core::RenderContext laserContext14;
	Core::RenderContext laserContext15;
	Core::RenderContext laserContext16;
	Core::RenderContext laserContext17;
	Core::RenderContext laserContext18;
	Core::RenderContext laserContext19;
	Core::RenderContext laserContext20;

}

GLuint depthMapFBOSun;
GLuint depthMapSun;

GLuint program;
GLuint programSun;
GLuint programTest;
GLuint programTex;
GLuint programDepth;
GLuint programSkybox;
GLuint programParallaxMap;



GLuint programLaser;

Core::Shader_Loader shaderLoader;

Core::RenderContext shipContext;
Core::RenderContext enemyShipContext;
Core::RenderContext sphereContext;
Core::RenderContext skyboxContext;

glm::vec3 sunPos = glm::vec3(-4.740971f, 2.149999f, 0.369280f);
glm::vec3 sunDir = glm::vec3(-0.93633f, 0.351106, 0.003226f);
glm::vec3 sunColor = glm::vec3(0.9f, 0.9f, 0.7f) * 5;

glm::vec3 cameraPos = glm::vec3(0.479490f, 1.250000f, -2.124680f);
glm::vec3 cameraDir = glm::vec3(-0.354510f, 0.000000f, 0.935054f);

GLuint VAO, VBO;

float aspectRatio = 1.f;

float exposition = 1.f;

glm::vec3 pointlightPos = glm::vec3(0, 2, 0);
glm::vec3 pointlightColor = glm::vec3(0.9, 0.6, 0.6);


glm::vec3 laserLightPos0;
glm::vec3 laserLightPos1;
glm::vec3 laserLightPos2;
glm::vec3 laserLightPos3;
glm::vec3 laserLightPos4;
glm::vec3 laserLightPos5;
glm::vec3 laserLightPos6;
glm::vec3 laserLightPos7;
glm::vec3 laserLightPos8;
glm::vec3 laserLightPos9;
glm::vec3 laserLightPos10;
glm::vec3 laserLightPos11;
glm::vec3 laserLightPos12;
glm::vec3 laserLightPos13;
glm::vec3 laserLightPos14;
glm::vec3 laserLightPos15;
glm::vec3 laserLightPos16;
glm::vec3 laserLightPos17;
glm::vec3 laserLightPos18;
glm::vec3 laserLightPos19;
glm::vec3 laserLightColor = glm::vec3(1.0, 0, 0);

glm::vec3 spotlightPos = glm::vec3(0, 0, 0);
glm::vec3 spotlightConeDir = glm::vec3(0, 0, 0);
glm::vec3 spotlightColor = glm::vec3(0.4, 0.4, 0.9) * 3;
float spotlightPhi = 3.14 / 4;

glm::vec3 laserColor = glm::vec3(0, 0, 0);


bool drawLaserShot = false;


double startCursorXPos;
double startCursorYPos;


float lastTime = -1.f;
float deltaTime = 0.f;

bool isWindowBroke = false;

Laser laser1 = Laser();
Laser laser2 = Laser();

SpaceShip spaceShip = SpaceShip(20, glm::vec3(0.065808f, 1.250000f, -2.0));
SpaceShip enemySpaceShip = SpaceShip(20, glm::vec3(-0.065f, 1.25f, -1.75));//glm::vec3(0.2f, 1.65f, 2.05)

std::vector<Core::RenderContext> lasersContexts{ models::laserContext1, models::laserContext2, models::laserContext3, models::laserContext4, models::laserContext5,
												models::laserContext6, models::laserContext7, models::laserContext8, models::laserContext9, models::laserContext10,
												models::laserContext11, models::laserContext12, models::laserContext13, models::laserContext14, models::laserContext15,
												models::laserContext16, models::laserContext17, models::laserContext18, models::laserContext19, models::laserContext20 };


std::vector<glm::vec3> lasersLightPos{ laserLightPos0, laserLightPos1, laserLightPos2, laserLightPos3, laserLightPos4, laserLightPos5, laserLightPos6, laserLightPos7,
									   laserLightPos8, laserLightPos9, laserLightPos10, laserLightPos11, laserLightPos12, laserLightPos13, laserLightPos14, laserLightPos15,
									   laserLightPos15, laserLightPos16, laserLightPos17, laserLightPos18, laserLightPos19};
//glm::vec3 lasersLightPos[21] = { laserLightPos0, laserLightPos1, laserLightPos2, laserLightPos3, laserLightPos4, laserLightPos5, laserLightPos6, laserLightPos7,
//									   laserLightPos8, laserLightPos9, laserLightPos10, laserLightPos11, laserLightPos12, laserLightPos13, laserLightPos14, laserLightPos15,
//									   laserLightPos16, laserLightPos17, laserLightPos18, laserLightPos19 };

std::vector<char*> figuresPathToObject{ "./models/pawnFigure.obj", "./models/towerFigure.obj", "./models/horseFigure.obj" };
std::vector<Core::RenderContext> figuresContexts{ models::pawnFigureContext, models::towerFigureContext, models::horseFigureContext };

std::vector<Laser> lasers;

glm::mat4 enemiesMatrixModel;
float enemyTime;
float enemyAngle = -180.0f;
float enemyShipAxisX = 0.0f;
float enemyShipAxisY = 1.0f;
float enemyShipAxisZ = 0.0f;

float startEnemy = 0;



glm::vec3 pawnCoord;
glm::vec3 towerCoord;
glm::vec3 horseCoord;
int figuresCount;

glm::vec3 figureCoord1;
glm::vec3 figureCoord2;
glm::vec3 figureCoord3;

glm::vec3 figure1Color;
glm::vec3 figure2Color;
glm::vec3 figure3Color;

Core::RenderContext figureRandomContext1;
Core::RenderContext figureRandomContext2;
Core::RenderContext figureRandomContext3;

bool laserTexture = false;


void updateDeltaTime(float time) {
	if (lastTime < 0) {
		lastTime = time;
		return;
	}

	deltaTime = time - lastTime;
	if (deltaTime > 0.1) deltaTime = 0.1;
	lastTime = time;
}
glm::mat4 createCameraMatrix()
{
	glm::vec3 cameraSide = glm::normalize(glm::cross(cameraDir, glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 cameraUp = glm::normalize(glm::cross(cameraSide, cameraDir));
	glm::mat4 cameraRotrationMatrix = glm::mat4({
		cameraSide.x,cameraSide.y,cameraSide.z,0,
		cameraUp.x,cameraUp.y,cameraUp.z ,0,
		-cameraDir.x,-cameraDir.y,-cameraDir.z,0,
		0.,0.,0.,1.,
		});
	cameraRotrationMatrix = glm::transpose(cameraRotrationMatrix);
	glm::mat4 cameraMatrix = cameraRotrationMatrix * glm::translate(-cameraPos);

	return cameraMatrix;
}

glm::mat4 createPerspectiveMatrix()
{

	glm::mat4 perspectiveMatrix;
	float n = 0.05;
	float f = 20.;
	float a1 = glm::min(aspectRatio, 1.f);
	float a2 = glm::min(1 / aspectRatio, 1.f);
	perspectiveMatrix = glm::mat4({
		1,0.,0.,0.,
		0.,aspectRatio,0.,0.,
		0.,0.,(f + n) / (n - f),2 * f * n / (n - f),
		0.,0.,-1.,0.,
		});


	perspectiveMatrix = glm::transpose(perspectiveMatrix);

	return perspectiveMatrix;
}

void drawObjectDepth(Core::RenderContext context, glm::mat4 viewProjectionMatrix, glm::mat4 modelMatrix) {

	glUniformMatrix4fv(glGetUniformLocation(programDepth, "viewProjectionMatrix"), 1, GL_FALSE, (float*)&viewProjectionMatrix);
	glUniformMatrix4fv(glGetUniformLocation(programDepth, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
	Core::DrawContext(context);
}

void drawObjectPBR(Core::RenderContext& context, glm::mat4 modelMatrix, glm::vec3 color, float roughness, float metallic) {

	glm::mat4 viewProjectionMatrix = createPerspectiveMatrix() * createCameraMatrix();
	glm::mat4 transformation = viewProjectionMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	glUniform1f(glGetUniformLocation(program, "exposition"), exposition);

	glUniform1f(glGetUniformLocation(program, "roughness"), roughness);
	glUniform1f(glGetUniformLocation(program, "metallic"), metallic);

	glUniform3f(glGetUniformLocation(program, "color"), color.x, color.y, color.z);

	glUniform3f(glGetUniformLocation(program, "cameraPos"), cameraPos.x, cameraPos.y, cameraPos.z);

	glUniform3f(glGetUniformLocation(program, "sunDir"), sunDir.x, sunDir.y, sunDir.z);
	glUniform3f(glGetUniformLocation(program, "sunColor"), sunColor.x, sunColor.y, sunColor.z);

	glUniform3f(glGetUniformLocation(program, "lightPos"), pointlightPos.x, pointlightPos.y, pointlightPos.z);
	glUniform3f(glGetUniformLocation(program, "lightColor"), pointlightColor.x, pointlightColor.y, pointlightColor.z);
	
	//lasers light
	for (int i = 0; i < lasers.size(); i++) {
		std::string stringLaserPos = "laserLightPos";
		stringLaserPos += std::to_string(i);
		if (lasers[i].isLaserFly()) {
			glUniform3f(glGetUniformLocation(programTex, "laserLightColor"), laserLightColor.x, laserLightColor.y, laserLightColor.z);
			glUniform3f(glGetUniformLocation(programTex, stringLaserPos.c_str()), lasersLightPos[i].x, lasersLightPos[i].y, lasersLightPos[i].z);
			/*glUniform3fv(glGetUniformLocation(program, "lasersLightPos"), 3, &lasersLightPos[i][0]);
			glUniform1i(glGetUniformLocation(program, "lasersLightPosArrayIndex"), i);*/
		}
	}

	glUniform3f(glGetUniformLocation(program, "spotlightConeDir"), spotlightConeDir.x, spotlightConeDir.y, spotlightConeDir.z);
	glUniform3f(glGetUniformLocation(program, "spotlightPos"), spotlightPos.x, spotlightPos.y, spotlightPos.z);
	glUniform3f(glGetUniformLocation(program, "spotlightColor"), spotlightColor.x, spotlightColor.y, spotlightColor.z);
	glUniform1f(glGetUniformLocation(program, "spotlightPhi"), spotlightPhi);

	//For shadows
	glm::mat4 lightVPSun = glm::ortho(-3.f, 2.3f, -1.3f, 3.f, -1.0f, 40.0f) * glm::lookAt(sunPos, sunPos - sunDir, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(glGetUniformLocation(program, "LightVPSun"), 1, GL_FALSE, (float*)&lightVPSun);
	glUniform1i(glGetUniformLocation(program, "depthMapSun"), 2);
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, depthMapSun);

	Core::DrawContext(context);
}




void drawObjectTexture(Core::RenderContext& context, glm::mat4 modelMatrix, GLuint textureID,  glm::vec3 color, float roughness, float metallic) {
	glUseProgram(programTex);
	glm::mat4 viewProjectionMatrix = createPerspectiveMatrix() * createCameraMatrix();
	glm::mat4 transformation = viewProjectionMatrix * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(programTex, "transformation"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(programTex, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
	
	glUniform1f(glGetUniformLocation(programTex, "roughness"), roughness);
	glUniform1f(glGetUniformLocation(programTex, "metallic"), metallic);
	glUniform3f(glGetUniformLocation(programTex, "color"), color.x, color.y, color.z);

	glUniform1f(glGetUniformLocation(programTex, "exposition"), exposition);

	glUniform3f(glGetUniformLocation(programTex, "cameraPos"), cameraPos.x, cameraPos.y, cameraPos.z);

	glUniform3f(glGetUniformLocation(programTex, "sunDir"), sunDir.x, sunDir.y, sunDir.z);
	glUniform3f(glGetUniformLocation(programTex, "sunColor"), sunColor.x, sunColor.y, sunColor.z);

	glUniform3f(glGetUniformLocation(programTex, "lightPos"), pointlightPos.x, pointlightPos.y, pointlightPos.z);
	glUniform3f(glGetUniformLocation(programTex, "lightColor"), pointlightColor.x, pointlightColor.y, pointlightColor.z);


	//lasers light
	for (int i = 0; i < lasers.size(); i++) {
		std::string stringLaserPos = "laserLightPos";
		stringLaserPos += std::to_string(i);
		if (lasers[i].isLaserFly()) {
			glUniform3f(glGetUniformLocation(programTex, "laserLightColor"), laserLightColor.x, laserLightColor.y, laserLightColor.z);
			glUniform3f(glGetUniformLocation(programTex, stringLaserPos.c_str()), lasersLightPos[i].x, lasersLightPos[i].y, lasersLightPos[i].z);
			/*glUniform3fv(glGetUniformLocation(program, "lasersLightPos"), 3, &lasersLightPos[i][0]);
			glUniform1i(glGetUniformLocation(program, "lasersLightPosArrayIndex"), i);*/
		}
	}

	glUniform3f(glGetUniformLocation(programTex, "spotlightConeDir"), spotlightConeDir.x, spotlightConeDir.y, spotlightConeDir.z);
	glUniform3f(glGetUniformLocation(programTex, "spotlightPos"), spotlightPos.x, spotlightPos.y, spotlightPos.z);
	glUniform3f(glGetUniformLocation(programTex, "spotlightColor"), spotlightColor.x, spotlightColor.y, spotlightColor.z);
	glUniform1f(glGetUniformLocation(programTex, "spotlightPhi"), spotlightPhi);

	//For shadows
	glm::mat4 lightVPSun = glm::ortho(-3.f, 2.3f, -1.3f, 3.f, -1.0f, 40.0f) * glm::lookAt(sunPos, sunPos - sunDir, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(glGetUniformLocation(programTex, "LightVPSun"), 1, GL_FALSE, (float*)&lightVPSun);
	glUniform1i(glGetUniformLocation(programTex, "depthMapSun"), 2);
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, depthMapSun);

	Core::SetActiveTexture(textureID, "colorTexture", programTex, 0);
	Core::DrawContext(context);
	glUseProgram(0);
}


void renderShadowapSun(GLuint depthMapFBO, glm::mat4 lightVP) {
	float time = glfwGetTime();
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	//uzupelnij o renderowanie glebokosci do tekstury
	glUseProgram(programDepth);

	//ustawianie przestrzeni rysowania 
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	//bindowanie FBO
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//czyszczenie mapy głębokości 
	glClear(GL_DEPTH_BUFFER_BIT);
	//ustawianie programu
	glUseProgram(programDepth);

	drawObjectDepth(sphereContext, lightVP, glm::translate(pointlightPos) * glm::scale(glm::vec3(0.1)) * glm::eulerAngleY(time / 3) * glm::translate(glm::vec3(4.f, 0, 0)) * glm::scale(glm::vec3(0.3f)));

	drawObjectDepth(sphereContext,
		lightVP, glm::translate(pointlightPos) * glm::scale(glm::vec3(0.1)) * glm::eulerAngleY(time / 3) * glm::translate(glm::vec3(4.f, 0, 0)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(1.f, 0, 0)) * glm::scale(glm::vec3(0.1f)));

	drawObjectDepth(models::vase1Context, lightVP, glm::mat4());
	//drawObjectDepth(models::vase2Context, lightVP, glm::mat4());

	drawObjectDepth(models::tvTableContext, lightVP, glm::mat4());
	drawObjectDepth(models::tableContext, lightVP, glm::mat4());
	drawObjectDepth(models::doorContext, lightVP, glm::mat4());
	drawObjectDepth(models::doorFrameContext, lightVP, glm::mat4());
	drawObjectDepth(models::tvContext, lightVP, glm::mat4());
	drawObjectDepth(models::tvScreen, lightVP, glm::mat4());
	drawObjectDepth(models::xThingContext, lightVP, glm::mat4());
	drawObjectDepth(models::planeContext, lightVP, glm::mat4());
	drawObjectDepth(models::roomInsideContext, lightVP, glm::mat4());
	drawObjectDepth(models::roomOutsideContext, lightVP, glm::mat4());
	drawObjectDepth(models::windowContext, lightVP, glm::mat4());
	drawObjectDepth(models::brokenWindowContext, lightVP, glm::mat4());
	drawObjectDepth(models::sofaContext, lightVP, glm::mat4());	
	drawObjectDepth(models::booksContext, lightVP, glm::mat4());

	drawObjectDepth(models::paintBackContext, lightVP, glm::mat4());
	drawObjectDepth(models::paintFaceContext, lightVP, glm::mat4());

	//FIGURES
	switch (figuresCount)
	{
	case 1:
		drawObjectDepth(figureRandomContext1, lightVP, glm::mat4() * glm::translate(figureCoord1) * glm::scale(glm::vec3(0.1f)));
		break;
	case 2:
		drawObjectDepth(figureRandomContext1, lightVP, glm::mat4() * glm::translate(figureCoord1) * glm::scale(glm::vec3(0.1f)));
		drawObjectDepth(figureRandomContext2, lightVP, glm::mat4() * glm::translate(figureCoord2) * glm::scale(glm::vec3(0.1f)));
		break;
	case 3:
		drawObjectDepth(figureRandomContext1, lightVP, glm::mat4() * glm::translate(figureCoord1) * glm::scale(glm::vec3(0.1f)));
		drawObjectDepth(figureRandomContext2, lightVP, glm::mat4() * glm::translate(figureCoord2) * glm::scale(glm::vec3(0.1f)));
		drawObjectDepth(figureRandomContext3, lightVP, glm::mat4() * glm::translate(figureCoord3) * glm::scale(glm::vec3(0.1f)));
		break;
	default:
		break;
	}

	glm::vec3 spaceshipSide = glm::normalize(glm::cross(spaceShip.getSpaceShipDir(), glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 spaceshipUp = glm::normalize(glm::cross(spaceshipSide, spaceShip.getSpaceShipDir()));
	glm::mat4 specshipCameraRotrationMatrix = glm::mat4({
		spaceshipSide.x,spaceshipSide.y,spaceshipSide.z,0,
		spaceshipUp.x,spaceshipUp.y,spaceshipUp.z ,0,
		-spaceShip.getSpaceShipDir().x,-spaceShip.getSpaceShipDir().y,-spaceShip.getSpaceShipDir().z,0,
		0.,0.,0.,1.,
		});

	drawObjectDepth(shipContext, lightVP, 
		glm::translate(spaceShip.getSpaceShipPos()) * specshipCameraRotrationMatrix * glm::eulerAngleY(glm::pi<float>()) /** glm::scale(glm::vec3(0.03f))*/);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WIDTH, HEIGHT);
}

//LASER COLLISION
void laser_collision(Laser laser) {
	float x = laser.getLaserPos().x;
	float y = laser.getLaserPos().y;
	float z = laser.getLaserPos().z;

	std::cout << x << " " << y << " " << z << std::endl;

	bool collision =
		/*(-1.83187 < spaceShipPos.x) &&
		(spaceShipPos.x < -1.8) &&*/
		(-1.84 > x) &&
		(x < 1.79) &&
		(1.01537 < y) &&
		(y < 1.97) &&
		(-0.249217 < z) &&
		(z < 0.750784);


	if (collision) {
		isWindowBroke = true;
		std::cout << "WINDOW BROKE";
	}

}

void drawLaser(Laser laser, Core::RenderContext laserContext, float dyst, int index) {

	float time = glfwGetTime();

	glm::vec3 laserSide = glm::normalize(glm::cross(laser.getLaserDir(), glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 laserUp = glm::normalize(glm::cross(laserSide, laser.getLaserDir()));
	glm::mat4 laserCameraRotrationMatrix = glm::mat4({
		laserSide.x, laserSide.y, laserSide.z,0,
		laserUp.x, laserUp.y, laserUp.z ,0,
		-laser.getLaserDir().x,-laser.getLaserDir().y,-laser.getLaserDir().z,0,
		0.,0.,0.,1.,
		});
	float t = time - laser.getTimeSinceShootLaser();


	glm::vec3 newLaserPos = laser.getLaserPos() + laser.getLaserDir() * (laser.getLaserSpeed() * (t + sin(0.2 * t)));
	laser.setLaserPos(newLaserPos);

	lasersLightPos[index] = glm::vec3(laser.getLaserPos().x + dyst, laser.getLaserPos().y, laser.getLaserPos().z);

	glUseProgram(programLaser);
	glm::mat4 laserTransformation = createPerspectiveMatrix() * createCameraMatrix() * glm::translate(glm::vec3(laser.getLaserPos().x + dyst, laser.getLaserPos().y, laser.getLaserPos().z)) * laserCameraRotrationMatrix * glm::eulerAngleY(glm::pi<float>()) * glm::scale(glm::vec3(0.03f));//glm::eulerAngleXYZ(glm::radians(15.0f), time * glm::radians(45.0f), glm::radians(0.0f));
	glUniformMatrix4fv(glGetUniformLocation(programLaser, "transformation"), 1, GL_FALSE, (float*)&laserTransformation);
	glUniform1f(glGetUniformLocation(programLaser, "time"), time);
	glUniform3f(glGetUniformLocation(programLaser, "laserColor"), laserColor.x, laserColor.y, laserColor.z);

	drawObjectPBR(laserContext,
		laserTransformation,
		glm::vec3(1.0f, 0.f, 0.f), 0.f, 0.f);
	
}


void enemyAIPilot(Core::RenderContext context) {
	float time = glfwGetTime();
	float enemyMoveSpeed = 0.02f;
	float angleSpeed = 0.05f * deltaTime * 60;
	float t = time - enemyTime;

	//enemySpaceShip.setSpaceShipPos(enemySpaceShip.getSpaceShipPos() + enemySpaceShip.getSpaceShipDir() + enemyMoveSpeed);

	//enemiesMatrixModel = enemiesMatrixModel * enemySpaceShip.getSpaceShipPos();

	//enemySpaceShip.setSpaceShipPos(enemySpaceShip.getSpaceShipPos() + enemySpaceShip.getSpaceShipDir() * enemyMoveSpeed);
	//enemySpaceShip.setSpaceShipPos(glm::vec3(-0.065, 0, 0));
	//glm::vec3(glm::eulerAngleX(30.f) * glm::vec4(spaceShip.getSpaceShipDir(), 0))


	//enemySpaceShip.setSpaceShipPos(glm::vec3(enemySpaceShip.getSpaceShipPos().x + enemySpaceShip.getSpaceShipDir().x, enemySpaceShip.getSpaceShipPos().y + enemySpaceShip.getSpaceShipDir().y * (0.02 * (t + sin(0.2 * t))), enemySpaceShip.getSpaceShipPos().z + enemySpaceShip.getSpaceShipDir().z));

	/*glm::vec3 newEnemyPos = glm::vec3(enemySpaceShip.getSpaceShipPos().x, enemySpaceShip.getSpaceShipPos().y + (0.1 * (t + sin(0.1 * t))), enemySpaceShip.getSpaceShipPos().z - (0.1 * (t + sin(0.1 * t))));
	enemySpaceShip.setSpaceShipPos(newEnemyPos);*/

	/*if (enemyAngle < 100) {
		enemyAngle = enemyAngle + 20.f;
		printf("spaceshipDir = glm::vec3(%ff);\n", enemyAngle);
	}*/
	enemiesMatrixModel = glm::translate(enemySpaceShip.getSpaceShipPos()) * glm::scale(glm::vec3(0.015f)) * glm::rotate(glm::mat4(), glm::radians(enemyAngle), glm::vec3(enemyShipAxisX, enemyShipAxisY, enemyShipAxisZ));


	if (startEnemy == 0) {
		startEnemy = enemiesMatrixModel[3][1];
		//enemiesMatrixModel = glm::translate(enemySpaceShip.getSpaceShipPos()) * glm::scale(glm::vec3(0.015f)) * glm::rotate(glm::mat4(), glm::radians(-180.0f), glm::vec3(.0, 1.0, .0));
		drawObjectPBR(context, enemiesMatrixModel, glm::vec3(0.3, 0.3, 0.5), 0.2, 1.0);

	}
	else if (float((round((enemiesMatrixModel[3][1] - startEnemy) * 100.0) / 100.0)) < 0.57f) {
		glm::vec3 newEnemyPos = glm::vec3(enemySpaceShip.getSpaceShipPos().x, enemySpaceShip.getSpaceShipPos().y + (0.5 * (t + sin(0.5 * t))), enemySpaceShip.getSpaceShipPos().z - (0.5 * (t + sin(0.5 * t))));
		enemySpaceShip.setSpaceShipPos(newEnemyPos);

		enemiesMatrixModel *= glm::translate(enemySpaceShip.getSpaceShipPos()) * glm::rotate(glm::mat4(), glm::radians(time * -10), glm::vec3(1, 0, 0));
		//printf("minus = %f;\n", float(round((enemiesMatrixModel[3][1] - startEnemy) * 100.0) / 100.0));
		drawObjectPBR(context, enemiesMatrixModel, glm::vec3(0.3, 0.3, 0.5), 0.2, 1.0);
	}
	/*else if (float((round((enemiesMatrixModel[3][1] - startEnemy) * 100.0) / 100.0)) > 0.57f) {
		glm::vec3 newEnemyPos = glm::vec3(enemySpaceShip.getSpaceShipPos().x, enemySpaceShip.getSpaceShipPos().y, enemySpaceShip.getSpaceShipPos().z + (0.5 * (t + sin(0.5 * t))));
		enemySpaceShip.setSpaceShipPos(newEnemyPos);

		enemiesMatrixModel *= glm::translate(enemySpaceShip.getSpaceShipPos()) * glm::rotate(glm::mat4(), glm::radians(time * -10), glm::vec3(0, 0, 1));

		printf("enemyMatrix(0) = %ff %ff %ff %ff\nenemyMatrix(1) = %ff %ff %ff %ff\nenemyMatrix(2) = %ff %ff %ff %ff\nenemyMatrix(3) = %ff %ff %ff %ff\n\n\n", enemiesMatrixModel[0][0], enemiesMatrixModel[0][1], enemiesMatrixModel[0][2], enemiesMatrixModel[0][3], enemiesMatrixModel[1][0], enemiesMatrixModel[1][1], enemiesMatrixModel[1][2], enemiesMatrixModel[1][3], enemiesMatrixModel[2][0], enemiesMatrixModel[2][1], enemiesMatrixModel[2][2], enemiesMatrixModel[2][3], enemiesMatrixModel[3][0], enemiesMatrixModel[3][1], enemiesMatrixModel[3][2], enemiesMatrixModel[3][3]);



		drawObjectPBR(context, enemiesMatrixModel, glm::vec3(0.3, 0.3, 0.5), 0.2, 1.0);
	}*/
	else if (float((round((enemiesMatrixModel[3][1] - startEnemy) * 100.0) / 100.0)) == 0.57f) {
		enemyShipAxisX = 1.0f;
		enemyShipAxisY = 0.0f;
		printf("minus = %f;\n", float(round((enemiesMatrixModel[3][1] - startEnemy) * 100.0) / 100.0));

		glm::vec3 newEnemyPos = glm::vec3(enemySpaceShip.getSpaceShipPos().x, enemySpaceShip.getSpaceShipPos().y, enemySpaceShip.getSpaceShipPos().z + (1.5 * (t + sin(1.5 * t))));
		enemySpaceShip.setSpaceShipPos(newEnemyPos);

		enemiesMatrixModel *= glm::translate(enemySpaceShip.getSpaceShipPos()) * glm::rotate(glm::mat4(), glm::radians(enemyAngle), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(), glm::radians(time * -10), glm::vec3(0, 0, 1));
		drawObjectPBR(context, enemiesMatrixModel, glm::vec3(0.3, 0.3, 0.5), 0.2, 1.0);
	}


	//enemiesMatrixModel *= glm::translate(enemySpaceShip.getSpaceShipPos()) * glm::rotate(glm::mat4(), glm::radians(time * -10), glm::vec3(1, 0, 0));// + glm::eulerAngleX(enemyAngle + 50.f);

	//enemyAngle = enemyAngle + 50.f;// * glm::rotate(glm::mat4(), glm::radians(time * -180.0f), glm::vec3(1.0, .0, .0));
	//drawObjectPBR(context, enemiesMatrixModel, glm::vec3(0.3, 0.3, 0.5), 0.2, 1.0);

}

void drawSkybox(Core::RenderContext& context, GLuint textureID) {
	
	glDisable(GL_DEPTH_TEST);
	glUseProgram(programSkybox);
	glm::mat4 viewProjectionMatrix = createPerspectiveMatrix() * createCameraMatrix();
	glm::mat4 pos = glm::mat4({
	   1,0.,0.,cameraPos.x,
	   0.,1.,0.,cameraPos.y,
	   0.,0.,1.,cameraPos.z,
	   0.,0.,0.,1.,
		});


	pos = glm::transpose(pos);
	glm::mat4 transformation = viewProjectionMatrix * pos;
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "transformation"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "modelMatrix"), 1, GL_FALSE, (float*)&pos);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	Core::DrawContext(context);
	glEnable(GL_DEPTH_TEST);
}


void initDepthMap()
{
	glGenFramebuffers(1, &depthMapFBOSun);

	glGenTextures(1, &depthMapSun);
	glBindTexture(GL_TEXTURE_2D, depthMapSun);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBOSun);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapSun, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

glm::vec3 randomFiguresCoord() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> distributionX(-0.2, 0.2);
    double random_x_number = floor(distributionX(generator) / 0.01) * 0.01;
	
	std::uniform_real_distribution<double> distributionZ(-0.13, 0.3);
	double random_z_number = floor(distributionZ(generator) / 0.01) * 0.01;

	return glm::vec3(random_x_number, 0.58, random_z_number);
}

int randomFiguresCount() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(1, 3);

	int random_number = distribution(generator);
	
	return random_number;
}

Core::RenderContext randomFiguresContext() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, 2);

	int random_number = distribution(generator);

	return figuresContexts[random_number];
}

glm::vec3  blackOrWhiteFigureColor() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, 1);

	int random_number = distribution(generator);

	if (random_number == 0) {
		return glm::vec3(0.01, 0.01, 0.01);
	}
	else {
		return glm::vec3(0.9, 0.9, 0.9);
	}
}


void renderScene(GLFWwindow* window)
{
	glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float time = glfwGetTime();
	updateDeltaTime(time);

	glm::mat4 lightVPSun = glm::ortho(-3.f, 2.3f, -1.3f, 3.f, -1.0f, 40.0f) * glm::lookAt(sunPos, sunPos - sunDir, glm::vec3(0, 1, 0));

	renderShadowapSun(depthMapFBOSun, lightVPSun);

	drawSkybox(skyboxContext, texture::skybox);

	//space lamp
	glUseProgram(programSun);
	glm::mat4 viewProjectionMatrix = createPerspectiveMatrix() * createCameraMatrix();
	glm::mat4 transformation = viewProjectionMatrix * glm::translate(pointlightPos) * glm::scale(glm::vec3(0.1));
	glUniformMatrix4fv(glGetUniformLocation(programSun, "transformation"), 1, GL_FALSE, (float*)&transformation);
	glUniform3f(glGetUniformLocation(programSun, "color"), sunColor.x / 2, sunColor.y / 2, sunColor.z / 2);
	glUniform1f(glGetUniformLocation(programSun, "exposition"), exposition);
	Core::DrawContext(sphereContext);

	glUseProgram(program);

	drawObjectPBR(sphereContext, glm::translate(pointlightPos) * glm::scale(glm::vec3(0.1)) * glm::eulerAngleY(time / 3) * glm::translate(glm::vec3(4.f, 0, 0)) * glm::scale(glm::vec3(0.3f)), glm::vec3(0.2, 0.7, 0.3), 0.3, 0.0);

	drawObjectPBR(sphereContext,
		glm::translate(pointlightPos) * glm::scale(glm::vec3(0.1)) * glm::eulerAngleY(time / 3) * glm::translate(glm::vec3(4.f, 0, 0)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(1.f, 0, 0)) * glm::scale(glm::vec3(0.1f)),
		glm::vec3(0.5, 0.5, 0.5), 0.7, 0.0);

	//drawObjectPBR(models::booksContext, glm::mat4(), glm::vec3(0.420f, 0.212f, 0.089f), 0.2f, 0.0f);

	//drawObjectPBR(models::vase1Context, glm::mat4(), glm::vec3(0.320f, 0.11f, 0.131f), 0.2f, 0.0f);
	//drawObjectPBR(models::vase2Context, glm::mat4(), glm::vec3(0.4f, 0.2f, 0.1f), 0.2f, 0.0f);

	//drawObjectPBR(models::roomOutsideContext, glm::mat4(), glm::vec3(0.9f, 0.9f, 0.9f), 0.8f, 0.0f);
	//drawObjectPBR(models::tvContext, glm::mat4(), glm::vec3(1.f, 1.f, 1.f), 0.5f, 1.0f);

	//FIGURES
	switch (figuresCount)
	{
	case 1:
		drawObjectPBR(figureRandomContext1, glm::mat4() * glm::translate(figureCoord1) * glm::scale(glm::vec3(0.1f)), figure1Color, 0.2f, 0.0f);
		break;
	case 2:
		drawObjectPBR(figureRandomContext1, glm::mat4() * glm::translate(figureCoord1) * glm::scale(glm::vec3(0.1f)), figure1Color, 0.2f, 0.0f);
		drawObjectPBR(figureRandomContext2, glm::mat4() * glm::translate(figureCoord2) * glm::scale(glm::vec3(0.1f)), figure2Color, 0.2f, 0.0f);
		break;
	case 3:
		drawObjectPBR(figureRandomContext1, glm::mat4() * glm::translate(figureCoord1) * glm::scale(glm::vec3(0.1f)), figure1Color, 0.2f, 0.0f);
		drawObjectPBR(figureRandomContext2, glm::mat4() * glm::translate(figureCoord2) * glm::scale(glm::vec3(0.1f)), figure2Color, 0.2f, 0.0f);
		drawObjectPBR(figureRandomContext3, glm::mat4() * glm::translate(figureCoord3) * glm::scale(glm::vec3(0.1f)), figure3Color, 0.2f, 0.0f);
		break;
	default:
		break;
	}
	
	//drawObjectPBR(models::sofaContext, glm::mat4(), glm::vec3(0.620f, 0.313f, 0.131f), 0.2f, 0.0f);
	//drawObjectPBR(models::xThingContext, glm::mat4(), glm::vec3(0.10039f, 0.018356f, 0.001935f), 0.1f, 0.0f);
	//drawObjectPBR(models::planeContext, glm::mat4(), glm::vec3(0.402978f, 0.120509f, 0.057729f), 0.2f, 0.0f);
	
	//drawObjectPBR(models::tableContext, glm::mat4(), glm::vec3(0.428691f, 0.08022f, 0.036889f), 0.2f, 0.0f);


	//drawObjectPBR(models::roofContext, glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
	
	
	drawObjectTexture(models::doorContext, glm::mat4(), texture::door, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);

	
	if (isWindowBroke)
	{
		drawObjectTexture(models::brokenWindowContext, glm::mat4(), texture::door, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	}
	else
	{
		drawObjectTexture(models::windowContext, glm::mat4(), texture::door, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	}
	
	
	
	
	drawObjectTexture(models::doorFrameContext, glm::mat4(), texture::door, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);

	drawObjectTexture(models::tvTableContext, glm::mat4(), texture::tvTable, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	drawObjectTexture(models::tvScreen, glm::mat4(), texture::tvscreen, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	drawObjectTexture(models::tvContext, glm::mat4(), texture::tv, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	drawObjectTexture(models::booksContext, glm::mat4(), texture::books, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	drawObjectTexture(models::vase1Context, glm::mat4(), texture::vase1, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);

	drawObjectTexture(models::tableContext, glm::mat4(), texture::table, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	drawObjectTexture(models::planeContext, glm::mat4(), texture::floor, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	drawObjectTexture(models::xThingContext, glm::mat4(), texture::xThing, glm::vec3(0.9f, 0.9f, 0.9f), 0.1f, 0.0f);
	drawObjectTexture(models::sofaContext, glm::mat4(), texture::sofa, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);
	drawObjectTexture(models::roofContext, glm::mat4(), texture::roof, glm::vec3(0.9f, 0.9f, 0.9f), 0.8f, 0.0f);
	drawObjectTexture(models::roomInsideContext, glm::mat4(), texture::walls, glm::vec3(0.9f, 0.9f, 0.9f), 0.8f, 0.0f);


	drawObjectTexture(models::paintBackContext, glm::mat4(), texture::paintBack, glm::vec3(0.9f, 0.9f, 0.9f), 0.8f, 0.0f);
	drawObjectTexture(models::paintFaceContext, glm::mat4(), texture::paintFace, glm::vec3(0.9f, 0.9f, 0.9f), 0.8f, 0.0f);


	glm::vec3 spaceshipSide = glm::normalize(glm::cross(spaceShip.getSpaceShipDir(), glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 spaceshipUp = glm::normalize(glm::cross(spaceshipSide, spaceShip.getSpaceShipDir()));
	glm::mat4 specshipCameraRotrationMatrix = glm::mat4({
		spaceshipSide.x,spaceshipSide.y,spaceshipSide.z,0,
		spaceshipUp.x,spaceshipUp.y,spaceshipUp.z ,0,
		-spaceShip.getSpaceShipDir().x,-spaceShip.getSpaceShipDir().y,-spaceShip.getSpaceShipDir().z,0,
		0.,0.,0.,1.,
		});

	drawObjectTexture(shipContext,glm::translate(spaceShip.getSpaceShipPos()) * specshipCameraRotrationMatrix * glm::eulerAngleY(glm::pi<float>()),texture::ship, glm::vec3(0.9f, 0.9f, 0.9f), 0.2f, 0.0f);


	enemyTime = time;


	//enemyAIPilot(enemyShipContext);
	
	spotlightPos = spaceShip.getSpaceShipPos() + 0.2 * spaceShip.getSpaceShipDir();
	spotlightConeDir = spaceShip.getSpaceShipDir();

	glUseProgram(programTex);
	//draw lasers
	for (int i = 0; i < lasers.size(); i++) {
		if (lasers[i].isLaserFly()) {
			laserColor = glm::vec3(1, 0, 0);
			glUniform3f(glGetUniformLocation(programLaser, "laserColor"), laserColor.x, laserColor.y, laserColor.z);
			glUniform1f(glGetUniformLocation(programTex, "time"), time);
			
			drawLaser(lasers[i], lasersContexts[i], 0.1, i);
			drawLaser(lasers[i], lasersContexts[i], -0.1, i);

		}
	}

	

	//test depth buffer
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programTest);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMapSun);
	Core::DrawContext(models::testContext);*/

	glUseProgram(0);
	glfwSwapBuffers(window);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / float(height);
	glViewport(0, 0, width, height);
	WIDTH = width;
	HEIGHT = height;
}
void loadModelToContext(std::string path, Core::RenderContext& context)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	context.initFromAssimpMesh(scene->mMeshes[0]);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	float angleSpeed = 0.05f * deltaTime * 60;

	if (ypos < startCursorYPos) {
		startCursorYPos = ypos;
		spaceShip.setSpaceShipDir(glm::vec3(glm::eulerAngleX(angleSpeed) * glm::vec4(spaceShip.getSpaceShipDir(), 0)));
	}
	else if (ypos > startCursorYPos) {
		startCursorYPos = ypos;
		spaceShip.setSpaceShipDir(glm::vec3(glm::eulerAngleX(-angleSpeed) * glm::vec4(spaceShip.getSpaceShipDir(), 0)));
	}

	//spaceShip.setSpaceShipDir(glm::vec3(glm::eulerAngleZ(angleSpeed) * glm::vec4(spaceShip.getSpaceShipDir(), 0)));
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	std::cout << "x = " << spaceShip.getSpaceShipPos().x << "  y = " << spaceShip.getSpaceShipPos().y << "  z = " << spaceShip.getSpaceShipPos().z << "\n";

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		drawLaserShot = true;

		spaceShip.setAttackDecision(true);
		/*spaceShip.laserPreparationBeforeShoot(glfwGetTime());*/


		for (int i = 0; i < lasers.size(); i++) {
			if (!lasers[i].isLaserFly() && spaceShip.getAttackDecision()) {
				lasers[i].setTimeSinceShootLaser(glfwGetTime());
				lasers[i].setLaserDir(spaceShip.getSpaceShipDir());
				lasers[i].setLaserPos(spaceShip.getSpaceShipPos());
				lasers[i].setLaserSpeed(5);
				lasers[i].setLaserFly(true);
				spaceShip.setAttackDecision(false);


				std::cout << "i = " << i << " " << "laser fly = " << lasers[i].isLaserFly() << "\n";
			}
		}
	}

}


GLuint LoadSkybox(char* filepath[6])
{
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	int w, h;
	unsigned char* data;
	for (unsigned int i = 0; i < 6; i++)
	{
		unsigned char* image = SOIL_load_image(filepath[i], &w, &h, 0, SOIL_LOAD_RGBA);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image
		);

	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);

	return id;
}


void init(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glfwGetCursorPos(window, &startCursorXPos, &startCursorYPos);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glfwSetCursorPosCallback(window, cursor_position_callback);

	initDepthMap();


	pawnCoord = randomFiguresCoord();
	towerCoord = randomFiguresCoord();
	horseCoord = randomFiguresCoord();

	glEnable(GL_DEPTH_TEST);
	program = shaderLoader.CreateProgram("shaders/shader_9_1.vert", "shaders/shader_9_1.frag");
	programTest = shaderLoader.CreateProgram("shaders/test.vert", "shaders/test.frag");
	programSun = shaderLoader.CreateProgram("shaders/shader_8_sun.vert", "shaders/shader_8_sun.frag");

	programDepth = shaderLoader.CreateProgram("shaders/shader_shadowap_sun.vert", "shaders/shader_shadowap_sun.frag");

	programLaser = shaderLoader.CreateProgram("shader_laser.vert", "shader_laser.frag");

	programSkybox = shaderLoader.CreateProgram("shaders/shader_skybox.vert", "shaders/shader_skybox.frag");

	programTex = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");

	programParallaxMap = shaderLoader.CreateProgram("shaders/shader_parallax.vert", "shaders/shader_parallax.frag");

	loadModelToContext("./models/sphere.obj", sphereContext);
	loadModelToContext("./models/spaceShip.obj", shipContext);

	//loadModelToContext("./models/enemyShip.obj", enemyShipContext);

	loadModelToContext("./models/cube.obj", skyboxContext);

	loadModelToContext("./models/books.obj", models::booksContext);
	loadModelToContext("./models/sofa.obj", models::sofaContext);
	loadModelToContext("./models/tvTable.obj", models::tvTableContext);
	loadModelToContext("./models/table.obj", models::tableContext);

	loadModelToContext("./models/paintingFace.obj", models::paintFaceContext);
	loadModelToContext("./models/paintingBack.obj", models::paintBackContext);

	loadModelToContext("./models/doorFrame.obj", models::doorFrameContext);
	loadModelToContext("./models/door.obj", models::doorContext);

	loadModelToContext("./models/vase1.obj", models::vase1Context);
	loadModelToContext("./models/vase2.obj", models::vase2Context);

	loadModelToContext("./models/brokenWindow.obj", models::brokenWindowContext);

	loadModelToContext("./models/TV.obj", models::tvContext);
	loadModelToContext("./models/TVscreen.obj", models::tvScreen);
	loadModelToContext("./models/x.obj", models::xThingContext);
	loadModelToContext("./models/plane.obj", models::planeContext);
	loadModelToContext("./models/room.obj", models::roomInsideContext);
	loadModelToContext("./models/roomOutside.obj", models::roomOutsideContext);
	loadModelToContext("./models/roof.obj", models::roofContext);
	//loadModelToContext("./models/spaceShip.obj", models::spaceshipContext);
	loadModelToContext("./models/sphere.obj", models::sphereContext);
	loadModelToContext("./models/window.obj", models::windowContext);
	loadModelToContext("./models/test.obj", models::testContext);

	loadModelToContext("./models/pawnFigure.obj", models::pawnFigureContext);
	loadModelToContext("./models/towerFigure.obj", models::towerFigureContext);
	loadModelToContext("./models/horseFigure.obj", models::horseFigureContext);

	for (int i = 0; i < figuresContexts.size(); i++) {
		loadModelToContext(figuresPathToObject[i], figuresContexts[i]);
	}


	texture::sofa = Core::LoadTexture("textures/sofa1.jpg");
	texture::xThing = Core::LoadTexture("textures/xThing.png");
	texture::vase1 = Core::LoadTexture("textures/VaseColor.png");
	
	//texture::paintFace = Core::LoadTexture("textures/paintingFace.jpg");
	texture::paintFace = Core::LoadTexture("parallax/paintingParallaxRes.jpg");

	//texture::paintFace = Core::LoadTexture("textures/paintingFace.jpg");
	texture::door = Core::LoadTexture("textures/door_texture_light.png");
	texture::tvTable = Core::LoadTexture("textures/white_wood.png");

	texture::paintBack = Core::LoadTexture("textures/paintingBack.jpg");//???


	texture::table = Core::LoadTexture("textures/coffeTable.jpg");

	texture::floor = Core::LoadTexture("textures/floor.jpg");
	texture::walls = Core::LoadTexture("textures/123.jpg");
	texture::ship = Core::LoadTexture("textures/ship.jpg");
	//texture::roof = Core::LoadTexture("textures/roof.jpg");
	texture::roof = Core::LoadTexture("textures/paintingFace.jpg");
	texture::books = Core::LoadTexture("textures/floor.jpg");
	texture::tvscreen = Core::LoadTexture("textures/tvscreen.jpg");
	texture::tv = Core::LoadTexture("textures/tv.jpg");

	
	texture::skybox = LoadSkybox(new char* [6]{ "skybox/posx.jpg",  "skybox/negx.jpg", "skybox/posy.jpg","skybox/negy.jpg",  "skybox/posz.jpg", "skybox/negz.jpg" });

	//lasersContexts.reserve(spaceShip.getMaxNumberOfLasers());

	for (int i = 0; i < spaceShip.getMaxNumberOfLasers(); i++) {
		loadModelToContext("./models/newlaser2.obj", lasersContexts[i]);

		lasers.push_back(Laser(spaceShip.getSpaceShipDir(), spaceShip.getSpaceShipPos(), 10, false));
			
	}
}

void shutdown(GLFWwindow* window)
{
	shaderLoader.DeleteProgram(program);
}



bool check_window_collision(int plus_or_minus) {

	float spaceShipX = 0.20445;
	float spaceShipY = 0.04875;
	float spaceShipZ = 0.16275;

	glm::vec3 spaceshipUp = glm::vec3(0.f, 1.f, 0.f);
	float moveSpeed = 0.02f * deltaTime * 60;

	glm::vec3 spaceShipPos = spaceShip.getSpaceShipPos() + (spaceShip.getSpaceShipDir() * moveSpeed) * plus_or_minus;

	//bool collision = (-1 < spaceShipPos.x < 1) && (0.0 < spaceShipPos.y < 0.9)  && (-1.5 < spaceShipPos.z < 0.5);
	
	if (isWindowBroke)
	{
		bool collision =
			/*(-1.83187 < spaceShipPos.x) &&
			(spaceShipPos.x < -1.8) &&*/
			(-1.5 + spaceShipX > spaceShipPos.x) &&
			(1.01537 + spaceShipY < spaceShipPos.y) &&
			(spaceShipPos.y < 1.97 - spaceShipY) &&
			(-0.249217 + spaceShipZ < spaceShipPos.z) &&
			(spaceShipPos.z < 0.750784 - spaceShipZ);

		return collision;
	}
	else
	{
		return false;
	}
	
	
}

bool check_room_collision(int plus_or_minus) {

	float spaceShipX = 0.20445 / 2;
	float spaceShipY = 0.04875 / 2;
	float spaceShipZ = 0.16275 / 2;

	glm::vec3 spaceshipUp = glm::vec3(0.f, 1.f, 0.f);
	float moveSpeed = 0.02f * deltaTime * 60;

	glm::vec3 spaceShipPos = spaceShip.getSpaceShipPos() + (spaceShip.getSpaceShipDir() * moveSpeed) * plus_or_minus;


	if ((spaceShipPos.x >= 2 + spaceShipX || spaceShipPos.x <= -2 - spaceShipX) ||
		(spaceShipPos.y >= 2.5 + spaceShipY || spaceShipPos.y <= 0.0 - spaceShipY) ||
		(spaceShipPos.z >= 2.5 + spaceShipZ  || spaceShipPos.z <= -2.5 - spaceShipZ))
	{
		return false;
	}
	else
	{
		if (check_window_collision(plus_or_minus)) {
			//printf("WINDOW 1");
			return false;
		}
		else {
			bool collision =
				spaceShipPos.z < -2.2 + spaceShipZ || spaceShipPos.z > 2.1 - spaceShipZ ||
				spaceShipPos.x < -1.72 + spaceShipX || spaceShipPos.x > 1.78 - spaceShipX ||
				spaceShipPos.y < 0.0 + spaceShipY || spaceShipPos.y > 2.2 - spaceShipY;
			return collision;
		}

	}

	
	
}

bool check_sofa_collision(int plus_or_minus) {

	float spaceShipX = 0.20445;
	float spaceShipY = 0.04875;
	float spaceShipZ = 0.16275;

	glm::vec3 spaceshipUp = glm::vec3(0.f, 1.f, 0.f);
	float moveSpeed = 0.02f * deltaTime * 60;

	glm::vec3 spaceShipPos = spaceShip.getSpaceShipPos() + (spaceShip.getSpaceShipDir() * moveSpeed) * plus_or_minus;

	//bool collision = (-1 < spaceShipPos.x < 1) && (0.0 < spaceShipPos.y < 0.9)  && (-1.5 < spaceShipPos.z < 0.5);
	bool collision = 
		(-1.07 - spaceShipX < spaceShipPos.x) &&
		(spaceShipPos.x < 1.05 + spaceShipX) &&
		(0.0 - spaceShipY < spaceShipPos.y) &&
		(spaceShipPos.y < 0.64 + spaceShipY) &&
		(-1.57 - spaceShipZ< spaceShipPos.z) &&
		(spaceShipPos.z < -0.49 + spaceShipZ);

	return collision;

	
}


//bool CollisionDetection(const std::vector<Vertex>& object1, const std::vector<Vertex>& object2) {
//	// Calculate the bounding box for object1
//	float minX1 = object1[0].x, maxX1 = object1[0].x;
//	float minY1 = object1[0].y, maxY1 = object1[0].y;
//	float minZ1 = object1[0].z, maxZ1 = object1[0].z;
//	for (int i = 1; i < object1.size(); i++) {
//		minX1 = min(minX1, object1[i].x);
//		maxX1 = max(maxX1, object1[i].x);
//		minY1 = min(minY1, object1[i].y);
//		maxY1 = max(maxY1, object1[i].y);
//		minZ1 = min(minZ1, object1[i].z);
//		maxZ1 = max(maxZ1, object1[i].z);
//	}
//
//	// Calculate the bounding box for object2
//	float minX2 = object2[0].x, maxX2 = object2[0].x;
//	float minY2 = object2[0].y, maxY2 = object2[0].y;
//	float minZ2 = object2[0].z, maxZ2 = object2[0].z;
//	for (int i = 1; i < object2.size(); i++) {
//		minX2 = min(minX2, object2[i].x);
//		maxX2 = max(maxX2, object2[i].x);
//		minY2 = min(minY2, object2[i].y);
//		maxY2 = max(maxY2, object2[i].y);
//		minZ2 = min(minZ2, object2[i].z);
//		maxZ2 = max(maxZ2, object2[i].z);
//	}
//
//	// Check for overlap in x, y, and z
//	if (maxX1 < minX2 || minX1 > maxX2) return false;
//	if (maxY1 < minY2 || minY1 > maxY2) return false;
//	if (maxZ1 < minZ2 || minZ1 > maxZ2) return false;
//
//	// Objects intersect
//	return true;
//}




//obsluga wejscia
void processInput(GLFWwindow* window)
{

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glm::vec3 spaceshipSide = glm::normalize(glm::cross(spaceShip.getSpaceShipDir(), glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 spaceshipUp = glm::vec3(0.f, 1.f, 0.f);
	float angleSpeed = 0.05f * deltaTime * 60;
	float moveSpeed = 0.02f * deltaTime * 60;
	

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (!check_room_collision(1) && !check_sofa_collision(1)) {
			spaceShip.setSpaceShipPos(spaceShip.getSpaceShipPos() + spaceShip.getSpaceShipDir() * moveSpeed);
		}
		//spaceshipPos += spaceshipDir * moveSpeed;
		
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (!check_room_collision(-1) && !check_sofa_collision(-1)) {
			spaceShip.setSpaceShipPos(spaceShip.getSpaceShipPos() - spaceShip.getSpaceShipDir() * moveSpeed);
		}
		//spaceshipPos -= spaceshipDir * moveSpeed;
		
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		//spaceshipPos += spaceshipSide * moveSpeed;
		if (!check_room_collision(1) && !check_sofa_collision(1)) {
			spaceShip.setSpaceShipPos(spaceShip.getSpaceShipPos() + spaceshipSide * moveSpeed);
		}

		
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		if (!check_room_collision(-1) && !check_sofa_collision(-1)) {
			spaceShip.setSpaceShipPos(spaceShip.getSpaceShipPos() - spaceshipSide * moveSpeed);
		}

		//spaceshipPos -= spaceshipSide * moveSpeed;

		
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		//spaceshipPos += spaceshipUp * moveSpeed;
		if ((spaceShip.getSpaceShipPos() + spaceshipUp * moveSpeed).y > 2.25) {
			std::cout << "Collision detected!" << std::endl;
		}
		else{
			spaceShip.setSpaceShipPos(spaceShip.getSpaceShipPos() + spaceshipUp * moveSpeed);
		}

	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		if ((spaceShip.getSpaceShipPos() + spaceshipUp * moveSpeed).y < 0.05) {
			std::cout << "Collision detected!" << std::endl;
		}
		else {
			spaceShip.setSpaceShipPos(spaceShip.getSpaceShipPos() - spaceshipUp * moveSpeed);
		}

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//spaceshipDir = glm::vec3(glm::eulerAngleY(angleSpeed) * glm::vec4(spaceShip.getSpaceShipDir(), 0));

		spaceShip.setSpaceShipDir(glm::vec3(glm::eulerAngleY(angleSpeed) * glm::vec4(spaceShip.getSpaceShipDir(), 0)));

		if (!spaceShip.getAttackDecision()) {
			//laser.setLaserDir(spaceShip.getSpaceShipDir());

			/*for (int i = 0; i < lasers.size(); i++) {
				lasers[i].setLaserDir(spaceShip.getSpaceShipDir());
			}*/
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//spaceshipDir = glm::vec3(glm::eulerAngleY(-angleSpeed) * glm::vec4(spaceShip.getSpaceShipDir(), 0));

		spaceShip.setSpaceShipDir(glm::vec3(glm::eulerAngleY(-angleSpeed) * glm::vec4(spaceShip.getSpaceShipDir(), 0)));

		if (!spaceShip.getAttackDecision()) {
			//laser.setLaserDir(spaceShip.getSpaceShipDir());

			/*for (int i = 0; i < lasers.size(); i++) {
				lasers[i].setLaserDir(spaceShip.getSpaceShipDir());
			}*/
		}
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		//spaceshipDir = glm::vec3(glm::eulerAngleY(-angleSpeed) * glm::vec4(spaceShip.getSpaceShipDir(), 0));

		figureRandomContext1 = randomFiguresContext();
		figureRandomContext2 = randomFiguresContext();
		figureRandomContext3 = randomFiguresContext();

		figure1Color = blackOrWhiteFigureColor();
		figure2Color = blackOrWhiteFigureColor();
		figure3Color = blackOrWhiteFigureColor();

		figuresCount = randomFiguresCount();

		figureCoord1 = randomFiguresCoord();
		figureCoord2 = randomFiguresCoord();
		figureCoord3 = randomFiguresCoord();
	}


	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		isWindowBroke = true;
	}


	cameraPos = spaceShip.getSpaceShipPos() - 0.5 * spaceShip.getSpaceShipDir() + glm::vec3(0, 1, 0) * 0.2f;
	cameraDir = spaceShip.getSpaceShipDir();

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		exposition -= 0.05;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		exposition += 0.05;

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		printf("spaceshipPos = glm::vec3(%ff, %ff, %ff);\n", spaceShip.getSpaceShipPos().x, spaceShip.getSpaceShipPos().y, spaceShip.getSpaceShipPos().z);
		printf("spaceshipDir = glm::vec3(%ff, %ff, %ff);\n", spaceShip.getSpaceShipDir().x, spaceShip.getSpaceShipDir().y, spaceShip.getSpaceShipDir().z);
	}

	//if(glfwGetKey(window, GLFW_MOUSE))

	//cameraDir = glm::normalize(-cameraPos);

}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		for (int i = 0; i < lasers.size(); i++) {
			if (lasers[i].isLaserFly()) {
				laser_collision(lasers[i]);
			}
		}

		renderScene(window);
		glfwPollEvents();
	}
}
//}