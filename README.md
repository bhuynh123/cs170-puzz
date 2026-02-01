# cs170-puzz
cs170porject

Follow basic outline of search algorithm


1. start 2 x 2 -> 3 x 3
    a. need to decide if array or vector
    b. not sure if memory matters yet
2. create branching function
    a. operators : up donw left right
    b. need to create a guard function so operators don't go outside of array
    c. q -ing function  need to figure out how to put 2d vector or array on the stack if it matters
    d. sometthing like this:
        Node {
        state   // board representation
        parent  // previous node
        action  // move taken
        cost    // path cost
        }
3. uniform cost
4. hueristic
5. misplaced tile


void generalSearch(problem, q-ing function) {

    nodes = make-q(make-node(problem.inital state))

    loop do

    if empty(nodes)

        return failure

        node = remove-front(nodes)

    if problem.testforgoal (node state) succeeds then return node
        node = q-ing func(node, expand(node problem.operator))

    end
}
