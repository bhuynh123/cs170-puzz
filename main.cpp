#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//height, width
constexpr int w = 2;

struct Node {
    int state[w][w]; //actualy state itself
    Node* parent;   
    string action; //backtrace to parent

    //copy over constructor
    Node(int initialState[w][w]) {
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < w; j++) {
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
   
}

//branching funciton
//intution youtuve video solving 8 puzzle bfs python
//look for 0 which indicates empty space and swap with valid moves

void branchingFunction(Node* n, queue<Node*>& queue, vector<Node*> exploredAlready)  {
    //location (x,y) of zero
    int x;
    int y;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            if (n->state[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }
    //possible moves
    
    if(x > 0) { //up
        Node* upNode = new Node(n->state);
        swap(upNode->state[x][y], upNode->state[x-1][y]);
        upNode->parent = n;
        upNode->action = "up";
        queue.push(upNode);
    }
    if(x < w - 1) { //down
        Node* downNode = new Node(n->state);
        swap(downNode->state[x][y], downNode->state[x+1][y]);
        downNode->parent = n;
        downNode->action = "down";
        queue.push(downNode);
    }
    if(y > 0) { //left
        Node* leftNode = new Node(n->state);
        swap(leftNode->state[x][y], leftNode->state[x][y-1]);
        leftNode->parent = n;
        leftNode->action = "left";
        queue.push(leftNode);
    }
    if(y < w - 1) { //right
        Node* rightNode = new Node(n->state);
        swap(rightNode->state[x][y], rightNode->state[x][y+1]);
        rightNode->parent = n;
        rightNode->action = "right";
        queue.push(rightNode);
    }

}

bool goalTest(Node* n) {

    int goalState[w][w];

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < w; j++) {
            goalState[i][j] = i * w + j + 1;
        }
    }

    goalState[w-1][w-1] = 0; //set last element to 0

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < w; j++) {
            if(n->state[i][j] != goalState[i][j]) {
                return false;
            }
        }
    }

    return true;
}



void generalSearch(int initialState[2][2]) {
    // Implement general search algorithm here
    queue<Node*> explore;

    explore.push(new Node(initialState));

    printNode(explore.front());

    vector<Node*> visited;

    do {

        if(explore.empty()) {
            cout << "No more nodes to explore." << endl;
            break;
        }
 
        if (!explore.empty()) {
            Node* currentNode = explore.front();
            explore.pop();
            visited.push_back(currentNode);

            // Process currentNode here (e.g., check for goal state, generate successors, etc.)
            printNode(currentNode);

             if (goalTest(currentNode)) break;


            branchingFunction(currentNode, explore);
            
            // For demonstration, we will not generate successors in this example.
            // In a complete implementation, you would generate and push successor nodes onto the stack here.
        }

    } while (!explore.empty());


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