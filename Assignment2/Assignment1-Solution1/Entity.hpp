#pragma once
#include "SceneNode.hpp"

class Entity :
    public SceneNode
{
public:
	Entity(State* state);
	void				setVelocity(XMFLOAT3 velocity);
	void				setVelocity(float vx, float vy, float vz);
	XMFLOAT3			getVelocity() const;

	virtual	void		updateCurrent(const GameTimer& gt);
	void				accelerate(XMFLOAT3 accel);
	void				accelerate(float x, float y, float z);
public:
	XMFLOAT3		mVelocity;
};

