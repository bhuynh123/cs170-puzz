#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

//height, width, can be changed to make 15 puzzle or 24 puzzle, just need to change the state representation and goal test
constexpr int w = 3;

struct Node {
    int state[w][w]; //actualy state itself
    Node* parent;   
    string action; //backtrace to parent
    int depth;
    //hueristic values (h(n))
    int misplaced;
    int manhattan;
    int uniformCost;

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
        // 3x 3 = 9 + 1 < n is impossible
        misplaced = 100;
        // 4 is the most out of placed, 4 x 9  = 36 < n is impossible
        manhattan = 100;
        uniformCost = 0;
    }
};

//subroutine to copy states
void copyState(int end[w][w], const int original[w][w]) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            end[i][j] = original[i][j];
        }
    }
}

//print node for debugging
void printNode(Node* n) {

    cout << "Board:" << endl;

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++)
            cout << n->state[i][j] << " ";
        cout << endl;
    }

    cout << "Action: " << n->action;
   
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
void branchingFunction(Node* n, vector<Node*>& explore, const vector<Node*>& exploredAlready)  {
    //store location (x,y) of zero
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
        //move 0 up by swapping with tile above it
        swap(upNode->state[row][column], upNode->state[row-1][column]);
        //if not found in explored already, add to explore queue, else delete node
        if (!redundantSearch(upNode, exploredAlready)) {
            upNode->parent = n;
            upNode->action = "up";
            upNode->depth = n->depth + 1;
            explore.push_back(upNode);
        } else {
            delete upNode; 
        }
    }
    if (row < w - 1) { //down
        Node* downNode = new Node(n->state);
        //move 0 down by swapping with tile below it
        swap(downNode->state[row][column], downNode->state[row+1][column]);
        //if not found in explored already, add to explore queue, else delete node
        if (!redundantSearch(downNode, exploredAlready)) {
            downNode->parent = n;
            downNode->action = "down";
            downNode->depth = n->depth + 1;
            explore.push_back(downNode);
        } else {
            delete downNode;
        }
    }
    if (column > 0) { //left
        Node* leftNode = new Node(n->state);
        //move 0 left by swapping with tile to the left
        swap(leftNode->state[row][column], leftNode->state[row][column-1]);
        //if not found in explored already, add to explore queue, else delete node
        if (!redundantSearch(leftNode, exploredAlready)) {
            leftNode->parent = n;
            leftNode->action = "left";
            leftNode->depth = n->depth + 1;
            explore.push_back(leftNode);
        } else {
            delete leftNode;
        }
    }
    if (column < w - 1) { //right
        Node* rightNode = new Node(n->state);
        //move 0 right by swapping with tile to the right
        swap(rightNode->state[row][column], rightNode->state[row][column+1]);
        //if not found in explored already, add to explore queue, else delete node
        if (!redundantSearch(rightNode, exploredAlready)) {
            rightNode->parent = n;
            rightNode->action = "right";
            rightNode->depth = n->depth + 1;
            explore.push_back(rightNode);
        } else {
            delete rightNode;
        }
    }

}
//takes input to create goal state with the blank or 0 tile at the 2,2 index position
void generateGoalState(int goalState[w][w]) {
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < w; j++) {
            goalState[i][j] = i * w + j + 1;
        }
    }
    goalState[w- 1][w - 1] = 0; 
}
//goal test, checks if current node state is the same as the goal state
bool goalTest(Node* n) {

    int goalState[w][w];

    generateGoalState(goalState);
    
    //set last element to 0
    goalState[w-1][w-1] = 0; 
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
        cout << endl << "g(n) (depth): " << path[i]->depth << endl;

        if(path[i]->misplaced != 100) {
            cout << "Misplaced Tiles h(n): " << path[i]->misplaced << endl;
        }

        if(path[i]->manhattan != 100) {
            cout << "Manhattan Distance h(n): " << path[i]->manhattan << endl;
        }
         cout << endl;  
    }

    // print depth (number of moves from initial to goal)
    cout << "Solution depth (moves): " << n->depth << endl;

    cout << endl;
}

//didn't add b/c cost of 0 
void uniformCost(vector<Node*>& nodes) {
    //since h(n) = 0 for uniform cost search, no need to reorder queue, branching function adds nodes in order of depth, so its already ordered by g(n)
    sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return (a->uniformCost + a->depth) < (b->uniformCost + b->depth);
    });
}

void uniformCostSearch(int initialState[w][w]) {
    
    //nodes = Make-Queue(MAKE-NODE(initialState))
    vector<Node*> explore;
    explore.push_back(new Node(initialState));
    int maxQueueSize = 0;
    //store redundant states to avoid loops
    vector<Node*> visited;
    bool found = false;

    //loop do
    while (!explore.empty()) {

        //node = REMOVE-FRONT(nodes)
        Node* currentNode = explore.front();
        explore.erase(explore.begin());
        visited.push_back(currentNode);


        //if problem.GOAL-TEST(node.STATE) succeeds, return solution
        if (goalTest(currentNode)) {
            cout << "Goal found" << endl;
            found = true;
            backtrace(currentNode);
            cout << "Max queue size during search: " << maxQueueSize << endl;
            cout << "Nodes Explored: " << visited.size() << endl;
            break;
        }
        //nodes = queueiong function(nodes, expand(nodes, problem.operators))
        branchingFunction(currentNode, explore, visited);
        //since h(n) = 0 for uniform cost search, no need to reorder queue, branching function adds nodes in order of depth, so its already ordered by g(n)


        if(explore.size() > maxQueueSize) {
            maxQueueSize = explore.size();
        }
    }

    if (!found && explore.empty()) {
        cout << "No Solution found" << endl;
    }

};

int misplacedTiles(Node* n) {
    
    int goalState[w][w];
    generateGoalState(goalState);
    int value = 0;

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < w; j++) {
            // if nodes != goal state, not counting 0 or blank tile
            if(n->state[i][j] != goalState[i][j] && n->state[i][j] != 0) {
                value++;
            }
        }
    }

    n->misplaced = value;
    return value;
};

void reorderByMisplaced(vector<Node*>& nodes) {
    //sort vector based on heuristic value of each node
    sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return (misplacedTiles(a) + a->depth) < (misplacedTiles(b) + b->depth);
    });
}

//same as uniform search, but can't reorder a queue from the library so using a vector instead and sorting it based on the heuristic value of each node
void misplacedTileSearch(int initialState[w][w]) {
    
    //nodes = Make-Queue(MAKE-NODE(initialState))
    vector<Node*> explore;
    explore.push_back(new Node(initialState));
    int maxQueueSize = 0;
    //store redundant states to avoid loops
    vector<Node*> visited;
    bool found = false;

    //loop do
    while (!explore.empty()) {

        //node = REMOVE-FRONT(nodes)
        Node* currentNode = explore.front();
        explore.erase(explore.begin());
        visited.push_back(currentNode);

        //if problem.GOAL-TEST(node.STATE) succeeds, return solution
        if (goalTest(currentNode)) {
            cout << "Goal found" << endl;
            found = true;
            backtrace(currentNode);
            cout << "Max queue size: " << maxQueueSize << endl;
            cout << "Nodes Explored: " << visited.size() << endl;
            break;
        }
        //nodes = queueiong function(nodes, expand(nodes, problem.operators))
        branchingFunction(currentNode, explore, visited);
        //sorts queue by f(n) = g(n) + h(n)
        reorderByMisplaced(explore);

            if(explore.size() > maxQueueSize) {
                maxQueueSize = explore.size();
            }

    }

    if (!found && explore.empty()) {
        cout << "No Solution found" << endl;
    }


};

int manhattanDistance(Node* n) {
    //hardcoded goal positions for each tile, index 0 is tile 1, index 1 is tile 2, etc.
    vector<pair<int, int>> goalPositions = { {0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1} };
    int value = 0;

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < w; j++) {
        
            if( n->state[i][j] != 0) {
                //calc manhattan dists = absc(current row - goal row) + abs(current col - goal col)
                value += (abs(i - goalPositions[n->state[i][j] - 1].first) + abs(j - goalPositions[n->state[i][j] - 1].second));
                
            }
        }
    }
    n->manhattan = value;
    return value;

};

void reorderByManhattan(vector<Node*>& nodes) {
    //sort vector based on heuristic value of each node
    sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return (manhattanDistance(a) + a->depth) < (manhattanDistance(b) + b->depth);
    });
}

void manhattanDistanceSearch(int initialState[w][w]) {

//nodes = Make-Queue(MAKE-NODE(initialState))
    vector<Node*> explore;
    int maxQueueSize = 0;
    explore.push_back(new Node(initialState));
    //store redundant states to avoid loops
    vector<Node*> visited;
    bool found = false;

    //loop do
    while (!explore.empty()) {

        //node = REMOVE-FRONT(nodes)
        Node* currentNode = explore.front();
        explore.erase(explore.begin());
        visited.push_back(currentNode);

        //if problem.GOAL-TEST(node.STATE) succeeds, return solution
        if (goalTest(currentNode)) {
            cout << "Goal found" << endl;
            found = true;
            backtrace(currentNode);
            cout << "Max queue size during search: " << maxQueueSize << endl;
            cout << "Nodes Explored: " << visited.size() << endl;
            break;
        }
        //nodes = queueiong function(nodes, expand(nodes, problem.operators))
        branchingFunction(currentNode, explore, visited);
        //sorts queue by f(n) = g(n) + h(n)
        reorderByManhattan(explore);

        if(explore.size() > maxQueueSize) {
            maxQueueSize = explore.size();
        }
    }

    if (!found && explore.empty()) {
        cout << "No Solution found" << endl;
    }

}

int main() {

    
    cout << "Welcome to my 170 8-Puzzle Solver. Type '1' to use a default puzzle, or '2' to create your own" << endl;
    int choice;
    int customState[w][w];
    cin >> choice;
    if (choice == 1) {

        cout << "You wish to use a default puzzle. Please enter a desired difficulty on a scale from 1 to 5 (1 being the easiest)." << endl << endl;
        
        int defaultChoice;
        cin >> defaultChoice;

        if (defaultChoice == 1) {
            cout << "Trivial puzzle selected" << endl;
            const int trivial[w][w]  = { {1, 2, 3} , {4, 5, 6} , {7, 8, 0} };
            copyState(customState, trivial);
        }
        if ( defaultChoice == 2) {
            cout << "Very Easy puzzle selected" << endl;
            const int veryEasy[w][w]  = { {1, 2, 3} , {4, 5, 6} , {7, 0, 8} };
            copyState(customState, veryEasy);
        }
        if (defaultChoice == 3) {
            cout << "Easy puzzle selected" << endl;
            const int easy[w][w]  = { {1, 2, 0} , {4, 5, 3} , {7, 8, 6} };
            copyState(customState, easy);
        }
        if (defaultChoice == 4) {
            cout << "Doable puzzle selected" << endl;
            const int doable[w][w]  = { {0, 1, 2} , {4, 5, 3} , {7, 8, 6} };
            copyState(customState, doable);
        }
        if (defaultChoice == 5) {
            cout << "OH BOY" << endl;
            const int ohBoy[w][w]  = { {8, 7, 1} , {6, 0, 2} , {5, 4, 3} };
            copyState(customState, ohBoy);
        }

        
    }
    if (choice == 2) {
        //custom puzzle
        cout << " Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles. " << endl;
        cout << "Enter the puzzle delimiting the numbers with a space. Once you have completed a line, PRESS ENTER to Start a new line" << endl;

        cout << "Example: " << endl;
        cout << "First row: 1 2 3 *press ENTER*" << endl;
        cout << "Second row: 4 5 6 *press ENTER*" << endl;
        cout << "Third row: 7 8 0 *press ENTER*" << endl << endl << endl;

        for (int i = 0; i < w; i++) {
            if (i == 0) {
                cout << "First row: ";
            } 
            else if (i == 1) {
                cout << "Second row: ";
            } 
            else {
                cout << "Third row: ";
            }
            for (int j = 0; j < w; j++) {
                cin >> customState[i][j];
            }
        }
    }

    cout << "Select algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) the Manhattan Distance Heuristic." << endl;
    int searchChoice;
    cin >> searchChoice;

    if(searchChoice == 1) {
        cout << "Uniform Cost Search selected " << endl;
        uniformCostSearch(customState);
    } 
    else if (searchChoice == 2) {
        cout << "Misplaced Tile Heuristic selected" << endl;
          misplacedTileSearch(customState);
    } 
    else if (searchChoice == 3) {
        cout << "Manhattan Distance Heuristic selected" << endl;
        manhattanDistanceSearch(customState);
    } 
    else {
        cout << "Invalid choice. Exiting." << endl;
    }
       
    
    return 0;
}