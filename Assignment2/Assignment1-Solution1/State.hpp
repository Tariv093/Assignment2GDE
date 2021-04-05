#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP

#include "StateIdentifiers.hpp"
#include "../../Common/d3dApp.h" 


#include <memory>


class StateStack;
class Player;
class Game;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(Player* player, Game* game);

		Player* player;
		Game* game;

	};


public:
	State(StateStack* stack, Context* context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(const GameTimer& dt) = 0;
	virtual bool		handleEvent(WPARAM btnState) = 0;
	virtual void		BuildScene() = 0;
	Game*				mGame;
	Context*			getContext() const;
protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	

	StateStack*			mStack;

private:
	Context*			mContext;
};

#endif // BOOK_STATE_HPP
