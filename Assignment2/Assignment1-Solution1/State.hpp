#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP

#include "StateIdentifiers.hpp"
#include "../../Common/d3dApp.h"
#include "SceneNode.hpp"
#include "FrameResource.h"


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
		Context(Player& player);

		Player* player;
	};


public:
	State(StateStack& stack, Context context, Game* game);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(const GameTimer& dt) = 0;
	virtual bool		handleEvent(WPARAM btnState) = 0;
	virtual void		BuildScene() = 0;
	Game*				mGame;

protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;

	StateStack*			mStack;

private:
	Context				mContext;
};

#endif // BOOK_STATE_HPP
