#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 10

// A structure to represent the NFA
typedef struct NFA {
    int numStates;
    int epsilon[MAX_STATES][MAX_STATES]; // epsilon transitions
} NFA;

// Function to find epsilon closure of a state
void epsilonClosure(NFA *nfa, int state, int *closure) {
    int stack[MAX_STATES], top = -1;
    int visited[MAX_STATES] = {0};
    
    // Initialize closure with the state itself
    closure[state] = 1;
    stack[++top] = state;
    visited[state] = 1;

    while (top != -1) {
        int currentState = stack[top--];
        
        // For all epsilon transitions of the current state
        for (int nextState = 0; nextState < nfa->numStates; nextState++) {
            if (nfa->epsilon[currentState][nextState] && !visited[nextState]) {
                visited[nextState] = 1;
                closure[nextState] = 1;
                stack[++top] = nextState;
            }
        }
    }
}

// Function to compute epsilon closure for all states
void computeEpsilonClosures(NFA *nfa) {
    int closure[MAX_STATES];
    
    for (int i = 0; i < nfa->numStates; i++) {
        // Reset the closure for each state
        for (int j = 0; j < nfa->numStates; j++) {
            closure[j] = 0;
        }
        
        // Find epsilon closure for the state i
        epsilonClosure(nfa, i, closure);
        
        // Print the epsilon closure of the current state
        printf("Epsilon closure of q%d: { ", i);
        for (int j = 0; j < nfa->numStates; j++) {
            if (closure[j]) {
                printf("q%d ", j);
            }
        }
        printf("}\n");
    }
}

// Function to initialize the NFA with user input
void initializeNFA(NFA *nfa) {
    int numEpsilonTransitions, state1, state2;

    // Input number of states
    printf("Enter the number of states: ");
    scanf("%d", &(nfa->numStates));

    // Initialize epsilon transitions matrix
    for (int i = 0; i < nfa->numStates; i++) {
        for (int j = 0; j < nfa->numStates; j++) {
            nfa->epsilon[i][j] = 0;
        }
    }

    // Input epsilon transitions
    printf("Enter the number of epsilon transitions: ");
    scanf("%d", &numEpsilonTransitions);
    
    for (int i = 0; i < numEpsilonTransitions; i++) {
        printf("Enter epsilon transition (state1 state2): ");
        scanf("%d %d", &state1, &state2);
        if (state1 >= 0 && state1 < nfa->numStates && state2 >= 0 && state2 < nfa->numStates) {
            nfa->epsilon[state1][state2] = 1;
        } else {
            printf("Invalid state numbers. Try again.\n");
            i--;
        }
    }
}

// Main function
int main() {
    NFA nfa;

    // Initialize the NFA with user input
    initializeNFA(&nfa);

    // Compute and print epsilon closures for all states
    computeEpsilonClosures(&nfa);

    return 0;
}

