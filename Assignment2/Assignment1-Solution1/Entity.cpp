#include "Entity.hpp"

Entity::Entity(State* state) : SceneNode(state), mVelocity(0, 0, 0)
{
}

void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy, float vz)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
	mVelocity.z = vz;
}

XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(const GameTimer& gt) 
{
	XMFLOAT3 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	mV.z = mVelocity.z * gt.DeltaTime();

	move(mV.x, mV.y, mV.z);

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}

void Entity::accelerate(XMFLOAT3 accel)
{
	mVelocity.x += accel.x;
	mVelocity.y += accel.y;
	mVelocity.z += accel.z;
}

void Entity::accelerate(float x, float y, float z)
{
	mVelocity.x += x;
	mVelocity.y += y;
	mVelocity.z += z;
}
