#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int state[2][2]; //actualy state itself
    Node* parent;   
    string action; //backtrace to parent
    Node* child[4]; //up, down, left, right

    //copy over constructor
    Node(int initialState[2][2]) {

        for (int i = 0; i < 2; i++) {

            for (int j = 0; j < 2; j++) {

                state[i][j] = initialState[i][j];

            }

        }

        parent = nullptr;
        action = "";
        //started hard coding all child to null but loop to better scale
        for (int i = 0; i < 4; i++) {
            child[i] = nullptr;
        }
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

    Node* startNode = new Node(initialState);

    stack.push(startNode);

    printNode(stack.front());


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