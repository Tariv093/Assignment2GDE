#pragma once
#include "Entity.hpp"
#include <string>

class Aircraft :
    public Entity
{
public:

	enum class Type
	{
		Eagle,
		Raptor,
	};


public:
	Aircraft(Type type, State* state);


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
	virtual unsigned int	getCategory() const;

private:
	Type				mType;
	std::string			mSprite;
	//RenderItem* mAircraftRitem;
};
