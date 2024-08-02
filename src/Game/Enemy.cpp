#include "Enemy.h"

Enemy::Enemy()
{
	this->addModel("res/Test/Robot/Robot.gltf");
	this->setScale(2.1, 2.4, 2.1);
	this->setPosition(0.0, -3.5, 0.0);
	killed = false;
	hp = 20;
}

void Enemy::onUpdate(Timestep ts)
{
	moveEnemy(ts);
	updateLights();
	hitTimer += ts;
}

void Enemy::damage(float damagept)
{
	if (hitTimer < 0.5) return;
	this->hp -= damagept;
	if (hp <= 0)
	{
		killed = true;
		isVisible = false;
		for (Light* l : enemyLights)
		{
			l->discard();
		}

		enemyLights.clear();
	}
	hitTimer = 0.0;
}

void Enemy::draw(Shader& shader, Camera& camera)
{
	this->campos = glm::vec3(camera.position.x, this->position.y, camera.position.z) / this->scale;
	GameObject::draw(shader, camera);
}

float Enemy::distanceTo(glm::vec3 point)
{
	return glm::distance(this->position, glm::vec3(point.x, this->position.y, point.z) / this->scale);
}

void Enemy::moveEnemy(Timestep ts)
{
	glm::vec2 desiredDirection = glm::normalize(glm::vec2(campos.x - position.x, campos.z - position.z));
	glm::vec2 yourDirection(direction.x, direction.z);

	float currentAngle = glm::degrees(glm::angle(yourDirection, desiredDirection));
	if (currentAngle > 5.0)
	{
		speed = 2;
		float yAngle = 0.0;
		glm::vec3 testRotation = glm::normalize(glm::rotateY(direction, glm::radians((float)1.0)));

		if (glm::degrees(glm::angle(glm::vec2(testRotation.x, testRotation.z), desiredDirection)) < currentAngle)
		{
			yAngle = 1;
		}
		else
		{
			yAngle = -1;
		}
		rotateEnemy(yAngle);
	}
	else
	{
		speed = 5;
	}

	move(glm::normalize(direction) * (ts * speed));
}

void Enemy::addLight(Light* light, float yPos)
{
	glm::vec3 newLightPos = glm::vec3(this->position.x, yPos, this->position.x) / this->scale;
	enemyLights.push_back(light);
}

void Enemy::rotateEnemy(float yAngle)
{
	GameObject::rotate(0, yAngle, 0);
	direction = glm::normalize(glm::rotateY(direction, glm::radians(yAngle)));
}

void Enemy::updateLights()
{
	//std::cout << "UPDATE LIGHTS" << enemyLights.size() << std::endl;
	for (Light* l : enemyLights)
	{
		l->setPosition(glm::vec3(this->position.x, l->getPosition().y, this->position.z) * this->scale);
	}
}