#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    string song;
    Node* next;

    Node(string s) 
    {
        song = s;
        next = NULL;
    }
};

class Playlist {
private:
    Node* head;
    Node* tail;

public:
    Playlist() 
    {
        head = NULL;
        tail = NULL;
    }

    void add(string s) 
    {
        Node* t = new Node(s);

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

        cout << "\nAll Songs:\n";

        if (head == NULL)
            return;

        do 
        {
            cout << t->song << " -> ";
            t = t->next;
        } while (t != head);

        cout << "Back to First Song\n";
    }

    void play() 
    {
        Node* t = head;

        cout << "\nPlaying Playlist (2 Complete Rounds):\n";

        for (int i = 1; i <= 2; i++) 
        {
            cout << "\nRound " << i << ":\n";

            for (int j = 1; j <= 5; j++) 
            {
                cout << "Playing: " << t->song << endl;
                t = t->next;
            }
        }
    }
};

int main() 
{
    Playlist p;
    string s;

    cout << "Enter 5 song names:\n";

    for (int i = 1; i <= 5; i++) 
    {
        cout << "Song " << i << ": ";
        cin >> s;
        p.add(s);
    }

    p.show();
    p.play();

    return 0;
}