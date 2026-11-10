#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    string folderName;
    Node* left;
    Node* right;

    Node(string name) {
        folderName = name;
        left = nullptr;
        right = nullptr;
    }
};

void preOrder(Node* root) {
    if (root == nullptr) return;
    cout << "[" << root->folderName << "] ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << "[" << root->folderName << "] ";
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << "[" << root->folderName << "] ";
}

int main() 
{
    Node* root = new Node("Root (C:)");

    root->left = new Node("Documents");
    root->right = new Node("Pictures");

    root->left->left = new Node("Work");
    root->left->right = new Node("Personal");

    root->right->left = new Node("Vacation");
    root->right->right = new Node("Family");

    cout << "--- Pre-Order Traversal (Root -> Left -> Right) ---\n";
    preOrder(root);
    cout << "\n\n";

    cout << "--- In-Order Traversal (Left -> Root -> Right) ---\n";
    inOrder(root);
    cout << "\n\n";

    cout << "--- Post-Order Traversal (Left -> Right -> Root) ---\n";
    postOrder(root);
    cout << "\n";

    return 0;
}