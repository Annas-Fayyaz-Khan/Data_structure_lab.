#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string name) {
        this->name = name;
        this->left = nullptr;
        this->right = nullptr;
    }
};

void displayHierarchy(Node* node) {
    if (node == nullptr) return;

    string leftChild = (node->left != nullptr) ? node->left->name : "None";
    string rightChild = (node->right != nullptr) ? node->right->name : "None";

    cout << "Member: " << node->name << "\n";
    cout << "  Left Child:  " << leftChild << "\n";
    cout << "  Right Child: " << rightChild << "\n\n";

    displayHierarchy(node->left);
    displayHierarchy(node->right);
}

int main() 
{
    Node* root = new Node("Dr. Alice (HOD)");

    Node* coord1 = new Node("Prof. Bob (Coordinator 1)");
    Node* coord2 = new Node("Prof. Charlie (Coordinator 2)");

    Node* fac1 = new Node("Dr. David (Faculty 1)");
    Node* fac2 = new Node("Dr. Emma (Faculty 2)");
    Node* fac3 = new Node("Dr. Frank (Faculty 3)");
    Node* fac4 = new Node("Dr. Grace (Faculty 4)");

    root->left = coord1;
    root->right = coord2;

    coord1->left = fac1;
    coord1->right = fac2;

    coord2->left = fac3;
    coord2->right = fac4;

    displayHierarchy(root);

    return 0;
}