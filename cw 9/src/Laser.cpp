#include "Laser.h"
#include "glm.hpp"
#include "glew.h"
#include "objload.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Render_Utils.h"


Laser::Laser() {

}

Laser::Laser(glm::vec3 dirOfLaser, glm::vec3 posOfLaser, float speedOfLaser, bool lasFly) {
	this->laserDir = dirOfLaser;
	this->laserPos = posOfLaser;
	this->laserSpeed = speedOfLaser;
	this->laserFly = lasFly;
}

void Laser::setLaserDir(glm::vec3 dirOfLaser) {
	laserDir = dirOfLaser;
}

glm::vec3 Laser::getLaserDir() {
	return laserDir;
}

void Laser::setLaserPos(glm::vec3 posOfLaser) {
	laserPos = posOfLaser;
}

glm::vec3 Laser::getLaserPos() {
	return laserPos;
}

void Laser::setLaserSpeed(float speedOfLaser) {
	laserSpeed = speedOfLaser;
}

float Laser::getLaserSpeed() {
	return laserSpeed;
}

void Laser::setTimeSinceShootLaser(float tSinceShootLaser) {
	timeSinceShootLaser = tSinceShootLaser;
}

float Laser::getTimeSinceShootLaser() {
	return timeSinceShootLaser;
}

void Laser::setLaserContext(Core::RenderContext lasContext) {
	this->laserContext = lasContext;
}

Core::RenderContext Laser::getLaserContext() {
	return this->laserContext;
}

void Laser::setLaserFly(bool lasFly) {
	this->laserFly = lasFly;
}

bool Laser::isLaserFly() {
	return this->laserFly;
}
