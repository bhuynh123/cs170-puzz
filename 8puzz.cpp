#include <iostream>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;

//height, width
constexpr int w = 3;

struct Node {
    int state[w][w]; //actualy state itself
    Node* parent;   
    string action; //backtrace to parent
    int depth;

    //copy over constructor
    Node(int initialState[w][w]) {
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < w; j++) {
                state[i][j] = initialState[i][j];
            }
        }
        parent = nullptr;
        action = "";
        depth = 0; // initialize root depth
    }
};

//print node for debugging
void printNode(Node* n) {

    cout << "Board:" << endl;

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++)
            cout << n->state[i][j] << " ";
        cout << endl;
    }

    cout << "Action: " << n->action << endl;
   
}

//starts false and after comparing each STATE to explored states, returns true
bool redundantSearch(Node* n, const vector<Node*>& exploredAlready) {
    for (Node* exploredNode : exploredAlready) {
        //reset to true each node
        bool identical = true;
        for (int i = 0; i < w; i++) {

            for (int j = 0; j < w; j++) {
                //if at least one element is different, move on
                if (n->state[i][j] != exploredNode->state[i][j]) {
                    identical = false;
                    break;
                }
            }
            //if loop breaks, its bc they arent identical
            if (!identical){
                break;
            }
        }
        //if at least one node is identical, end loop and terminate search
        if (identical) {
            return true;
        }
    }
    //if loops complete, that means no identical nodes found
    return false;
}

//branching funciton
//intution youtuve video solving 8 puzzle bfs python
//look for 0 which indicates empty space and swap with valid moves
void branchingFunction(Node* n, queue<Node*>& queue, const vector<Node*>& exploredAlready)  {
    //location (x,y) of zero
    int row = -1;
    int column = -1;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            if (n->state[i][j] == 0) {
                row = i;
                column = j;
                //issues if 2 0s are found
                break;
            }
        }
        if (row != -1) {
            break;
        }
    }
    //possible moves
    
    //track the movement of 0 tile
    if (row > 0) { //up
        Node* upNode = new Node(n->state);
        swap(upNode->state[row][column], upNode->state[row-1][column]);
        if (!redundantSearch(upNode, exploredAlready)) {
            upNode->parent = n;
            upNode->action = "up";
            upNode->depth = n->depth + 1;
            queue.push(upNode);
        } else {
            delete upNode; //avoid memory leak
        }
    }
    if (row < w - 1) { //down
        Node* downNode = new Node(n->state);
        swap(downNode->state[row][column], downNode->state[row+1][column]);
        if (!redundantSearch(downNode, exploredAlready)) {
            downNode->parent = n;
            downNode->action = "down";
            downNode->depth = n->depth + 1;
            queue.push(downNode);
        } else {
            delete downNode;
        }
    }
    if (column > 0) { //left
        Node* leftNode = new Node(n->state);
        swap(leftNode->state[row][column], leftNode->state[row][column-1]);
        if (!redundantSearch(leftNode, exploredAlready)) {
            leftNode->parent = n;
            leftNode->action = "left";
            leftNode->depth = n->depth + 1;
            queue.push(leftNode);
        } else {
            delete leftNode;
        }
    }
    if (column < w - 1) { //right
        Node* rightNode = new Node(n->state);
        swap(rightNode->state[row][column], rightNode->state[row][column+1]);
        if (!redundantSearch(rightNode, exploredAlready)) {
            rightNode->parent = n;
            rightNode->action = "right";
            rightNode->depth = n->depth + 1;
            queue.push(rightNode);
        } else {
            delete rightNode;
        }
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

void backtrace(Node* n) {
    // collect path from goal back to initial
    vector<Node*> path;
    Node* current = n;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }

    cout << "Solution path (from initial to goal):" << endl;

    // print boards from initial to goal
    for (int i = path.size() - 1; i >= 0; i--) {
        printNode(path[i]);
    }

    // print depth (number of moves from initial to goal)
    cout << "Solution depth (moves): " << n->depth << endl;

    cout << endl;
}

void generalSearch(int initialState[w][w]) {
    
    //nodes = Make-Queue(MAKE-NODE(initialState))
    queue<Node*> explore;
    explore.push(new Node(initialState));

    vector<Node*> visited;
    bool found = false;

    //loop do
    while (!explore.empty()) {

        //node = REMOVE-FRONT(nodes)
        Node* currentNode = explore.front();
        explore.pop();
        visited.push_back(currentNode);


        //if problem.GOAL-TEST(node.STATE) succeeds, return solution
        if (goalTest(currentNode)) {
            cout << "Goal found" << endl;
            found = true;
            backtrace(currentNode);
            break;
        }
        //nodes = queueiong function(nodes, expand(nodes, problem.operators))
        branchingFunction(currentNode, explore, visited);
    }

    if (!found && explore.empty()) {
        cout << "No Solution found" << endl;
    }

};

int main() {
   
//start as 2 x 2 array

    //goal state
  //nt goalState[2][2] = { {1, 2}, {3, 0}};

   // 1 2
   // 3 0

//input
   //int initialState[2][2] = { {1, 0}, {3, 2}};
    // 1 0
    // 3 2

    //operators
    //up, down, left, right
    //generalSearch(initialState);
    //int testState8[3][3] = { {1, 2, 3} , {5, 0, 6} , {4, 7, 8} };
   // int testState8[3][3] = { {1, 3, 6} , {5, 0, 2} , {4, 7, 8} };
      //int testState15[3][3] = { {1, 6, 4} , {5, 0, 7} , {2, 3, 8} };
    //int testState[3][3] = { {4, 2, 7} , {5, 3, 8} , {6, 1, 0} };

    //int testState17[3][3] = { {4, 3, 8} , {5, 0, 1} , {7, 2, 6} };
    //int testState
    int testState27[3][3] = { {3, 0, 7} , {8, 6, 4} , { 2, 5, 1}};

    auto start = std::chrono::high_resolution_clock::now();
    generalSearch(testState27);
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "Elapsed time: " << ms << " ms (" << ms / 1000.0 << " s)" << endl;

    return 0;
}