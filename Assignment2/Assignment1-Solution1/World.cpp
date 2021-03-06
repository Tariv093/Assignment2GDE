#define NOMINMAX
#include "World.hpp"

World::World(State* state)
	: mSceneGraph(new SceneNode(state))
	, mState(state)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-5.f, 5.f, -2.f, 2.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.0f)	
	
{
}

void World::update(const GameTimer& gt)
{
	
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);
	}
	
	mSceneGraph->update(gt);

	adjustPlayerVelo();
	adaptPlayerPosition();
	//AirCraft Bouncing
	/*if (mPlayerAircraft->getWorldPosition().x < mWorldBounds.x
		|| mPlayerAircraft->getWorldPosition().x > mWorldBounds.y)
	{
		mPlayerAircraft->setVelocity(XMFLOAT3(mPlayerAircraft->getVelocity().x * -1.0f, 0, 0));
	}*/

	
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::adjustPlayerVelo()
{
	XMFLOAT3 velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.z != 0.f)
		mPlayerAircraft->setVelocity(velocity.x / std::sqrt(2.f), velocity.y / std::sqrt(2.f), velocity.z / std::sqrt(2.f));

	// Add scrolling velocity
	//mPlayerAircraft->accelerate(mScrollSpeed, 0, 0);
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	//sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 100.f;

	XMFLOAT3 position = mPlayerAircraft->getWorldPosition();
	position.x = std::max(position.x, mWorldBounds.x);
	position.x = std::min(position.x, mWorldBounds.y);
	position.z = std::max(position.z, mWorldBounds.z);
	position.z = std::min(position.z, mWorldBounds.w);
	mPlayerAircraft->setPosition(position.x, position.y, position.z);
}

void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Type::Eagle, mState));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0.0f, 0.1f, 0.0f);
	mPlayerAircraft->setScale(0.5f, 0.5f, 0.5f);
	mPlayerAircraft->setVelocity(mScrollSpeed, 0.0f, 0.0f);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Type::Raptor, mState));
	auto raptor = enemy1.get();
	raptor->setPosition(0.5f, 0.0f, 1.0f);
	raptor->setScale(1.0f, 1.0f, 1.0f);
	raptor->setWorldRotation(0.0f,  XM_PI, 0.0f);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Type::Raptor, mState));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-0.5, 0, 1);
	raptor2->setScale(1.0, 1.0, 1.0);
	raptor2->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mState));
	mBackground = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(200.0, 1.0, 200.0);
	mBackground->setVelocity(0,0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}
