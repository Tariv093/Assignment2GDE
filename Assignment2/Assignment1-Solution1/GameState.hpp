#ifndef BOOK_GAMESTATE_HPP
#define BOOK_GAMESTATE_HPP

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "SpriteNode.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context, Game* game);

	virtual void		draw();
	virtual bool		update(const GameTimer& dt);
	virtual bool		handleEvent(WPARAM btnState);


private:
	World*				mWorld;
	Player&				mPlayer;

public:
	SceneNode* mPauseSceneGraph;
	SpriteNode* mPauseBackground;
	SpriteNode* mPauseText;
	SpriteNode* mPauseInstructionText;

private:
	virtual void BuildScene() override;
};

#endif // BOOK_GAMESTATE_HPP