#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "CommandQueue.hpp"
class World
{
public:
	explicit							World(Game* game);
	void								update(const GameTimer& gt);
	void								draw();
	void								adjustPlayerVelo();
	void								adaptPlayerPosition();
	//void								loadTextures();
	void								buildScene();
	CommandQueue&						getCommandQueue();

private:
	enum class Layer
	{
		Background,
		Air
	};


private:
	Game* mGame;

	SceneNode* mSceneGraph;
	std::array<SceneNode*, 2>	mSceneLayers;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft* mPlayerAircraft;
	SpriteNode* mBackground;
	Aircraft* mEnemy;
	CommandQueue mCommandQueue;
};
