#include <iostream>
using namespace std;
#define MAX_SIZE 5 
class PassengerDeque {
private:
    int arr[MAX_SIZE];
    int front;
    int rear;
public:
    PassengerDeque() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == MAX_SIZE - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void insertFront(int requestID) {
        if (isFull()) 
        {
            cout << "[OVERFLOW] Deque is full! Cannot insert request " << requestID << " at front.\n";
            return;
        }

        if (isEmpty()) 
        {
            front = 0;
            rear = 0;
        } 
        else if (front == 0) 
        {
            front = MAX_SIZE - 1; 
        } 
        else 
        {
            front = front - 1;
        }

        arr[front] = requestID;
        cout << "Request " << requestID << " added at the FRONT.\n";
    }

    void insertRear(int requestID) {
        if (isFull()) 
        {
            cout << "[OVERFLOW] Deque is full! Cannot insert request " << requestID << " at rear.\n";
            return;
        }

        if (isEmpty()) 
        {
            front = 0;
            rear = 0;
        } 
        else if (rear == MAX_SIZE - 1) 
        {
            rear = 0; 
        } 
        else 
        {
            rear = rear + 1;
        }

        arr[rear] = requestID;
        cout << "Request " << requestID << " added at the REAR.\n";
    }

    void deleteFront() {
        if (isEmpty()) 
        {
            cout << "[UNDERFLOW] Deque is empty! No requests to remove from front.\n";
            return;
        }

        cout << "Removed request " << arr[front] << " from the FRONT.\n";

        if (front == rear) 
        {
            front = -1;
            rear = -1;
        } 
        else if (front == MAX_SIZE - 1) 
        {
            front = 0;
        } 
        else
        {
            front = front + 1;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "[UNDERFLOW] Deque is empty! No requests to remove from rear.\n";
            return;
        }

        cout << "Removed request " << arr[rear] << " from the REAR.\n";

        if (front == rear) 
        {
            front = -1;
            rear = -1;
        } 
        else if (rear == 0) 
        {
            rear = MAX_SIZE - 1;
        } 
        else 
        {
            rear = rear - 1;
        }
    }

    void display() {
        if (isEmpty()) 
        {
            cout << "Deque is empty! No pending passenger requests.\n";
            return;
        }

        cout << "Front -> ";
        int i = front;
        while (true) {
            cout << arr[i];
            if (i == rear) break;
            cout << ", ";
            i = (i + 1) % MAX_SIZE;
        }
        cout << " <- Rear\n";
    }
};

int main() {
    PassengerDeque deque;
    int choice, requestID;

    while (true) {
        cout << "\n====================================\n";
        cout << " TRAIN STATION PASSENGER MANAGEMENT \n";
        cout << "====================================\n";
        cout << "1. Insert Request at Front\n";
        cout << "2. Insert Request at Rear\n";
        cout << "3. Remove Request from Front\n";
        cout << "4. Remove Request from Rear\n";
        cout << "5. Display All Requests\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Passenger Request ID: ";
            cin >> requestID;
            deque.insertFront(requestID);
            break;
        case 2:
            cout << "Enter Passenger Request ID: ";
            cin >> requestID;
            deque.insertRear(requestID);
            break;
        case 3:
            deque.deleteFront();
            break;
        case 4:
            deque.deleteRear();
            break;
        case 5:
            deque.display();
            break;
        case 6:
            cout << "Exiting Passenger Management System.\n";
            return 0;
        default:
            cout << "Invalid choice! Please select a valid option.\n";
        }
    }

    return 0;
}