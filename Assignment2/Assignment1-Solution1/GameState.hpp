#ifndef BOOK_GAMESTATE_HPP
#define BOOK_GAMESTATE_HPP

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp""

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(const GameTimer& dt);
	virtual bool		handleEvent(WPARAM btnState);


private:
	World				mWorld;
	Player& mPlayer;
};

#endif // BOOK_GAMESTATE_HPP