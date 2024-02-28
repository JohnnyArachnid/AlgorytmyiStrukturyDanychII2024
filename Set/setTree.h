//Autor: Daniel Szarek

#include <vector>
#include "node.h"

class setTree {
private:

    Node *root;

    int getSize(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + getSize(node->left) + getSize(node->right);
    }

    void printSet(Node *node) {
        if (node != nullptr) {
            printSet(node->left);
            std::cout << node->value << std::endl;
            printSet(node->right);
        }
    }

    Node *insert(Node *node, int x) {
        if (node == nullptr) {
            return new Node(x);
        }
        if (x < node->value) {
            node->left = insert(node->left, x);
        } else if (x > node->value) {
            node->right = insert(node->right, x);
        }
        return node;
    }

    Node *findMin(Node *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node *withdraw(Node *node, int x) {
        if (node == nullptr) {
            return nullptr;
        }
        if (x < node->value) {
            node->left = withdraw(node->left, x);
        } else if (x > node->value) {
            node->right = withdraw(node->right, x);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                Node *temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                Node *temp = node;
                node = node->left;
                delete temp;
            } else {
                Node *temp = findMin(node->right);
                node->value = temp->value;
                node->right = withdraw(node->right, temp->value);
            }
        }
        return node;
    }

    bool isInSet(Node *node, int x) {
        if (node == nullptr) {
            return false;
        } else if (x < node->value) {
            return isInSet(node->left, x);
        } else if (x > node->value) {
            return isInSet(node->right, x);
        } else {
            return true;
        }
    }

    void clearSet(Node *node) {
        if (node != nullptr) {
            clearSet(node->left);
            clearSet(node->right);
            delete node;
        }
    }

    std::vector<Node *> traverseInOrder(Node *node) {
        std::vector<Node *> result;
        traverseInOrderHelper(node, result);
        return result;
    }

    void traverseInOrderHelper(Node *node, std::vector<Node *> &result) {
        if (node != nullptr) {
            traverseInOrderHelper(node->left, result);
            result.push_back(node);
            traverseInOrderHelper(node->right, result);
        }
    }

    bool isEqual(Node *node1, Node *node2) {
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        } else if (node1 != nullptr && node2 != nullptr) {
            return node1->value == node2->value && isEqual(node1->left, node2->left) && isEqual(node1->right, node2->right);
        } else {
            return false;
        }
    }

    bool isSubset(int value, Node *node) {
        if (node == nullptr) {
            return false;
        } else if (value < node->value) {
            return isSubset(value, node->left);
        } else if (value > node->value) {
            return isSubset(value, node->right);
        } else {
            return true;
        }
    }

    bool isSubset(Node *node1, Node *node2) {
        if (node1 == nullptr) {
            return true;
        } else if (node2 == nullptr) {
            return false;
        } else {
            return isSubset(node1->value, node2) && isSubset(node1->left, node2) && isSubset(node1->right, node2);
        }
    }

    void copyNodes(Node *node, Node *&newNode) {
        if (node != nullptr) {
            newNode = new Node(node->value);
            copyNodes(node->left, newNode->left);
            copyNodes(node->right, newNode->right);
        }
    }

    setTree &operator=(const setTree &other) {
        if (this != &other) {
            clearSet(root);
            copyNodes(other.root, root);
        }
        return *this;
    }

public:
    setTree();
    setTree(const setTree &other);
    int getSize();  
    void printSet(); 
    void insert(int x);
    void withdraw(int x);
    bool isInSet(int x); 
    void clearSet();
    setTree operator+(setTree& other);  
    setTree operator*(setTree& other);   
    setTree operator-(setTree& other);
    bool operator==(setTree& other);  
    bool operator<=(setTree& other);
    ~setTree();
};

setTree::setTree() : root(nullptr) {}

setTree::setTree(const setTree &other) : root(nullptr) { copyNodes(other.root, root); }

int setTree::getSize() { return getSize(root); }

void setTree::printSet() { printSet(root); }

void setTree::insert(int x) { root = insert(root, x); }

void setTree::withdraw(int x) { root = withdraw(root, x); }

bool setTree::isInSet(int x) { return isInSet(root, x); }

void setTree::clearSet() {
        clearSet(root);
        root = nullptr;
    }

setTree setTree::operator+(setTree &other) {
        setTree sum = *this;
        for (Node *node : traverseInOrder(other.root)) {
            sum.insert(node->value);
        }
        return sum;
    }

setTree setTree::operator*(setTree &other) {
        setTree intersection;
        for (Node *node : traverseInOrder(root)) {
            if (other.isInSet(node->value)) {
                intersection.insert(node->value);
            }
        }
        return intersection;
    }

setTree setTree::operator-(setTree &other) {
        setTree difference = *this;
        for (Node *node : traverseInOrder(other.root)) {
            if (difference.isInSet(node->value)) {
                difference.withdraw(node->value);
            }
        }
        return difference;
    }

bool setTree::operator==(setTree &other) { return isEqual(root, other.root); }

bool setTree::operator<=(setTree &other) { return isSubset(root, other.root); }

setTree::~setTree() { clearSet(root); }
