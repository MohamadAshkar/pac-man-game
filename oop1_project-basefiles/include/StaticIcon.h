#pragma once
#include "Icon.h"


class StaticIcon : public Icon
{
public:
	StaticIcon() {};
	
	//this class has virtual functions of draw
	//this class inherates from the icon class
	virtual void draw(sf::RenderWindow &window, sf::Vector2f pos) {}
	virtual bool getState()const { return m_state; };
	virtual void setState(bool s) {};
	~StaticIcon() {};
protected:
	bool m_state;

	
};


