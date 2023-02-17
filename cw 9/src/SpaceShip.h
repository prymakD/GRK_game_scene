#pragma once
#include "glm.hpp"
#include "glew.h"
#include "objload.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>
#include "Laser.h"

class SpaceShip
{
private:
	bool attackDecision = false;
	glm::vec3 spaceShipDir;
	glm::vec3 spaceShipPos;

	std::vector<Laser> gun;
	int maxNumberOfLasers;
	int numberOfLeftLasers;


public:
	SpaceShip();
	SpaceShip(int numberOfLasers, glm::vec3 shipPos);


	//getters and setters
	void setAttackDecision(bool attackDec);
	bool getAttackDecision();

	void setSpaceShipDir(glm::vec3 spShipDir);
	glm::vec3 getSpaceShipDir();

	void setSpaceShipPos(glm::vec3 spShipPos);
	glm::vec3 getSpaceShipPos();

	void setGun(std::vector<Laser> g);
	std::vector<Laser> getGun();

	void setMaxNumberOfLasers(int numberOfLasers);
	int getMaxNumberOfLasers();

	void setNumberOfLeftLasers(int numberOfLasers);
	int getNumberOfLeftLasers();


	//methods
	void laserPreparationBeforeShoot(float time);
};

