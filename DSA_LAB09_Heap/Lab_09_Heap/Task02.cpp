#include <iostream>
#include <string>

using namespace std;

struct Patient {
    string name;
    int patientID;
    int priority;
    Patient* left;
    Patient* right;
    Patient* parent;

    Patient(string n, int id, int p)
        : name(n), patientID(id), priority(p), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct QueueNode {
    Patient* data;
    QueueNode* next;

    QueueNode(Patient* p) : data(p), next(nullptr) {}
};

class CustomQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int count;

public:
    CustomQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    bool empty() {
        return frontNode == nullptr;
    }

    int size() {
        return count;
    }

    void push(Patient* p) {
        QueueNode* newNode = new QueueNode(p);
        if (rearNode == nullptr) 
        {
            frontNode = rearNode = newNode;
        } 
        else 
        {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    Patient* front() {
        if (frontNode != nullptr) {
            return frontNode->data;
        }
        return nullptr;
    }

    void pop() {
        if (frontNode == nullptr) return;
        QueueNode* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) 
        {
            rearNode = nullptr;
        }
        delete temp;
        count--;
    }
};

class HospitalMaxHeap {
private:
    Patient* root;
    int nodeCount;

    void swapPatientData(Patient* a, Patient* b) {
        string tempName = a->name;
        a->name = b->name;
        b->name = tempName;

        int tempID = a->patientID;
        a->patientID = b->patientID;
        b->patientID = tempID;

        int tempPriority = a->priority;
        a->priority = b->priority;
        b->priority = tempPriority;
    }

    Patient* getNodeAt(int index) {
        if (index <= 0 || root == nullptr) return nullptr;
        if (index == 1) return root;

        int highestBit = 1;
        while ((highestBit << 1) <= index) 
        {
            highestBit <<= 1;
        }

        Patient* current = root;
        for (int bit = highestBit >> 1; bit > 0; bit >>= 1) 
        {
            if (index & bit) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return current;
    }

    void heapifyUp(Patient* node) {
        while (node->parent != nullptr && node->priority > node->parent->priority) {
            swapPatientData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(Patient* node) {
        while (node != nullptr) {
            Patient* largest = node;

            if (node->left != nullptr && node->left->priority > largest->priority) 
            {
                largest = node->left;
            }
            if (node->right != nullptr && node->right->priority > largest->priority) 
            {
                largest = node->right;
            }

            if (largest != node) 
            {
                swapPatientData(node, largest);
                node = largest;
            } 
            else 
            {
                break;
            }
        }
    }

public:
    HospitalMaxHeap() : root(nullptr), nodeCount(0) {}

    void insert(string name, int patientID, int priority) {
        Patient* newNode = new Patient(name, patientID, priority);
        nodeCount++;

        if (root == nullptr) 
        {
            root = newNode;
            return;
        }

        Patient* parent = getNodeAt(nodeCount / 2);
        newNode->parent = parent;

        if (nodeCount % 2 == 0) 
        {
            parent->left = newNode;
        } 
        else 
        {
            parent->right = newNode;
        }

        heapifyUp(newNode);
    }

    void displayLevelOrder() {
        if (root == nullptr) 
        {
            cout << "No patients in the emergency queue.\n";
            return;
        }

        CustomQueue q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            cout << "Level " << level << ": ";

            for (int i = 0; i < levelSize; i++) {
                Patient* curr = q.front();
                q.pop();

                cout << "[" << curr->name << " | ID: " << curr->patientID
                     << " | Priority: " << curr->priority << "] ";

                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }
            cout << "\n";
            level++;
        }
    }

    void displayHighestPriority() {
        if (root == nullptr) 
        {
            cout << "No patients waiting.\n";
            return;
        }

        cout << "\nHighest Priority Patient -> " << root->name
             << " (ID: " << root->patientID << ", Priority: " << root->priority << ")\n";
    }

    void treatAndDeleteHighestPriority() 
    {
        if (root == nullptr) {
            cout << "No patients to treat.\n";
            return;
        }

        cout << "\nTreating & Removing Patient -> " << root->name
             << " (ID: " << root->patientID << ", Priority: " << root->priority << ")\n";

        if (nodeCount == 1) 
        {
            delete root;
            root = nullptr;
            nodeCount = 0;
            cout << "No more patients waiting for treatment.\n";
            return;
        }

        Patient* lastNode = getNodeAt(nodeCount);

        swapPatientData(root, lastNode);

        if (lastNode->parent->left == lastNode) 
        {
            lastNode->parent->left = nullptr;
        } 
        else 
        {
            lastNode->parent->right = nullptr;
        }

        delete lastNode;
        nodeCount--;

        heapifyDown(root);

        cout << "Next Patient for Treatment -> " << root->name
             << " (ID: " << root->patientID << ", Priority: " << root->priority << ")\n";
    }
};

int main() 
{
    HospitalMaxHeap emergencyHeap;

    emergencyHeap.insert("Ahmed", 201, 4);
    emergencyHeap.insert("Fatima", 202, 7);
    emergencyHeap.insert("Hassan", 203, 9);
    emergencyHeap.insert("Zoya", 204, 5);
    emergencyHeap.insert("Omar", 205, 10);
    emergencyHeap.insert("Hina", 206, 6);

    cout << "=== Hospital Emergency Max Heap (Level Order Traversal) ===\n";
    emergencyHeap.displayLevelOrder();

    emergencyHeap.displayHighestPriority();

    emergencyHeap.treatAndDeleteHighestPriority();

    cout << "\n=== Updated Emergency Max Heap ===\n";
    emergencyHeap.displayLevelOrder();

    return 0;
}