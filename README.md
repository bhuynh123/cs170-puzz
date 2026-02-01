# cs170-puzz
cs170porject

Follow basic outline of search algorithm


1. start 2 x 2 -> 3 x 3
    a. need to decide if array or vector
    b. not sure if memory matters yet
2. create branching function
    a. operators : up donw left right
   
    b. need to create a guard function so operators don't go outside of array
   
    c. q -ing function need to figure out how to put 2d vector or array on the stack if it matters
   
    d. something like this:
   
        Node {
   
        state   // board representation
   
        parent  // previous node
   
        action  // move taken
   
        cost    // path cost
   
        }
4. uniform cost

5. heuristic

6. misplaced tile
