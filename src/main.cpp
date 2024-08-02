#include "Engine.h"

#include "Renderer/Renderer.h"
#include "Renderer/OpenGL/Shader.h"
#include "Renderer/OpenGL/Model.h"
#include "Renderer/OpenGL/Light.h"
#include "Renderer/UI/UIElement.h";
#include "Renderer/UI/UIElement.h"
#include "Renderer/UI/UICounter.h"

#include "Game/MyCamera.h"
#include "Game/UICamera.h"
#include "Game/Gun.h"
#include "Game/Ammo.h"
#include "Game/Medpack.h"
#include "Game/Bullet.h"
#include "Game/Enemy.h"
#include "Game/Map.h"

#include <stdlib.h>
#include <time.h>
/**
* @brief checks whether given pointer is a instance of class given in template
*
* @tparam Base Type of class we want to check against
* @tparam T Type of pointer we ant to check
* @param ptr pointer we want to check
* @return True if the pointer is instance of Base class, false otherwise.
*/
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

/**
 * @class RenderLayer
 *
 * @brief Class representing a layer implementation used to run a game. It contains base game logic
 */
class RenderLayer : public Layer
{
public:
	/**
	* @brief Constructs a RenderLayer object.
	*/
	RenderLayer() : Layer("Renderlayer") {}

	/**
	* @brief method called when creating a layer. This implementation contains loading all object that are required to play the game
	*/
	void onAttach() override
	{
		const unsigned int height = Engine::get().getWindow().getHeight();
		const unsigned int width = Engine::get().getWindow().getWidth();
		glViewport(0, 0, width, height );
		camera = new MyCamera(width, height, 0.1f, 100.0f, 95.0, glm::vec3(0.0, 3, 0.0));
		uiCamera = new UICamera(width, height, 0.1f, 100.0f, 100.0, glm::vec3(0.0, 1, 0.0));
		mainShader = new Shader("res/shader/def.vert", "res/shader/def.frag");
		uiShader = new Shader("res/shader/ui.vert", "res/shader/ui.frag");
	
		objects.push_back(new Skybox("res/Test/space"));
		objects.push_back(new Gun());		
		objects.push_back(new Map("res/Test/Map/Arena.gltf"));
		objects.push_back(healthGiver = new Medpack());
		objects.push_back(ammoGiver = new Ammo());
		
		addLights();	

		objects[1]->setPosition(0.0, -0.5, 0.0);
		objects[1]->rotate(0.0, 90.0, 0.0);
		objects[1]->linkCamera(*camera);

		elements.push_back(new UIElement(0.0, 0.0));

		healthCounter = new UICounter(0.3, 0.1, 3);
		healthCounter->setValue(Health);
		healthCounter->setPosition(-0.6, -0.7);
		elements.push_back(healthCounter);	

		scoreCounter = new UICounter(0.6, 0.1, 6);
		scoreCounter->setValue(Score);
		scoreCounter->setPosition(1.25, 0.65);
		elements.push_back(scoreCounter);

		fpsCounter = new UICounter(0.1, 0.03, 4);
		fpsCounter->setValue(0);
		fpsCounter->setPosition(-0.83, 0.95);
		elements.push_back(fpsCounter);

		ammo = new UICounter(0.2, 0.1, 2);
		ammo->setValue(AmmoCount);
		ammo->setPosition(0.75, -0.7);
		elements.push_back(ammo);		

		UIElement* icon = new UIElement(.05, .1);
		icon->setPosition(-0.9, -0.7);
		icon->setTexture("res/Test/helthIco.png");
		elements.push_back(icon);

		icon = new UIElement(.05, .1);
		icon->setPosition(0.9, -0.7);
		icon->setTexture("res/Test/AmmoIco.png");
		elements.push_back(icon);

		icon = new UIElement(0.05, 0.07);
		icon->setTexture("res/Test/crosshair.png");
		elements.push_back(icon);

		damageUI = new UIElement(1, 1);
		damageUI->setTexture("res/Test/damage.png");
		damageUI->setVisible(false);
		elements.push_back(damageUI);

		pauseText = new UIElement(0.5, 0.5);
		pauseText->setTexture("res/Test/pause.png");
		pauseText->setVisible(false);
		elements.push_back(pauseText);
	}

	/**
	* @brief method called when detaching a layer. This implementation releases all used pointers
	*/
	void onDetach() override
	{
		for (Object* obj : objects)
		{
			delete obj;
		}
		objects.clear();

		for (UIElement* el : elements)
		{
			delete el;
		}
		elements.clear();

		delete camera;
		delete uiCamera;

		delete mainShader;
		delete uiShader;
	}

	/**
	* @brief method called when layer receives event
	*/
	void onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&RenderLayer::shoot, this, std::placeholders::_1));
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&RenderLayer::pause, this, std::placeholders::_1));

		camera->onEvent(event);
		
		for (Object* obj : objects)
		{
			obj->onEvent(event);
		}
	}
	/**
	* @brief method called when updating a layer. This implementation contains all game logic
	*/
	void onUpdate(Timestep ts) override
	{	 	
		if (isTimeStoped) ts = 0;

		glEnable(GL_DEPTH_TEST);
		camera->onUpdate(ts);

		Renderer::clearColor({ 0.1f, 0.1f, 0.10f, 1.0f });
		Renderer::clearBuffers();

		camera->Matrix(*mainShader, "camMatrix");

		giveAmmo(ts);
		giveHealth(ts);

		ammo->setValue(AmmoCount);
		healthCounter->setValue(Health);
		scoreCounter->setValue(Score);
		fpsCounter->setValue(1 / ts);

		shootTimer += ts;

		spawnEnemy(ts);

		glUniform1f(glGetUniformLocation(mainShader->ID, "brightness"), (isTimeStoped)? 0.5: 1.0);

		std::vector<glm::vec3> bulletpositions;

		for (std::vector<Object*>::iterator b = objects.begin(); b != objects.end(); ++b)
		{
			(*b)->onUpdate(ts);
			Renderer::submit(*(*b), *mainShader, *camera);

			if (instanceof<Bullet>(*b))
			{
				bulletpositions.push_back((*b)->position);
				if ((*b)->position.x > 55.0f || (*b)->position.x < -55.0f || (*b)->position.z > 55.0f || (*b)->position.z < -55.0f)
				{

					((Bullet*)(*b))->disable();
					delete (*b);
					(*b) = nullptr;
				}

			}
			else if (instanceof<Enemy>(*b))
			{
				if (((Enemy*)(*b))->isKilled())
				{
					delete (*b);
					(*b) = nullptr;
				}
			}

			// Delete unused objects
			if ((*b) == nullptr)
			{
				b = objects.erase(b);
				b--;
			}
		}

		// Check for hits
		for (std::vector<Object*>::iterator b = objects.begin(); b != objects.end(); b++)
		{
			if (instanceof<Enemy>(*b))
			{
				for (glm::vec3 bullpos : bulletpositions)
				{ 
					if (((Enemy*)(*b))->distanceTo(bullpos) < 4)
					{
						((Enemy*)(*b))->damage(5);
					}
				}

				
				if (damageTimer > 0.5 && ((Enemy*)(*b))->distanceTo(getCameraLocation()) < 3 )
				{
					damageUI->setVisible(true);
					Health -= 10;
					damageTimer = 0;
					if (Health <= 0)
					{
						Health = 0;
						endGame();
					}
				}
					
				if (((Enemy*)(*b))->isKilled())
				{
					Score += 10 * (waveCounter + 1);
					enemyCounter--;
					killsInWave++;

					if (killsInWave >= 10)
					{
						waveCounter++;
						killsInWave = 0;
					}
				}
			}
		}
		damageTimer += ts;
		if (damageTimer > 0.8) damageUI->setVisible(false);

		// Handle Lighting
		int i = 0;
		for (std::vector<Light*>::iterator b = lights.begin(); b != lights.end(); ++b)
		{
			if ((*b)->isDiscarded())
			{
				delete (*b);
				b = lights.erase(b);
				b--;
			}
			(*b)->passToShader(*mainShader, *camera, i);
			i++;
		}

		// Draw UI
		for (UIElement* element : elements)
		{
			if (instanceof<UIElement>(element))
			{
				glUniform2f(glGetUniformLocation(uiShader->ID, "TextureOffset"),0, 0);
			}
			element->draw(*uiShader, *uiCamera);
		}
	}

	/**
	* @brief gets current location of main camera
	* 
	* @return location op main camera
	*/
	glm::vec3 getCameraLocation() 
	{
		return camera->position;
	}

private:
	std::vector<Object*> objects; ///< vector containing rendered objects
	std::vector<Light*> lights; ///< vector containing scene lights
	std::vector<UIElement*> elements; ///< vector containing UI

	Camera* camera = nullptr; ///< pointer to main camera
	Camera* uiCamera = nullptr; ///< pointer to camera responsible for rendering UI
	Shader* mainShader = nullptr; ///< pointer to main shader
	Shader* uiShader = nullptr; ///< pointer to shader responsible for rendering UI

	UICounter* ammo = nullptr;  ///< pointer to counter responsible for displaing ammuintion amount
	UICounter* healthCounter = nullptr; ///< pointer to counter responsible for displaing health amount
	UICounter* scoreCounter = nullptr; ///< pointer to counter responsible for displaing current score
	UICounter* fpsCounter = nullptr; ///< pointer to counter responsible for displaing frames per second
	UIElement* damageUI = nullptr; ///< pointer to UI element responsible for displaing damage effect
	UIElement* pauseText = nullptr; ///< pointer to UI element responsible for displaing text when game stoped;
	

	Ammo* ammoGiver = nullptr; ///< pointer to object responsible for giving ammunition
	Medpack* healthGiver = nullptr; ///< pointer to object responsible for giving health
	
	Light* ammoLight = nullptr; ///< Pointer to light of ammunition box
	Light* healthLight = nullptr; ///< Pointer to light of health pack
	
	bool isAmmoAvaliable = true; ///< Flag informing if ammunition is avaliable to collect
	bool isHealthAvaliable = true; ///< Flag informing if health is avaliable to collect
	bool isTimeStoped = false; ///< Flag informing if time is stopped
	
	//Timers
	float ammoTimer = 0; ///< timer for Ammo spawning
	float shootTimer = 0; ///< timer for shooting
	float healthTimer = 0; ///< timer for health spawning
	float enemyTimer = 0; ///< timer for enemy spawning
	float damageTimer = 0; ///< timer for taking damage

	unsigned int enemyCounter = 0; ///< Counts number of active enemies
	unsigned int waveCounter = 0; ///< Counts number of wave of enemies for difficulty progression
	unsigned int killsInWave = 0; ///< Counts number of kills in wave for difficulty progression
	int AmmoCount = 30; ///< counts amount of ammunition
	int Health = 70; ///< counts amount of health
	int Score = 0; ///< counts amount of score

	/**
	* @brief adds lights to scene
	*/
	void addLights()
	{
		//SUN
		lights.push_back(new Light(DIRECT, {-10.0, 100.0, 10}, { 1.0, 1.0, 0.9 }, 0.7));

		// lights on walls
		for (float h = 10.0; h <= 50; h += 40.0)
		{
			for (int i = 0; i < 3; i++)
			{
				Light* crrntLight = new Light(POINT);
				crrntLight->setColor({ 0.8, 0.7, 0.4 });
				crrntLight->setPosition({ -27 + (i * 27), h, -50.0 });
				crrntLight->setIntensity(15);
				lights.push_back(crrntLight);

			}
			for (int i = 0; i < 3; i++)
			{
				Light* crrntLight = new Light(POINT);
				crrntLight->setColor({ 0.8, 0.7, 0.4 });
				crrntLight->setPosition({ -27 + (i * 27), h, 55.0 });
				crrntLight->setIntensity(15);
				lights.push_back(crrntLight);
			}
		}

		lights.push_back(ammoLight = new Light(POINT, { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }));
		lights.push_back(healthLight = new Light(POINT, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }));
	}

	/**
	* @brief method for handling shooting
	* 
	* @param event key pressed event
	* @return true if event has been handled otherwise false
	*/
	bool shoot(KeyPressedEvent event)
	{
		if (event.getKeyCode() != GLFW_KEY_SPACE) return false;
		
		if (shootTimer < 0.25)
		{
			return true;
		}
		shootTimer = 0.0;

		AmmoCount--;
		if (AmmoCount < 0)
		{
			AmmoCount = 0;
		}
		else
		{
			glm::vec3 newPosition = camera->position;
			newPosition.y -= 0.5;
			newPosition += glm::normalize(camera->orientation);
			Light* bulletLight = new Light(POINT, newPosition, { 0.0, 0.0, 1.0 });
			lights.push_back(bulletLight);
			bulletLight->setIntensity(10);
			Bullet* bullet = new Bullet(bulletLight, camera->orientation);
			bullet->position = newPosition;
			objects.push_back(bullet);
		}
		return true;		
	}

	/**
	* @brief method responsible for spawning and giving ammunition
	*
	* @param is amount of time from last update
	*/
	void giveAmmo(Timestep ts) {
		if (!isAmmoAvaliable)
		{
			ammoGiver->setVisible(false);
			ammoLight->setIntensity(0.0);
			if (ammoTimer < 3) ammoTimer += ts;
			else
			{
				ammoTimer = 0;
				isAmmoAvaliable = true;
				
			}
			return;
		}

		ammoGiver->setPosition(ammoGiver->position.x, -2, ammoGiver->position.z);
		ammoLight->setPosition(glm::vec3(ammoGiver->position.x, -2.5, ammoGiver->position.z) * ammoGiver->scale);
		ammoGiver->setVisible(true);
		ammoLight->setIntensity(5.0);
		srand(AmmoCount * time(NULL));
		if (ammoGiver->getDistanceFromCamera() < 4 )
		{			
			if (AmmoCount < 99) AmmoCount += 15 ;
			if (AmmoCount >= 99) AmmoCount = 99;
			
			float randX = rand() % 60 - 31;
			float randY = rand() % 60 - 31;

			ammoGiver->setPosition({ randX, -2.0, randY });
			isAmmoAvaliable = false;
		}
	}

	/**
	* @brief method responsible for spawning and giving health
	*
	* @param is amount of time from last update
	*/
	void giveHealth(Timestep ts)
	{
		if (!isHealthAvaliable)
		{
			healthGiver->setPosition(healthGiver->position.x, -12, healthGiver->position.z);
			healthLight->setIntensity(0.0);
			if (healthTimer < 25 + (waveCounter * 1.3) + (killsInWave * 0.1)) healthTimer += ts;
			else
			{
				healthTimer = 0;
				isHealthAvaliable = true;

			}
			return;
		}
		srand(Health*time(NULL));
		healthGiver->setPosition(healthGiver->position.x, -2, healthGiver->position.z);
		healthLight->setPosition(glm::vec3(healthGiver->position.x, -2.5, healthGiver->position.z) * healthGiver->scale);
		healthLight->setIntensity(5.0);
		if (healthGiver->getDistanceFromCamera() < 5)
		{			
			if (Health < 100) Health += 10;
			if (Health >= 100) Health = 100;
			
			float randX = rand() % 60 - 31;
			float randY = rand() % 60 - 31;

			healthGiver->setPosition({ randX, -2.0, randY });
			isHealthAvaliable = false;
		}
	}

	/**
	* @brief method responsible for spawning Enemies
	*
	* @param is amount of time from last update
	*/
	void spawnEnemy(Timestep ts)
	{
		srand(Health * enemyTimer * time(NULL) + waveCounter + killsInWave);
		enemyTimer += ts.getSeconds();
		float timerTreshold;
		if (enemyCounter == (3 + waveCounter/2))
		{
			timerTreshold = 1 - (waveCounter * 0.7) - killsInWave * 0.2;
		}
		else
		{
			timerTreshold = 5 - (waveCounter * 0.55) - killsInWave * 0.15;
		}

		if (enemyCounter >= (3 + waveCounter / 2) || enemyTimer < timerTreshold) return;

		float randX = rand() % 50 - 26;
		float randY = rand() % 50 - 26;

		Enemy* enemy = new Enemy();
		enemy->setPosition({ randX, enemy->position.y, randY });

		Light* enemyLight = new Light(POINT, {0.0, 0.0, 0.0}, {0.9, 0.1, 0.0}, 3);
		enemy->addLight(enemyLight, 3);
		lights.push_back(enemyLight);

		objects.push_back(enemy);
		enemyCounter++;
		enemyTimer = 0;
	}

	/**
	* @brief method responsible for pausing the game
	*
	* @param event key pressed event
	* @return true if event has been handled otherwise false
	*/
	bool pause(KeyPressedEvent& e)
	{
		if (e.getKeyCode() != GLFW_KEY_ESCAPE) return false;
		
		if (isTimeStoped)
		{
			isTimeStoped = false;
			pauseText->setVisible(false);
		}
		else 
		{
			isTimeStoped = true;
			pauseText->setVisible(true);
		} 
	}

	/**
	* @brief method responsible for ending the game
	*/
	void endGame()
	{
		isTimeStoped = true;
		pauseText->setTexture("res/test/gameover.png");
		pauseText->setVisible(true);
	}
};

/**
 * @class Ceres
 *
 * @brief Class representing the game itself
 */
class Ceres : public Engine
{
public:
	/**
	* @brief Constructs a Ceres game.
	*/
	Ceres()
	{
		pushLayer(new RenderLayer());		
	}

	/**
	* @brief Destroys a Ceres game.
	*/
	~Ceres()
	{

	}
};

/**
* @brief main aplication function - creates and launches the game
*/
int main()
{
	// Main Engine Entry point
	Ceres* ceres = new Ceres();

	ceres->run();

	delete ceres;	

	return 0;
}

