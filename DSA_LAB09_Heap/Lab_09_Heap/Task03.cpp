#include <iostream>
#include <string>

using namespace std;

struct Order {
    int orderID;
    string customerName;
    float orderAmount;
    Order* left;
    Order* right;
    Order* parent;

    Order(int id, string name, float amount)
        : orderID(id), customerName(name), orderAmount(amount), left(nullptr), right(nullptr), parent(nullptr) {}
};

class OrderMaxHeap {
private:
    Order* root;
    int nodeCount;

    void swapOrderData(Order* a, Order* b) {
        int tempID = a->orderID;
        a->orderID = b->orderID;
        b->orderID = tempID;

        string tempName = a->customerName;
        a->customerName = b->customerName;
        b->customerName = tempName;

        float tempAmount = a->orderAmount;
        a->orderAmount = b->orderAmount;
        b->orderAmount = tempAmount;
    }

    Order* getNodeAt(int index) {
        if (index <= 0 || root == nullptr) return nullptr;
        if (index == 1) return root;

        int highestBit = 1;
        while ((highestBit << 1) <= index) {
            highestBit <<= 1;
        }

        Order* current = root;
        for (int bit = highestBit >> 1; bit > 0; bit >>= 1) {
            if (index & bit) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return current;
    }

    void heapifyUp(Order* node) {
        while (node->parent != nullptr && node->orderAmount > node->parent->orderAmount) {
            swapOrderData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(Order* node) {
        while (node != nullptr) {
            Order* largest = node;

            if (node->left != nullptr && node->left->orderAmount > largest->orderAmount) {
                largest = node->left;
            }
            if (node->right != nullptr && node->right->orderAmount > largest->orderAmount) {
                largest = node->right;
            }

            if (largest != node) {
                swapOrderData(node, largest);
                node = largest;
            } else {
                break;
            }
        }
    }

public:
    OrderMaxHeap() : root(nullptr), nodeCount(0) {}

    void insert(int orderID, string customerName, float orderAmount) {
        Order* newNode = new Order(orderID, customerName, orderAmount);
        nodeCount++;

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Order* parent = getNodeAt(nodeCount / 2);
        newNode->parent = parent;

        if (nodeCount % 2 == 0) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        heapifyUp(newNode);
    }

    float deleteRoot() {
        if (root == nullptr) {
            return -1.0f;
        }

        float deletedAmount = root->orderAmount;

        if (nodeCount == 1) {
            delete root;
            root = nullptr;
            nodeCount = 0;
            return deletedAmount;
        }

        Order* lastNode = getNodeAt(nodeCount);

        swapOrderData(root, lastNode);

        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = nullptr;
        } else {
            lastNode->parent->right = nullptr;
        }

        delete lastNode;
        nodeCount--;

        heapifyDown(root);

        return deletedAmount;
    }

    void heapSortAndDisplay() {
        if (nodeCount == 0) {
            cout << "No orders to sort.\n";
            return;
        }

        int totalOrders = nodeCount;
        float* sortedAmounts = new float[totalOrders];

        for (int i = totalOrders - 1; i >= 0; i--) {
            sortedAmounts[i] = deleteRoot();
        }

        cout << "=== Order Amounts in Ascending Order (Smallest to Largest) ===\n";
        for (int i = 0; i < totalOrders; i++) {
            cout << sortedAmounts[i];
            if (i < totalOrders - 1) {
                cout << " -> ";
            }
        }
        cout << "\n";

        delete[] sortedAmounts;
    }
};

int main() {
    OrderMaxHeap orderHeap;

    orderHeap.insert(301, "Ali", 4500.50);
    orderHeap.insert(302, "Sara", 1200.00);
    orderHeap.insert(303, "Bilal", 8900.75);
    orderHeap.insert(304, "Ayesha", 3100.25);
    orderHeap.insert(305, "Usman", 6750.00);
    orderHeap.insert(306, "Zainab", 2300.50);

    orderHeap.heapSortAndDisplay();

    return 0;
}