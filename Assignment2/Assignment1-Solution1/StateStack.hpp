#ifndef BOOK_STATESTACK_HPP
#define BOOK_STATESTACK_HPP

#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "../../Common/d3dApp.h"
//
#include <vector>
#include <utility>
#include <functional>
#include <map>

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

class Game;
class StateStack 
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};


public:
	explicit			StateStack(State::Context context);

	template <typename T>
	void				registerState(States::ID stateID);

	void				update(const GameTimer& dt);
	void				draw();
	void				handleEvent(WPARAM btnState);

	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();

	bool				isEmpty() const;
	
	std::vector<State::Ptr>* GetStateStack();

	int					GetStackSize() { return mStack.size(); }
	State* GetCurrentState() { return mStack.back().get(); }
	State* GetPreviousState();
private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();


private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, States::ID stateID = States::None);

		Action				action;
		States::ID			stateID;
	};


private:
	std::vector<State::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;

	State::Context										mContext;
	std::map<States::ID, std::function<State::Ptr()>>		mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(this, &mContext));
	};
}

#endif // BOOK_STATESTACK_HPP
