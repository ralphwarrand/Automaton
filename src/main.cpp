#include "DFA.h"
#include <iostream>

int main()
{
    ADA::DFA dfa;

    // Add states
    dfa.addState(0, false);  // Non-final state
    dfa.addState(1, true);   // Final state

    // Set start state
    dfa.setStartState(0);

    // Add transitions
    dfa.addTransition(0, 'a', 1);
    dfa.addTransition(1, 'b', 0);

    // Test DFA
    std::string input1 = "ab";
    std::string input2 = "aba";

    std::cout << "Input \"" << input1 << "\" is "
              << (dfa.isAccepted(input1) ? "accepted" : "rejected") << ".\n";

    std::cout << "Input \"" << input2 << "\" is "
              << (dfa.isAccepted(input2) ? "accepted" : "rejected") << ".\n";

    return 0;
}
