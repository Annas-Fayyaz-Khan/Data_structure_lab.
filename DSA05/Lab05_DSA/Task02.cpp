#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    string name;
    Node* next;

    Node(string n) 
    {
        name = n;
        next = NULL;
    }
};

class Game {
private:
    Node* head;
    Node* tail;

public:
    Game() 
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
            tail->next = head;
        }
        else 
        {
            tail->next = t;
            tail = t;
            tail->next = head;
        }
    }

    void show() 
    {
        Node* t = head;

        cout << "\nPlayer Turns:\n";

        if (head == NULL)
            return;

        do 
        {
            cout << t->name << " -> ";
            t = t->next;
        } while (t != head);

        cout << head->name << " (First Player Again)\n";
    }
};

int main() 
{
    Game g;
    string n;

    cout << "Enter 5 player names:\n";

    for (int i = 1; i <= 5; i++) 
    {
        cout << "Player " << i << ": ";
        cin >> n;
        g.add(n);
    }

    g.show();

    return 0;
}