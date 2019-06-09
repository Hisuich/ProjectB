#ifndef INVENTORY
#define INVENTORY

#include "Item.h"
#include <vector>
class Inventory
{
public:
	vector<Item*> items;

public:
	Inventory();

	void addItem(Item* item);
	void getItems();

	void display();
};

#endif