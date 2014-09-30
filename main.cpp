#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define TEXTURE_ARRAY_SIZE 150
#define OBJECT_ARRAY_SIZE 150
#define MESSAGE_QUEUE_SIZE 150

class GameObject;

class Component
{
private:
	std::string componentType;

public:

	void update(GameObject &parent, sf::RenderWindow& window){}

	void setType(std::string newType)
	{
		componentType = newType;
	}

	std::string getType()
	{
		return componentType;
	}
};


//Basic generic components, shoud be extended to create behavior
class InputComponent
{
public:
	void update(GameObject &parent){}
};


class LogicComponent
{
public:
	void update(GameObject &parent){}
};


class PhysicsComponent
{
private:
	GameObject *storedParent;

public:
	void update(GameObject &parent)
	{
		storedParent = &parent;
	}

	GameObject* getParent()
	{
		return storedParent;
	}
};

class GraphicsComponent
{
	void update(GameObject &parent, sf::RenderWindow &window){}
};

class GameObject
{
private:
	std::vector<InputComponent *> inputComponents;
	std::vector<LogicComponent *> logicComponents;
	std::vector<PhysicsComponent *> physicsComponents;
	std::vector<GraphicsComponent *> graphicsComponents;

public:
	int position[2];
	int velocity[2];
	int angvel[2];

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
		
	}

	void addLogicComponent(Component *newComponent)
	{
		components.insert(components.begin(), newComponent);
	}

	//Returns pointer to component if component is found, NULL if not found. Therefore, can and should be used to test if object contains component.
	Component* getComponent(std::string componentType)
	{
		for(std::vector<Component *>::iterator it = components.begin(); it != components.end(); ++it)
		{
			Component *currentComponent = *it;

			if(currentComponent->getType().compare(componentType))
			{
				return currentComponent;
			}
		}
		return NULL;
	}
};

class SpriteComponent: public GraphicsComponent
{
private:
	sf::Sprite componentSprite;

public:
	void update(GameObject &parent, sf::RenderWindow window)
	{
		componentSprite.setPosition(parent.position[0],parent.position[1]);
		window.draw(componentSprite);
	}
};

class PlayerInputComponent: public InputComponent
{
public:

	void update(GameObject &parent)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			parent.velocity[0] -= 2;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			parent.velocity[0] += 2;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			parent.velocity[1] -= 2;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			parent.velocity[1] += 2;
		}
	}
};

//Generic message class
class Message
{
private:
	
	std::string contents;

public:

	Message(){}

	Message(std::string message)
	{
		contents = message;
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
			return Message("NULL");
		}
	}

	int getCurrentQuantity()
	{
		return storedMessages;
	}
};

void loadTexture(sf::Texture array[])
{

}

int main()
{/*
	//Perform initialization
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::Texture textureArray[TEXTURE_ARRAY_SIZE];
	Component componentsArray[OBJECT_ARRAY_SIZE];


	window.setFramerateLimit(60);
*/

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