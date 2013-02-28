/**
 *  Linked lists
 */

#include <iostream>
#include <map>

using namespace std;

class Node
{
    public:
        int data;
        Node* next;

    Node(int d)
    {
        data = d;
        next = NULL;
    }
    
    void appendToTail(int d)
    {
        Node* last = this; 
        while (last->next != NULL)
            last = last->next;

        last->next = new Node(d);
    }

    void printList()
    {
        Node* curr = this;
        while (curr != NULL)
        {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }

    Node* deleteFirstFromList(int d)
    {
        // If head needs to be deleted
        if (this->data == d)
        {
            Node* next = this->next;

            delete this;
            return next;
        }

        // Otherwise
        Node* curr = this;
        while (curr->next != NULL)
        {
            if (curr->next->data == d)
            {
                Node* tmp = curr->next;
                curr->next = curr->next->next;

                delete tmp;
                return this; // Head was not changed
            }
            curr = curr->next;
        }

        // If element was not found
        return this;
    }
};

// ------------------------------------ 2.1 -------------------------------------- //
/**
 *  Remove duplicates from an unosorted linked list
 */

/** Solution using map
 *
 *  Remarks:
 *      1. Head for sure won't be changed, so method is void
 */
void removeDups(Node* head)
{
    map<int, bool> used;
    used[head->data] = true;

    Node* curr = head;
    while(curr->next != NULL)
    {
        if (used[curr->next->data])
        {
            Node* tmp = curr->next;
            curr->next = curr->next->next;

            delete tmp;
        }
        else
        {
            used[curr->next->data] = true;
            curr = curr->next; 
        }
    }
}

/** FOLLOW UP: Solution without temporary buffer (map)
 *
 *  n^2 time complexity
 */
void removeDups_noBuf(Node* head)
{
    Node* base = head;
    while (base != NULL)
    {
        Node* runner = base;
        while (runner->next != NULL)
        {
            if (runner->next->data == base->data)
            {
                Node* tmp = runner->next;
                runner->next = runner->next->next;

                delete tmp;
            }
            else
                runner = runner->next;
        }
        base = base->next;
    }
}

// ------------------------------------ 2.2 -------------------------------------- //
/** Find the k-th to last element (k-th from the back) element of a singly linked list
 */

/** Solution - recursive
 */
Node* kToLast(Node* curr, int k, int& cnt)
{
    if (curr == NULL) return NULL;

    Node* nd = kToLast(curr->next, k, cnt);
    cnt = cnt + 1;
    if (cnt == k)
    {
        return curr;
    }

    return nd;
}

/** Solution - iterative
 *  Take 2 pointers, second k ahead of first. When second reaches end, first is pointing to k-th from end.
 */

// ------------------------------------ 2.3 -------------------------------------- //
/** Delete the middle element from the singly linked list, given only acces to that element.
 */
void deleteMiddle(Node* curr)
{
    if (curr == NULL || curr->next == NULL)
        return;

    // Copy data
    curr->data = curr->next->data;

    // Reroute and delete extra node
    Node* tmp = curr->next;
    curr->next = curr->next->next;

    delete tmp;
}

// ------------------------------------ 2.4 -------------------------------------- //
/** Given value x, rearrange the linked list so all elements smaller than x come before ones
 *  greater or equal to x.
 */

/** Solution - loop through list and if element < x, put it on the beginning of the list
 *  
 *  Remarks:
 *      1. Head is given by reference because it needs to be changed.
 *
 *  Good questions:
 *      1. Is it neccessary to preserve relative ordering of in each group of elements? - here I suppose it is not.
 */
void partitionList(Node*& head, int x)
{
    if (head == NULL) return;

    Node* curr = head;
    while (curr->next != NULL)
    {
        if (curr->next->data < x)
        {
            Node* tmp = curr->next;

            curr->next = curr->next->next;
            tmp->next = head;
            head = tmp;
        }
        else
            curr = curr->next;
    }
}

// ------------------------------------ 2.5 -------------------------------------- //
/** Two numbers are represented by linked lists. The digits are stored in reverse order.
 *  Sum them and return new list holding result.
 */

Node* sumReversed(Node* a, Node* b, int carry)
{
    if (a == NULL && b == NULL)
    {
        Node* res = NULL;
        if (carry != 0)
        {
            Node* tmp = new Node(carry);
            tmp->next = res;
            res = tmp;
        }
        return res;
    }

    int digit = (a ? a->data : 0) + (b ? b->data : 0) + carry;
    int carryNew = 0;
    if (digit > 10)
    {
        digit -= 10;
        carryNew = 1;
    }
    Node* res = new Node(digit);
    res->next = sumReversed(a->next, b->next, carryNew);

    return res;
}

/** FOLLOW UP: Do the same, but this time numbers are not reversed
 */

Node* sumListsInner(Node* a, Node* b, int& carry)
{
    if (a == NULL && b == NULL)
    {
        carry = 0;
        return NULL;
    }
    Node* toRight = sumListsInner(a->next, b->next, carry);

    int digit = a->data + b->data + carry;
    carry = 0;
    if (digit > 10)
    {
        digit -= 10;
        carry = 1;
    }

    Node* res = new Node(digit);
    res->next = toRight;

    return res;
}

Node* sumLists(Node* a, Node* b)
{
    // TO DO: If lists are not of the same size, pad smaller with zeroes

    int carry = 0;
    Node* res = sumListsInner(a, b, carry);

    if (carry != 0)
    {
        Node* tmp = new Node(carry);
        tmp->next = res;
        res = tmp;
    }
    return res;
}

// ------------------------------------ 2.6 -------------------------------------- //
/** Given a circular linked list, implement an algorithm which returns the node
 *  at the beginning of the loop.
 */

/** Solution - based on "Prove the list is circular" problem.
 *  
 *  We use 2 pointers - fastRunner and slowRunner. Slow runner advances by 1, while fast by 2.
 *  Eventually they will meet. Let's say slowRunner has come to the first node of circle after k steps.
 *  This also means k is the length of the non-circle part of the list. 
 *  Also, at this time fastRunner is k steps ahead of slowRunner (as it moves twice faster).
 *
 *  When will fastRunner and slowRunner meet?
 *  fastRunner also is (LOOP_SIZE - K) steps before slowRunner (where K = k % LOOP_SIZE), so they
 *  will meet after LOOP_SIZE - K steps. When they meet, it will be K steps away from start of loop (it can be easily seen
 *  by looking at slowRunner).
 *  
 *  How do we find the start of the circle now?
 *  We put one pointer at the collision spot, and another on the head of the list. We move them both by 1 and they will meet
 *  at the beginning of the circle after exactly k steps.
 *
 *  Why k, if collision spot was just K steps away from start?
 *  As k = K + M * LOOP_SIZE, after k steps the pointer which started from collision spot will finish on the same node
 *  as he would by doing only K steps.
 *
 */
Node* findCircStart(Node* head)
{
    Node* slowRunner = head;
    Node* fastRunner = head;

    // Get the collision point
    while(slowRunner != NULL && fastRunner != NULL)
    {
        slowRunner = slowRunner->next;
        fastRunner = fastRunner->next->next;
        if (slowRunner == fastRunner)
            break;
    }
    
    // Check for null values, if there is no circle
    if (slowRunner == NULL && fastRunner == NULL)
        return NULL;

    // Get the start of circle - there is circle for sure
    while(slowRunner != head)
    {
        slowRunner = slowRunner->next;
        head = head->next;
    }

    return slowRunner;
}


// ------------------------------------ 2.7 -------------------------------------- //
/** Implement a function to check if a linked list is a palindrome
 */

bool isPalindrome(Node* nd, Node*& head)
{
    if (nd == NULL) return true;

    bool ret = isPalindrome(nd->next, head);

    if (!ret) return false;

    bool checkRes = nd->data == head->data;
    head = head->next;

    return checkRes;
}

// ---------------------- Testing -------------------- //

int main()
{
    Node* a = new Node(6);
    a->appendToTail(7);
    a->appendToTail(8);
    a->appendToTail(8);
    a->appendToTail(7);
    a->appendToTail(6);

    cout << "List is: "; a->printList(); cout << endl;

    Node* head = a;
    bool res = isPalindrome(a, head);

    cout << "is palindrome: " << res << endl;

    return 0;
}
