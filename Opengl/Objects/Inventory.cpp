#include "Inventory.h"

Inventory::Inventory()
{
}

void Inventory::addItem(Item * item)
{
	this->items.push_back(item);
}

void Inventory::getItems()
{
	for (auto it : items)
	{
		cout << it->name;
	}
}

void Inventory::display()
{
	glPushMatrix();
	glLoadIdentity();

	int winWidth = glutGet(GLUT_WINDOW_WIDTH);
	int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
	glTranslatef(0, 0, 0);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);

	cout << winWidth << " " << winHeight;
	glBegin(GL_POLYGON);
	glVertex2i(0, 0);
	glVertex2i(winWidth, 0);
	glVertex2i(winWidth, winHeight / 8);
	glVertex2i(0, winHeight / 8);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(winWidth, 0);
	glVertex2i(winWidth, winHeight / 8);
	glVertex2i(0, winHeight / 8);
	glEnd();

	for (int i = 0; i < items.size(); i++)
	{
		
		PointXYZ position(i * winWidth / 16, winHeight / 16, 0);
		items[i]->drawGameObject(position);
	}

	glPopMatrix();
}
