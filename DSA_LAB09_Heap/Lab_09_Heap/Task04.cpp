#include <iostream>
#include <string>

using namespace std;

struct Medicine {
    string name;
    int medicineID;
    int expiryDate;
    Medicine* left;
    Medicine* right;
    Medicine* parent;

    Medicine(string n, int id, int exp)
        : name(n), medicineID(id), expiryDate(exp), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct QueueNode {
    Medicine* data;
    QueueNode* next;

    QueueNode(Medicine* m) : data(m), next(nullptr) {}
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

    void push(Medicine* m) {
        QueueNode* newNode = new QueueNode(m);
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    Medicine* front() {
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

class MedicineMinHeap {
private:
    Medicine* root;
    int nodeCount;

    void swapMedicineData(Medicine* a, Medicine* b) {
        string tempName = a->name;
        a->name = b->name;
        b->name = tempName;

        int tempID = a->medicineID;
        a->medicineID = b->medicineID;
        b->medicineID = tempID;

        int tempExp = a->expiryDate;
        a->expiryDate = b->expiryDate;
        b->expiryDate = tempExp;
    }

    Medicine* getNodeAt(int index) {
        if (index <= 0 || root == nullptr) return nullptr;
        if (index == 1) return root;

        int highestBit = 1;
        while ((highestBit << 1) <= index) {
            highestBit <<= 1;
        }

        Medicine* current = root;
        for (int bit = highestBit >> 1; bit > 0; bit >>= 1) {
            if (index & bit) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return current;
    }

    void heapifyUp(Medicine* node) {
        while (node->parent != nullptr && node->expiryDate < node->parent->expiryDate) {
            swapMedicineData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(Medicine* node) {
        while (node != nullptr) {
            Medicine* smallest = node;

            if (node->left != nullptr && node->left->expiryDate < smallest->expiryDate) {
                smallest = node->left;
            }
            if (node->right != nullptr && node->right->expiryDate < smallest->expiryDate) {
                smallest = node->right;
            }

            if (smallest != node) {
                swapMedicineData(node, smallest);
                node = smallest;
            } else {
                break;
            }
        }
    }

public:
    MedicineMinHeap() : root(nullptr), nodeCount(0) {}

    void insert(string name, int medicineID, int expiryDate) {
        Medicine* newNode = new Medicine(name, medicineID, expiryDate);
        nodeCount++;

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Medicine* parent = getNodeAt(nodeCount / 2);
        newNode->parent = parent;

        if (nodeCount % 2 == 0) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        heapifyUp(newNode);
    }

    void displayLevelOrder() {
        if (root == nullptr) {
            cout << "No medicines in the store.\n";
            return;
        }

        CustomQueue q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            cout << "Level " << level << ": ";

            for (int i = 0; i < levelSize; i++) {
                Medicine* curr = q.front();
                q.pop();

                cout << "[" << curr->name << " | ID: " << curr->medicineID
                     << " | Expiry: " << curr->expiryDate << "] ";

                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }
            cout << "\n";
            level++;
        }
    }

    void deleteNearestExpiry() {
        if (root == nullptr) {
            cout << "No medicines to check or delete.\n";
            return;
        }

        cout << "\nMedicine with Nearest Expiry Date -> " << root->name
             << " (ID: " << root->medicineID << ", Expiry: " << root->expiryDate << ")\n";
        cout << "Deleting this medicine from stock...\n";

        if (nodeCount == 1) {
            delete root;
            root = nullptr;
            nodeCount = 0;
            return;
        }

        Medicine* lastNode = getNodeAt(nodeCount);

        swapMedicineData(root, lastNode);

        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = nullptr;
        } else {
            lastNode->parent->right = nullptr;
        }

        delete lastNode;
        nodeCount--;

        heapifyDown(root);
    }
};

int main() {
    MedicineMinHeap expiryHeap;

    expiryHeap.insert("Paracetamol", 401, 20270315);
    expiryHeap.insert("Amoxicillin", 402, 20261205);
    expiryHeap.insert("Ibuprofen", 403, 20270120);
    expiryHeap.insert("Insulin", 404, 20261130);
    expiryHeap.insert("Cetirizine", 405, 20270510);
    expiryHeap.insert("Omeprazole", 406, 20261225);

    cout << "=== Medicine Expiry Min Heap (Level Order Traversal) ===\n";
    expiryHeap.displayLevelOrder();

    expiryHeap.deleteNearestExpiry();

    cout << "\n=== Updated Min Heap After Deletion & Heapify Down ===\n";
    expiryHeap.displayLevelOrder();

    return 0;
}