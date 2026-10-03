#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    string img;
    Node* prev;
    Node* next;

    Node(string n) 
    {
        img = n;
        prev = NULL;
        next = NULL;
    }
};

class Gallery {
private:
    Node* head;
    Node* tail;

public:
    Gallery() 
    {
        head = NULL;
        tail = NULL;
    }

    void add(string n) 
    {
        Node* t = new Node(n);

        if (head == NULL) 
        {
            head = tail = t;
        }
        else 
        {
            tail->next = t;
            t->prev = tail;
            tail = t;
        }
    }

    void show() 
    {
        Node* t = head;

        cout << "\nImages (First to Last):\n";

        while (t != NULL) 
        {
            cout << t->img << " -> ";
            t = t->next;
        }

        cout << "NULL\n";
    }

    void rev() 
    {
        Node* t = tail;

        cout << "\nImages (Last to First):\n";

        while (t != NULL) 
        {
            cout << t->img << " -> ";
            t = t->prev;
        }

        cout << "NULL\n";
    }
};

int main() 
{
    Gallery g;
    string n;

    cout << "Enter 5 image names:\n";

    for (int i = 1; i <= 5; i++) 
    {
        cout << "Image " << i << ": ";
        cin >> n;
        g.add(n);
    }

    g.show();
    g.rev();

    return 0;
}