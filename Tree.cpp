#include <iostream>
#include "Tree.h"

using namespace std;

Tree::Tree() {
    root = nullptr;
    tp = new TreePrinter();
}

Tree::Tree(int n) {
    add(n);
}

Tree::Tree(std::string input) {
    if (input == "AVL") {
        root = new AvlNode();
    } else if (input == "RB") {
        root = new RbNode();
    } else {
        root = nullptr;
    }
    type = input;
    tp = new TreePrinter();
}

Tree::Tree(int N, int *arr) {
    root = nullptr;
    for (int i = 0; i < N; i++) {
        add(arr[i]);
    }
}

Tree::~Tree() {
    if (root != nullptr) {
        delete root;
    }
}

void Tree::print(int tt) {
    if (root != nullptr && root->key != 0) {
        tp->printTree(tt, root, nullptr, false);
    } else {
        cout << "No elements" << endl;
    }
}

void Tree::add(int n) {
    if (root != nullptr) {
        /*root = root->add(root, n);*/
        root = *root + n;
    } else {
        if (type == "AVL")
            root = new AvlNode(n);
        else if (type == "RB")
            root = new RbNode(n);
        else
            root = new TreeNode(n);
    }
}

void Tree::remove(int n) {
    /*root = root->remove(root, n);*/
    if (root == nullptr) {
        cout << "Not found" << endl;
    } else
        root = *root - n;
}

Tree::TreeNode *Tree::remove(TreeNode *q, int n) {
    if (q == nullptr)
        return q;
    if (n < q->key)
        q->L = remove(q->L, n);
    else if (n > q->key)
        q->R = remove(q->R, n);
    else if (q->L != nullptr && q->R != nullptr) {
        q->key = q->minNode(q->R)->key;
        q->R = remove(q->R, q->key);
    } else {
        if (q->L != nullptr)
            q = q->L;
        else
            q = q->R;
    }
    balance();
    return q;
}

bool Tree::find(int n) {
    if (root != nullptr) {
        return root->find(n);
    } else
        return false;
}

void Tree::balance() {
    if (root != nullptr) {
        root = root->balance();
    } else
        cout << "There's nothing to balance" << endl;
};

void Tree::rand(int n) {
    for (int i = 0; i < n; ++i)
        add(std::rand());
}