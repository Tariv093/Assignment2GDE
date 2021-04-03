#include "GameState.hpp"


GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(&(context.game->mWorld))
	, mPlayer(*context.player)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(const GameTimer& dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(WPARAM btnState)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(commands);

	// Escape pressed, trigger the pause screen
#pragma region step 1
	if (btnState == VK_ESCAPE)
		requestStackPush(States::Pause);
#pragma endregion
	return true;
}