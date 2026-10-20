#include <iostream>
using namespace std;
#define SIZE 5 
class PacketBuffer {
private:
    int queue[SIZE];
    int front;
    int rear;

public:
    PacketBuffer() {
        front = -1;
        rear = -1;
    }

    bool isFull() 
    {
        return (rear + 1) % SIZE == front;
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int packetID) {
        if (isFull()) 
        {
            cout << "[OVERFLOW] Buffer is full! Packet " << packetID << " dropped.\n";
            return;
        }

        if (isEmpty()) 
        {
            front = 0;
            rear = 0;
        } 
        else 
        {
            rear = (rear + 1) % SIZE; 
        }

        queue[rear] = packetID;
        cout << "Packet " << packetID << " successfully added to buffer.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "[UNDERFLOW] Buffer is empty! No packets to transmit.\n";
            return;
        }

        cout << "Transmitted packet ID: " << queue[front] << "\n";

        if (front == rear) 
        {
           
            front = -1;
            rear = -1;
        } 
        else 
        {
            front = (front + 1) % SIZE;
        }
    }

    void display() {
        if (isEmpty()) 
        {
            cout << "No waiting packets in the buffer.\n";
            return;
        }

        cout << "Waiting packets in buffer: ";
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        cout << "\n";
    }
};

int main() 
{
    PacketBuffer buffer;
    int choice, packetID;

    while (true) {
        cout << "\n====================================\n";
        cout << "   NETWORK DATA PACKET MANAGER      \n";
        cout << "====================================\n";
        cout << "1. Insert Packet ID (Enqueue)\n";
        cout << "2. Transmit Oldest Packet (Dequeue)\n";
        cout << "3. Display Waiting Packets\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Packet ID: ";
            cin >> packetID;
            buffer.enqueue(packetID);
            break;
        case 2:
            buffer.dequeue();
            break;
        case 3:
            buffer.display();
            break;
        case 4:
            cout << "Exiting Packet Management System.\n";
            return 0;
        default:
            cout << "Invalid choice! Please select a valid option.\n";
        }
    }

    return 0;
}