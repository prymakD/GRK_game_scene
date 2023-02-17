#include "SpaceShip.h"
#include "glm.hpp"
#include "glew.h"
#include "objload.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Laser.h"


SpaceShip::SpaceShip() {

}

SpaceShip::SpaceShip(int numberOfLasers, glm::vec3 shipPos) {
	maxNumberOfLasers = numberOfLasers;
	numberOfLeftLasers = maxNumberOfLasers;
	gun.reserve(maxNumberOfLasers);

	this->spaceShipDir = glm::vec3(-0.490263f, 0.000000f, 0.871578f);
	this->spaceShipPos = shipPos;

	for (int i = 0; i < maxNumberOfLasers; i++) {
		gun.push_back(Laser(this->spaceShipDir, this->spaceShipPos, 0.01, false));
	}
}


void SpaceShip::setAttackDecision(bool attackDec) {
	attackDecision = attackDec;
}


bool SpaceShip::getAttackDecision() {
	return attackDecision;
}


void SpaceShip::setSpaceShipDir(glm::vec3 spShipDir) {
	spaceShipDir = spShipDir;
}

glm::vec3 SpaceShip::getSpaceShipDir() {
	return spaceShipDir;
}

void SpaceShip::setSpaceShipPos(glm::vec3 spShipPos) {
	spaceShipPos = spShipPos;
}

glm::vec3 SpaceShip::getSpaceShipPos() {
	return spaceShipPos;
}

void SpaceShip::setMaxNumberOfLasers(int numberOfLasers) {
	this->maxNumberOfLasers = numberOfLasers;
}

int SpaceShip::getMaxNumberOfLasers() {
	return this->maxNumberOfLasers;
}

void SpaceShip::setNumberOfLeftLasers(int numberOfLasers) {
	this->numberOfLeftLasers = numberOfLasers;
}

int SpaceShip::getNumberOfLeftLasers() {
	return this->numberOfLeftLasers;
}

void SpaceShip::setGun(std::vector<Laser> g) {
	this->gun = g;
}

std::vector<Laser> SpaceShip::getGun() {
	return this->gun;
}


void SpaceShip::laserPreparationBeforeShoot(float time) {

	if (this->numberOfLeftLasers > 0) {
		this->numberOfLeftLasers -= 1;
	}
	else if (this->numberOfLeftLasers == 0) {
		this->numberOfLeftLasers = this->maxNumberOfLasers;
		this->numberOfLeftLasers -= 1;
	}
	//this->numberOfLeftLasers -= 1;

	this->gun[this->numberOfLeftLasers].setTimeSinceShootLaser(time);
	this->gun[this->numberOfLeftLasers].setLaserDir(this->spaceShipDir);
	this->gun[this->numberOfLeftLasers].setLaserPos(this->spaceShipPos);
	this->gun[this->numberOfLeftLasers].setLaserSpeed(0.01);
}
