#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "mathvector.h"

#define TEXTURE_ARRAY_SIZE 150
#define OBJECT_ARRAY_SIZE 150
#define MESSAGE_QUEUE_SIZE 150

enum message_type_t {NONE,INPUT, LOGIC, PHYSICS, GRAPHICS};

class GameObject;

// Basic component definitions, should be extended with functionality.
class InputComponent
{
public:

	virtual ~InputComponent(){};

	InputComponent(){};

	virtual void update(GameObject &parent) =0;
};


class LogicComponent
{
public:

	virtual ~LogicComponent();

	virtual void update(GameObject &parent){}
};


class PhysicsComponent
{
protected:

	double position[2];
	double velocity[2];
	double angvel;

public:
	GameObject *storedParent;

	virtual ~PhysicsComponent(){};

	PhysicsComponent()
	{
		angvel = 0;
		for(int i = 0; i < 2; i++)
		{
			position[i] = 0;
			velocity[i] = 0;
		}
	}

	virtual void update(GameObject &parent)
	{
		storedParent = &parent;
	}

	GameObject* getParent()
	{
		return storedParent;
	}

	double getX()
	{
		return position[0];
	}

	double getY()
	{
		return position[1];
	}

	void setX(double newPosition)
	{
		position[0] = newPosition;
	}

	void setY(double newPosition)
	{
		position[1] = newPosition;
	}

	double getAngVel()
	{
		return angvel;
	}

	double getXVel()
	{
		return velocity[0];
	}

	double getYVel()
	{
		return velocity[1];
	}

	void setXVel(double newVel)
	{
		velocity[0] = newVel;
	}

	void setYVel(double newVel)
	{
		velocity[1] = newVel;
	}

};


class GraphicsComponent
{
public:
	GraphicsComponent(){};

	virtual ~GraphicsComponent(){};

	virtual void update(GameObject &parent, sf::RenderWindow &window) =0;
};








//Basic game object.
class GameObject
{
private:
	std::vector<InputComponent *> inputComponents;
	std::vector<LogicComponent *> logicComponents;
	std::vector<PhysicsComponent *> physicsComponents;
	std::vector<GraphicsComponent *> graphicsComponents;

public:
	/*int position[2];
	int velocity[2];
	int angvel[2];
*/
	GameObject()
	{/*
		for(int i = 0; i < 2; i++)
		{
			position[i] = 0;
			velocity[i] = 0;
			angvel[i] = 0;
		}
	*/
	}

	~GameObject()
	{
		for(std::vector<InputComponent *>::iterator it = inputComponents.begin(); it != inputComponents.end(); it++)
		{
			delete (*it);
		}
		for(std::vector<LogicComponent *>::iterator it = logicComponents.begin(); it != logicComponents.end(); it++)
		{
			delete(*it);
		}
		for(std::vector<PhysicsComponent *>::iterator it = physicsComponents.begin(); it != physicsComponents.end(); it++)
		{
			delete(*it);
		}
		for(std::vector<GraphicsComponent *>::iterator it = graphicsComponents.begin(); it != graphicsComponents.end(); it++)
		{
			delete(*it);
		}
	}

	void update(sf::RenderWindow& window)
	{
		for(std::vector<InputComponent *>::iterator it = inputComponents.begin(); it != inputComponents.end(); it++)
		{
			(*it)->update(*this);
		}
		for(std::vector<LogicComponent *>::iterator it = logicComponents.begin(); it != logicComponents.end(); it++)
		{
			(*it)->update(*this);
		}
		for(std::vector<PhysicsComponent *>::iterator it = physicsComponents.begin(); it != physicsComponents.end(); it++)
		{
			(*it)->update(*this);
		}
		for(std::vector<GraphicsComponent *>::iterator it = graphicsComponents.begin(); it != graphicsComponents.end(); it++)
		{
			(*it)->update(*this, window);
		}

	}

	void addInputComponent(InputComponent *newComponent)
	{
		inputComponents.insert(inputComponents.end(), newComponent);
	}

	void addLogicComponent(LogicComponent *newComponent)
	{
		logicComponents.insert(logicComponents.end(), newComponent);
	}

	void addPhysicsComponent(PhysicsComponent *newComponent)
	{
		physicsComponents.insert(physicsComponents.end(), newComponent);
	}

	void addGraphicsComponent(GraphicsComponent *newComponent)
	{
		graphicsComponents.insert(graphicsComponents.end(), newComponent);
	}

	InputComponent* getInputComponento(int index)
	{
		return inputComponents.at(index);
	}

	LogicComponent* getLogicComponent(int index)
	{
		return logicComponents.at(index);
	}

	PhysicsComponent* getPhysicsComponent(int index)
	{
		return physicsComponents.at(index);
	}

	GraphicsComponent* getGraphicsComponent(int index)
	{
		return graphicsComponents.at(index);
	}

};


//Declarations of derived component classes
class BasicSpriteComponent: public GraphicsComponent
{
private:
	sf::Sprite componentSprite;

public:

	~BasicSpriteComponent(){};

	BasicSpriteComponent(sf::Texture *texture)
	{
		componentSprite.setTexture(*texture);
	}

	void update(GameObject &parent, sf::RenderWindow &window)
	{
		//std::cout << "Sprite update called!" << std::endl;
		componentSprite.setPosition(parent.getPhysicsComponent(0)->getX(),parent.getPhysicsComponent(0)->getY());
		window.draw(componentSprite);
	}
};

class PlayerInputComponent: public InputComponent
{
public:

	~PlayerInputComponent(){};

	void update(GameObject &parent)
	{
		//std::cout << "Updating player input!" << std::endl;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			parent.getPhysicsComponent(0)->setXVel(parent.getPhysicsComponent(0)->getXVel() - 2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			parent.getPhysicsComponent(0)->setXVel(parent.getPhysicsComponent(0)->getXVel() + 2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			parent.getPhysicsComponent(0)->setYVel(parent.getPhysicsComponent(0)->getYVel() -2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			parent.getPhysicsComponent(0)->setYVel(parent.getPhysicsComponent(0)->getYVel() + 2);
		}
	}
};

class PlayerPhysicsComponent: public PhysicsComponent
{
private:
	bool hasStoredParent;
	int maxVelocity;
	int parentOffset;

public:

	~PlayerPhysicsComponent(){};

	PlayerPhysicsComponent()
	{
		hasStoredParent = false;
		maxVelocity = 50;
		parentOffset = 50;
	}

	void update(GameObject &parent)
	{
		if(hasStoredParent == false)
		{
			storedParent = &parent;
		}

		if(velocity[0] > maxVelocity)
		{
			velocity[0] = maxVelocity;
		}
		if(velocity[0] < -maxVelocity)
		{
			velocity[0] = -maxVelocity;
		}

		if(velocity[1] > maxVelocity)
		{
			velocity[1] = maxVelocity;
		}
		if(velocity[1] < -maxVelocity)
		{
			velocity[1] = -maxVelocity;
		}

		if(position[0] <= 0 || position[0] >= 600 - parentOffset)
		{
			position[0] -= velocity[0];
			velocity[0] *= -1;
		}
		if(position[1] < 0 || position[1] >= 600 - parentOffset)
		{
			position[1] -= velocity[1];
			velocity[1] *= -1;
		}

		position[0] += velocity[0];
		position[1] += velocity[1];

		if(velocity[0] > 0)
		{
			velocity[0] -= 1;
		}
		if(velocity[1] > 0)
		{
			velocity[1] -= 1;
		}

		if(velocity[0] < 0)
		{
			velocity[0] += 1;
		}
		if(velocity[1] < 0)
		{
			velocity[1] += 1;
		}
	}
};

class RigidBodyPhysicsComponent: public PhysicsComponent
{
private:
	MathVector position;
	MathVector velocity;
	double acceleration;

public:

	~RigidBodyPhysicsComponent(){};

	RigidBodyPhysicsComponent()
	{
		position = MathVector(50,50);
		velocity = MathVector(0,0);
		acceleration = 0;
	}

};

//Generic message class
class Message
{
private:

	std::string contents;
	message_type_t type;

public:

	Message(){}

	Message(message_type_t type, std::string message)
	{
		contents = message;
	}

	message_type_t getType()
	{
		return type;
	}

	std::string getContents()
	{
		return contents;
	}

	void setContents(std::string message)
	{
		contents = message;
	}
};

class RingBuffer
{
private:

	int head, tail, storedMessages;
	Message buffer[MESSAGE_QUEUE_SIZE];

public:

	RingBuffer()
	{
		head = tail = storedMessages = 0;
	}

	int addMessage(Message newMessage)
	{

		if(storedMessages < MESSAGE_QUEUE_SIZE)
		{
			buffer[tail] = newMessage;
			storedMessages += 1;

			if(tail < MESSAGE_QUEUE_SIZE)
			{
				tail += 1;
			} else
			{
				tail = 0;
			}

			return 0;

		} else
		{
			std::cout << "Unable to add message to queue: No remaining space." << std::endl;
			return 1;
		}
	}

	Message getMessage()
	{
		if(head != tail)
		{
			if(head < MESSAGE_QUEUE_SIZE)
			{
				head += 1;
			} else
			{
				head = 0;
			}

			if(storedMessages != 0)
			{
				storedMessages -= 1;
			}
			return buffer[head-1];


		} else
		{
			return Message(NONE,"NULL");
		}
	}

	int getCurrentQuantity()
	{
		return storedMessages;
	}
};

void loadTexture(sf::Texture textures[], int index, std::string name)
{
	sf::Texture tempTexture;
	if(!tempTexture.loadFromFile(name))
	{
		std::cout << "unable to load texture" << name << std::endl;
	} else
	{
	textures[index] = tempTexture;
	}
}

int main()
{
	//Perform initialization
	sf::RenderWindow window(sf::VideoMode(600, 600), "WIP SFML Game Engine");
	sf::Texture textures[TEXTURE_ARRAY_SIZE];
	std::vector<GameObject*> gameObjectsArray;
	GameObject *tempObject;
	sf::Sprite backgroundSprite;
	MathVector testVector = MathVector(5,5);
	MathVector secondVector = MathVector(2,5);
	double outputNumber;

	outputNumber = testVector.crossProduct(secondVector);

	std::cout << outputNumber << std::endl;

	window.setFramerateLimit(60);

	tempObject = new GameObject();
	gameObjectsArray.push_back(tempObject);
	loadTexture(textures, 0,"textures/square.png");
	tempObject->addGraphicsComponent(new BasicSpriteComponent(&textures[0]));
	tempObject->addInputComponent(new PlayerInputComponent());
	tempObject->addPhysicsComponent(new PlayerPhysicsComponent());
	loadTexture(textures, 1, "textures/background.png");
	backgroundSprite.setTexture(textures[1]);

	tempObject->getPhysicsComponent(0)->setX(10);
	tempObject->getPhysicsComponent(0)->setY(50);

	std::cout << "Reached main loop" << std::endl;
	while(window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
            	window.close();
            }
        }
		window.clear();
		window.draw(backgroundSprite);
		for(std::vector<GameObject*>::iterator it = gameObjectsArray.begin(); it != gameObjectsArray.end(); it++)
		{
			(*it)->update(window);
		}
		window.display();
	}

//	Dummied out code for testing the ring buffer
/*
	RingBuffer testBuffer;
	std::string testString, firstWord, messageSubstring;
	std::size_t foundLocation;
	Message testMessage;

	std::cout << "Type add and then a message to add something to the buffer, type get to get the buffer head." << std::endl;


	while(1)
	{
		std::getline(std::cin, testString);
		foundLocation = testString.find(" ");

		firstWord = testString.substr(0,foundLocation);
	//	std::cout << firstWord << std::endl;

		if(!firstWord.compare("add"))
		{
			messageSubstring = testString.substr(foundLocation + 1);
			std::cout << "testMessage containing " << messageSubstring << " created, sending to buffer." << std::endl;
			testMessage = Message(messageSubstring);
			testBuffer.addMessage(testMessage);
			std::cout << "new buffer capacity is " << testBuffer.getCurrentQuantity() << std::endl;
		}

		if(!firstWord.compare("get") && foundLocation == std::string::npos)
		{
			std::cout << testBuffer.getMessage().getContents() << std::endl;
		}

	}
*/
    return 0;
}
