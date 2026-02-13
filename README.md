# cs170-puzz
cs170project
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
   
        state   
   
        parent  
   
        action  

       child
   
        }

    e. store already explored notes and compare them to remove redundant states
       i. need to create function that compares them and returns boolean
    
4. uniform cost
    a. finished uniform cost for 2 x 2, then tweaked it for 8 x 8 2/3/2036 at least to find a solution
        i. need to handle when there is no solution b/c nothing happens

before i move on to step 5, I need to incorprate the interface
5. hueristic
6. misplaced tile

