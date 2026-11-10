#include <iostream>
#include <string>
#include <queue>
using namespace std;
class Node {
public:
    string category;
    Node* left;
    Node* right;

    Node(string val) {
        category = val;
        left = nullptr;
        right = nullptr;
    }
};

void bfsTraversal(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    cout << "BFS Traversal (Level-by-Level Order):\n";

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << "[" << current->category << "] ";

        if (current->left != nullptr) 
        {
            q.push(current->left);
        }

        if (current->right != nullptr) 
        {
            q.push(current->right);
        }
    }
    cout << endl;
}

int main() 
{
    Node* root = new Node("Electronics");

    root->left = new Node("Mobiles");
    root->right = new Node("Clothing");

    root->left->left = new Node("Laptops");
    root->left->right = new Node("Accessories");

    root->right->left = new Node("Men");
    root->right->right = new Node("Women");

    bfsTraversal(root);

    return 0;
}