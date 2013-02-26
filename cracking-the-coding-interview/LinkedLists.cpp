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

int main()
{

    Node* head = new Node(23);
    head->appendToTail(34);
    head->appendToTail(11);
    head->appendToTail(2);
    head->appendToTail(11);
    head->appendToTail(11);
    head->appendToTail(34);
    head->appendToTail(2);
    head->appendToTail(2);
    head->appendToTail(2);
    head->appendToTail(11);

    cout << "Initial list: " << endl;
    head->printList();
    cout << endl;

    // Try deleting duplicates
    removeDups_noBuf(head);

    cout << "No duplicates: " << endl;
    head->printList();
    cout << endl;

    return 0;
}
