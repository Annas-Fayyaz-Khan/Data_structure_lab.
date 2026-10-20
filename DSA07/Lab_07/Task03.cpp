#include <iostream>
#include <string>
using namespace std;
#define MAX_PATIENTS 10 

struct Patient {
    string id;
    int priority;
};

class HospitalPriorityQueue {
private:
    Patient queue[MAX_PATIENTS];
    int count;

public:
    HospitalPriorityQueue() 
    {
        count = 0;
    }

    bool isFull() 
    {
        return count == MAX_PATIENTS;
    }

    bool isEmpty() 
    {
        return count == 0;
    }

    void enqueue(string patientID, int priority) {
        if (isFull()) 
        {
            cout << "[OVERFLOW] Queue is full! Cannot add patient " << patientID << ".\n";
            return;
        }

        int i = count - 1;
        while (i >= 0 && queue[i].priority > priority) {
            queue[i + 1] = queue[i]; 
            i--;
        }

        queue[i + 1].id = patientID;
        queue[i + 1].priority = priority;
        count++;

        cout << "Patient " << patientID << " registered with Priority " << priority << ".\n";
    }

    void dequeue() 
    {
        if (isEmpty()) 
        {
            cout << "[UNDERFLOW] Queue is empty! No patients waiting for treatment.\n";
            return;
        }

        cout << "Now treating patient: " << queue[0].id << " (Priority Level: " << queue[0].priority << ")\n";

        for (int i = 0; i < count - 1; i++) 
        {
            queue[i] = queue[i + 1];
        }
        count--;
    }

    void display() {
        if (isEmpty()) 
        {
            cout << "No patients currently in the waiting queue.\n";
            return;
        }

        cout << "\n--------------------------------------\n";
        cout << "  WAITING PATIENTS LIST (BY URGENCY)  \n";
        cout << "--------------------------------------\n";
        cout << "Patient ID\tPriority Level\n";
        cout << "--------------------------------------\n";
        for (int i = 0; i < count; i++) 
        {
            cout << queue[i].id << "\t\t" << queue[i].priority;
            if (queue[i].priority == 1) 
            {
                cout << " (Critical)";
            }
            cout << "\n";
        }
        cout << "--------------------------------------\n";
    }
};

int main() 
{
    HospitalPriorityQueue emergencyRoom;
    int choice, priority;
    string patientID;

    while (true) {
        cout << "\n====================================\n";
        cout << "  HOSPITAL EMERGENCY DEPARTMENT PRIORITY QUEUE  \n";
        cout << "====================================\n";
        cout << "1. Add Patient (Enqueue)\n";
        cout << "2. Treat Highest Priority Patient (Dequeue)\n";
        cout << "3. Display Waiting Patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Patient ID (e.g., P101, P102): ";
            cin >> patientID;
            cout << "Enter Priority Level (1 = Highest urgency, higher numbers = lower urgency): ";
            cin >> priority;
            emergencyRoom.enqueue(patientID, priority);
            break;
        case 2:
            emergencyRoom.dequeue();
            break;
        case 3:
            emergencyRoom.display();
            break;
        case 4:
            cout << "Exiting Emergency Management System.\n";
            return 0;
        default:
            cout << "Invalid choice! Please select a valid option.\n";
        }
    }

    return 0;
}