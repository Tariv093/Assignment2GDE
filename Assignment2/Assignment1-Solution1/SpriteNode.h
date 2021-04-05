#pragma once
#include "Entity.hpp"

class SpriteNode :
    public Entity
{
public:
	SpriteNode(State* state, std::string spriteIMG = "Desert");
	//RenderItem* mSpriteNodeRitem;

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();

	std::string			mSprite;
};
