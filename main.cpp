#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int state[2][2]; //actualy state itself
    Node* parent;   
    string action; //backtrace to parent

    //copy over constructor
    Node(int initialState[2][2]) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                state[i][j] = initialState[i][j];
            }
        }
        parent = nullptr;
        action = "";
    }
};

//print node for debugging
void printNode(Node* n) {

    cout << "Board:" << endl;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            cout << n->state[i][j] << " ";
        cout << endl;
    }

    cout << "Action: " << n->action << endl;
    cout << "Parent: " << n->parent << endl;
}




void generalSearch(int initialState[2][2]) {
    // Implement general search algorithm here
    queue<Node*> stack;

    stack.push(new Node(initialState));

    printNode(stack.front());

    do {

        if(stack.empty()) {
            cout << "No more nodes to explore." << endl;
            break;
        }

        if (!stack.empty()) {
            Node* currentNode = stack.front();
            stack.pop();

            // Process currentNode here (e.g., check for goal state, generate successors, etc.)
            printNode(currentNode);

            for (int i = 0; i < 3; i++) {

            }
            // For demonstration, we will not generate successors in this example.
            // In a complete implementation, you would generate and push successor nodes onto the stack here.
        }

    } while (!stack.empty());


};

int main() {
   
//start as 2 x 2 array

    //goal state
   int goalState[2][2] = { {1, 2}, {3, 0}};

   // 1 2
   // 3 0

//input
   int initialState[2][2] = { {1, 0}, {3, 2}};
    // 1 0
    // 3 2

    //operators
    //up, down, left, right
    generalSearch(initialState);


    return 0;
}