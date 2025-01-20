#ifndef DFA_H
#define DFA_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>

namespace ADA
{
    // Struct to represent a state in the DFA
    struct State
    {
        int id;       // Unique identifier for the state

        // Default constructor
        State() : id(-1) {}

        // Constructor with parameters
        explicit State(const int& state_id) : id(state_id) {}
    };

    // Custom hash function for std::pair<int, char>
    struct pair_hash
    {
        template <class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2>& pair) const
        {
            // Combine the hashes of the two elements in the pair
            return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
        }
    };

    class DFA
    {
    public:
        DFA() : initial_state(-1) {}

        // Add a state to the DFA
        void addState(int state_id, bool is_final = false);

        // Set the start state
        void setStartState(int state_id);

        // Add a transition between states
        void addTransition(int from_state, char input_symbol, int to_state);

        // Check if an input string is accepted by the DFA
        bool isAccepted(const std::string& input);

        // Get all final states
        std::vector<int> getFinalStates() const
        {
            return std::vector<int>(final_states.begin(), final_states.end());
        }

    private:
        std::unordered_map<int, State> states;                              // Map of state ID to State
        std::unordered_map<std::pair<int, char>, int, pair_hash> transitions; // Transition map
        std::unordered_set<char> alphabet;                                 // DFA input alphabet
        std::unordered_set<int> final_states;                               // Set of final states
        int initial_state;                                                    // The start state of the DFA
    };

}

#endif // DFA_H