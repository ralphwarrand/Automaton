//
// Created by ralph on 20/01/2025.
//


#include "DFA.h"

namespace ADA
{
	void DFA::addState(const int state_id, const bool is_final)
	{
		if (states.contains(state_id))
        {
			throw std::invalid_argument("State already exists!");
        }

		states[state_id] = State(state_id);
		if (is_final)
        {
			final_states.insert(state_id);
        }
	}

	void DFA::setStartState(const int state_id)
	{
		if (!states.contains(state_id))
			throw std::invalid_argument("Start state must be a valid state!");
		initial_state = state_id;
	}

	void DFA::addTransition(int from_state, char input_symbol, const int to_state)
	{
		if (!states.contains(from_state) || !states.contains(to_state))
			throw std::invalid_argument("Both states must exist!");

		transitions[{from_state, input_symbol}] = to_state;
		alphabet.insert(input_symbol);
	}

	bool DFA::isAccepted(const std::string& input)
	{
		if (initial_state == -1)
			throw std::runtime_error("Start state is not set!");

		int currentState = initial_state;

		for (char symbol : input)
		{
			if (!alphabet.contains(symbol))
				throw std::invalid_argument("Input contains invalid symbols!");

			auto transitionKey = std::make_pair(currentState, symbol);
			if (!transitions.contains(transitionKey))
				return false; // No valid transition

			currentState = transitions[transitionKey];
		}

		return final_states.contains(currentState); // Check if the current state is a final state
	}
}