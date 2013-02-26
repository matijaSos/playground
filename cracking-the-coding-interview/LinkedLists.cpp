/**
 *  Linked lists
 */

#include <iostream>

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

int main()
{

    Node* head = new Node(23);
    head->appendToTail(34);
    head->appendToTail(2);
    head->appendToTail(11);
    head->appendToTail(34);

    cout << "Initial list: " << endl;
    head->printList();
    cout << endl;

    // Try deleting
    cout << "Deleted head: " << endl;
    head = head->deleteFirstFromList(23);
    head->printList();
    cout << endl;

    cout << "Deleted first 34: " << endl;
    head = head->deleteFirstFromList(34);
    head->printList();
    cout << endl;
    
    cout << "Deleted first 323: " << endl;
    head = head->deleteFirstFromList(323);
    head->printList();
    cout << endl;

    return 0;
}
