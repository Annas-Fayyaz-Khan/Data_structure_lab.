
#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    string web;
    Node* prev;
    Node* next;

    Node(string w) 
    {
        web = w;
        prev = NULL;
        next = NULL;
    }
};

class Browser {
private:
    Node* head;
    Node* tail;

public:
    Browser() 
    {
        head = NULL;
        tail = NULL;
    }

    void add(string w) 
    {
        Node* n = new Node(w);

        if (head == NULL) 
        {
            head = tail = n;
        }
        else 
        {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }

    void show() 
    {
        Node* t = head;

        cout << "\nHistory (First to Last):\n";

        while (t != NULL) 
        {
            cout << t->web << " -> ";
            t = t->next;
        }

        cout << "NULL\n";
    }

    void rev() 
    {
        Node* t = tail;

        cout << "\nHistory (Last to First):\n";

        while (t != NULL) 
        {
            cout << t->web << " -> ";
            t = t->prev;
        }

        cout << "NULL\n";
    }
};

int main() 
{
    Browser b;
    string w;

    cout << "Enter 5 website names:\n";

    for (int i = 1; i <= 5; i++) 
    {
        cout << "Website " << i << ": ";
        cin >> w;
        b.add(w);
    }

    b.show();
    b.rev();

    return 0;
}