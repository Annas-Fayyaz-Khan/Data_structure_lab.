#include <iostream>
using namespace std;
#define MAX_SIZE 5 

class BankQueue {
private:
    int queue[MAX_SIZE];
    int front;
    int rear;

public:
    BankQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return rear == MAX_SIZE - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(int token) {
        if (isFull()) 
        {
            cout << "[OVERFLOW] Queue is full! Cannot add token " << token << ".\n";
            return;
        }
        
        if (front == -1) 
        {
            front = 0; 
        }
        
        rear++;
        queue[rear] = token;
        cout << "Customer token " << token << " added to the queue.\n";
    }

    void dequeue() {
        if (isEmpty()) 
        {
            cout << "[UNDERFLOW] Queue is empty! No customers to serve.\n";
            return;
        }

        cout << "Serving customer with token number: " << queue[front] << "\n";
        front++;

        if (front > rear) 
        {
            front = -1;
            rear = -1;
        }
    }

    void display() {
        if (isEmpty()) 
        {
            cout << "No waiting customers in the queue.\n";
            return;
        }

        cout << "Waiting customer tokens: ";
        for (int i = front; i <= rear; i++) 
        {
            cout << queue[i] << " ";
        }
        cout << "\n";
    }

    void displayCount() {
        if (isEmpty()) 
        {
            cout << "Number of waiting customers: 0\n";
        } 
        else 
        {
            cout << "Number of waiting customers: " << (rear - front + 1) << "\n";
        }
    }
};

int main() 
{
    BankQueue bank;
    int choice, token;

    while (true) {
        cout << "\n====================================\n";
        cout << "    BANK CUSTOMER SERVICE SYSTEM    \n";
        cout << "====================================\n";
        cout << "1. Enqueue (Add Customer Token)\n";
        cout << "2. Dequeue (Serve Next Customer)\n";
        cout << "3. Display All Waiting Customers\n";
        cout << "4. Display Number of Waiting Customers\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter customer token number: ";
            cin >> token;
            bank.enqueue(token);
            break;
        case 2:
            bank.dequeue();
            break;
        case 3:
            bank.display();
            break;
        case 4:
            bank.displayCount();
            break;
        case 5:
            cout << "Exiting system. Have a great day!\n";
            return 0;
        default:
            cout << "Invalid choice! Please select a valid option.\n";
        }
    }

    return 0;
}