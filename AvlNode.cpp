#include <iostream>
#include "Tree.h"

Tree::AvlNode::AvlNode() : TreeNode() {

    level = 1;
}

Tree::AvlNode::AvlNode(int n) : TreeNode(n) {
    level = 1;
}

int Tree::AvlNode::height() {
    return level;
}

int Tree::AvlNode::height(TreeNode *q) {
    return q ? q->height() : 0;
}

int Tree::AvlNode::bfactor() {
    int r = height(R);
    int l = height(L);
    return height(R) - height(L);
}

void Tree::AvlNode::fixHeight() {
    int hl = height(L);
    int hr = height(R);
    level = (hl > hr ? hl : hr) + 1;
}

Tree::TreeNode *Tree::AvlNode::rightRotate(TreeNode *q) {
    TreeNode *p = L;
    L = p->R;
    p->R = this;
    fixHeight();
    p->fixHeight();
    return p;
}

Tree::TreeNode *Tree::AvlNode::leftRotate(TreeNode *q) {
    TreeNode *p = R;
    R = p->L;
    p->L = this;
    fixHeight();
    p->fixHeight();
    return p;
}

Tree::TreeNode *Tree::AvlNode::balance() {
    fixHeight();
    if (bfactor() == 2) {
        if (R && R->bfactor() < 0)
            R = R->rightRotate(nullptr);
        return leftRotate(nullptr);
    }
    if (bfactor() == -2) {
        if (L && L->bfactor() > 0)
            L = L->leftRotate(nullptr);
        return rightRotate(nullptr);
    }
    return this;
}

Tree::TreeNode *Tree::AvlNode::add(TreeNode *q, int n) {
    if (key == 0) {
        key = n;
        return this;
    }
    if (q == nullptr) {
        return new AvlNode(n);
    }
    if (n < q->key)
        q->L = add(q->L, n);
    else
        q->R = add(q->R, n);
    return q->balance();
}

Tree::TreeNode *Tree::AvlNode::findMin(Tree::TreeNode *p) {
    return p->L ? findMin(p->L) : p;
}

Tree::TreeNode *Tree::AvlNode::removeMin(Tree::TreeNode *p) {
    if (p->L == 0)
        return p->R;
    p->L = removeMin(p->L);
    return p->balance();
}

Tree::TreeNode *Tree::AvlNode::remove(TreeNode *p, int n) {
    if (!p){
        std::cout << "Not found" << std::endl;
        return 0;
    }
    if (n < p->key)
        p->L = remove(p->L, n);
    else if (n > p->key)
        p->R = remove(p->R, n);
    else {
        TreeNode *q = p->L;
        TreeNode *r = p->R;
        delete p;
        if (r == nullptr) return q;
        TreeNode *min = r->findMin(r);
        min->R = min->removeMin(r);
        min->L = q;
        return min->balance();
    }
    return p->balance();
}

Tree::TreeNode *Tree::AvlNode::find(int n) {
    if (key == n) {
        return this;
    }
    if (n > key && R != nullptr) {
        return R->find(n);
    }
    if (n < key && L != nullptr) {
        return L->find(n);
    }
    return nullptr;
}
