/**
 *  Stacks and queues
 */

#include <iostream>
#include <stack>

using namespace std;

// ------------------------------------ 3.1 -------------------------------------- //
/**
 *  Describe how you could use a single array to implement three stacks.
 */

/** Solution 1 - Fixed size to each stack (e.g. thirds)
 */

/** Solution 2 - Stacks are flexible in size
 *  
 *  Idea: When there is not enough space, expand stack by moving elements of others.
 */

// ------------------------------------ 3.2 -------------------------------------- //
/**
 *  Design a stack which can do also getMinElem() in O(1), besides push and pop operations.
 */

/** Solution - we have an extra stack to store minimal values
 */
class MinStack
{
    public:
        void push(int d)
        {
            data.push(d);

            if (mins.empty() || d <= mins.top()) 
                mins.push(d);
        }
        
        void pop()
        {
            if (data.top() == mins.top())
                mins.pop();

            data.pop();
        }
        
        int getMinElem()
        {
            return mins.top();
        }

    private:
        stack<int> data;
        stack<int> mins;
        
};


int main()
{
    MinStack myStack = MinStack();

    cout << "napravio stack" << endl;
    
    myStack.push(4);
    myStack.push(3);
    myStack.push(2);
    cout << "min: " << myStack.getMinElem() << endl;

    myStack.pop();
    cout << "min after pop: " << myStack.getMinElem() << endl;

    return 0;
}
