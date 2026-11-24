#include <iostream>
#include <string>

using namespace std;

struct Student {
    string name;
    int rollNumber;
    float marks;
    Student* left;
    Student* right;
    Student* parent;

    Student(string n, int r, float m)
        : name(n), rollNumber(r), marks(m), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct QueueNode {
    Student* data;
    QueueNode* next;

    QueueNode(Student* s) : data(s), next(nullptr) {}
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

    void push(Student* s) {
        QueueNode* newNode = new QueueNode(s);
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    Student* front() {
        if (frontNode != nullptr) {
            return frontNode->data;
        }
        return nullptr;
    }

    void pop() {
        if (frontNode == nullptr) return;
        QueueNode* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        count--;
    }
};

class StudentMaxHeap {
private:
    Student* root;
    int nodeCount;

    void swapStudentData(Student* a, Student* b) {
        string tempName = a->name;
        a->name = b->name;
        b->name = tempName;

        int tempRoll = a->rollNumber;
        a->rollNumber = b->rollNumber;
        b->rollNumber = tempRoll;

        float tempMarks = a->marks;
        a->marks = b->marks;
        b->marks = tempMarks;
    }

    Student* getNodeAt(int index) {
        if (index <= 0 || root == nullptr) return nullptr;
        if (index == 1) return root;

        int highestBit = 1;
        while ((highestBit << 1) <= index) {
            highestBit <<= 1;
        }

        Student* current = root;
        for (int bit = highestBit >> 1; bit > 0; bit >>= 1) {
            if (index & bit) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return current;
    }

    void heapifyUp(Student* node) {
        while (node->parent != nullptr && node->marks > node->parent->marks) {
            swapStudentData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(Student* node) {
        while (node != nullptr) {
            Student* largest = node;

            if (node->left != nullptr && node->left->marks > largest->marks) {
                largest = node->left;
            }
            if (node->right != nullptr && node->right->marks > largest->marks) {
                largest = node->right;
            }

            if (largest != node) {
                swapStudentData(node, largest);
                node = largest;
            } else {
                break;
            }
        }
    }

public:
    StudentMaxHeap() : root(nullptr), nodeCount(0) {}

    void insert(string name, int rollNumber, float marks) {
        Student* newNode = new Student(name, rollNumber, marks);
        nodeCount++;

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Student* parent = getNodeAt(nodeCount / 2);
        newNode->parent = parent;

        if (nodeCount % 2 == 0) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        heapifyUp(newNode);
    }

    void displayLevelOrder() {
        if (root == nullptr) 
        {
            cout << "Heap is empty.\n";
            return;
        }

        CustomQueue q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            cout << "Level " << level << ": ";

            for (int i = 0; i < levelSize; i++) 
            {
                Student* curr = q.front();
                q.pop();

                cout << "[" << curr->name << " | Roll: " << curr->rollNumber
                     << " | Marks: " << curr->marks << "] ";

                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }
            cout << "\n";
            level++;
        }
    }

    void deleteHighestMarks() {
        if (root == nullptr) 
        {
            cout << "Heap is empty. Nothing to delete.\n";
            return;
        }

        cout << "\nDeleting Top Merit Student -> " << root->name
             << " (Roll: " << root->rollNumber << ", Marks: " << root->marks << ")\n";

        if (nodeCount == 1) 
        {
            delete root;
            root = nullptr;
            nodeCount = 0;
            return;
        }

        Student* lastNode = getNodeAt(nodeCount);

        swapStudentData(root, lastNode);

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
    }
};

int main() 
{
    StudentMaxHeap meritHeap;

    meritHeap.insert("Ali", 101, 78.5);
    meritHeap.insert("Sara", 102, 85.0);
    meritHeap.insert("Bilal", 103, 92.0);
    meritHeap.insert("Ayesha", 104, 88.5);
    meritHeap.insert("Usman", 105, 95.0);
    meritHeap.insert("Zainab", 106, 81.0);

    cout << "=== Max Heap (Level Order Traversal) ===\n";
    meritHeap.displayLevelOrder();

    meritHeap.deleteHighestMarks();

    cout << "\n=== Updated Max Heap After Deletion & Heapify Down ===\n";
    meritHeap.displayLevelOrder();

    return 0;
}