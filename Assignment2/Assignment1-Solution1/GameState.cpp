#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack* stack, Context* context)
	: State(stack, context)
	, mWorld(this)
	, mPauseBackground(nullptr)
	, mPauseText(nullptr)
	, mPauseInstructionText(nullptr)
	, mPauseSceneGraph(new SceneNode(this))
{
	BuildScene();
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(const GameTimer& dt)
{
	ProcessInput();
	mWorld.update(dt);

	return true;
}

bool GameState::handleEvent(WPARAM btnState)
{
	// Game input handling

	// Escape pressed, trigger the pause screen
#pragma region step 1
	if (btnState == VK_ESCAPE)
		requestStackPush(States::Pause);
#pragma endregion
	return true;
}

void GameState::ProcessInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();
	getContext()->player->handleRealtimeInput(commands);
	getContext()->player->handleRealtimeInput(commands);
}
void GameState::BuildScene()
{
	//getContext()->game.BuildMaterials();
	mWorld.buildScene();

	getContext()->game.ClearFrameResources();
	getContext()->game.BuildFrameResources(mAllRitems.size());
	
}
