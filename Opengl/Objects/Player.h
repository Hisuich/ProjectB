#ifndef MAIN_PLAYER
#define MAIN_PLAYER

#include "DynamicObject.h"
#include "../Logic/TextCommand.h"
#include "../Logic/InteractCommand.h"
#include "../Logic/DialogCommand.h"
#include "Animation.h"
#include "Inventory.h"

class Player : public DynamicObject
{

public:
	static bool* key;

public:
	bool isStay = true;
	bool showInventory = false;

	Inventory* inventory = nullptr;

	Animation* left = nullptr;
	Animation* right = nullptr;
	Animation* up = nullptr;
	Animation* down = nullptr;
	Animation* currentAnimation = nullptr;

public:
	Player(PointXYZ position);
	Player();

	void playerMovementControl(unsigned char key, int x, int y);
	void playerMovementControlRelease(unsigned char key, int x, int y);

	void playerMovement(float dt);

	void setAnimation();
	void runAnimation(float dt);

	void update(float dt) override;
	void render() override;

	bool hasItem(Item* item);
	bool hasItem(long long itemId);

	void onStaticColision(GameObject* object) override;
	void onStaticInteraction(GameObject* object) override;

	void takeItem(Item* item);
};



#endif
