#include <iostream>
#include "Tree.h"

using namespace std;

Tree::TreeNode::TreeNode() {
    L = nullptr;
    R = nullptr;
    P = nullptr;
    key = 0;
}

Tree::TreeNode::TreeNode(int n) {
    key = n;
    L = nullptr;
    R = nullptr;
    P = nullptr;
}

Tree::TreeNode::~TreeNode() {
    if(P && this == P->R){
        P->R = nullptr;
    }
    else if (P){
        P->L = nullptr;
    }
    P = nullptr;
    L = nullptr;
    R = nullptr;
}

Tree::TreeNode *Tree::TreeNode::add(TreeNode *q, int n) {
    if (key < n) {
        if (R != nullptr) {
            R = R->add(R, n);
            return this;
        }
        R = new TreeNode(n);
        return this;
    }
    if (key > n) {
        if (L != nullptr) {
            L = L->add(L, n);
            return this;
        }
        L = new TreeNode(n);
        return this;
    }
    return this;
}

Tree::TreeNode* Tree::TreeNode::find(int n) {
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

Tree::TreeNode *Tree::TreeNode::balance() {
    return this;
}

Tree::TreeNode *Tree::TreeNode::maxNode(TreeNode *root) {
    if (root->R == nullptr)
        return root;
    return minNode(root->R);
};

Tree::TreeNode *Tree::TreeNode::minNode(TreeNode *root) {
    if (root->L == nullptr)
        return root;
    return minNode(root->L);
};

Tree::TreeNode *Tree::TreeNode::rightRotate(TreeNode *q) {
    return this;
}

Tree::TreeNode *Tree::TreeNode::leftRotate(TreeNode *q) {
    return this;
}

int Tree::TreeNode::bfactor() {
    return 0;
}

void Tree::TreeNode::fixHeight() {
}

int Tree::TreeNode::height() {
    return 0;
}

int Tree::TreeNode::height(TreeNode *q) {
    return 0;
}

Tree::TreeNode *Tree::TreeNode::findMin(Tree::TreeNode *p) {
    return p->L ? findMin(p->L) : p;
}

Tree::TreeNode *Tree::TreeNode::removeMin(Tree::TreeNode *p) {
    if (p->L == 0)
        return p->R;
    p->L = removeMin(p->L);
    return p->balance();
}

int Tree::TreeNode::getColor(){
    return 0;
}

void Tree::TreeNode::fixAdd(TreeNode* q){

}

Tree::TreeNode* Tree::TreeNode::getUncle(){
    return this;
}

Tree::TreeNode* Tree::TreeNode::getGrand(){
    return this;
}

void Tree::TreeNode::setColor(int i) {

}

void Tree::TreeNode::setParent(TreeNode *par){

}

Tree::TreeNode* Tree::TreeNode::getSibling() {
    return this;
}

void Tree::TreeNode::rightRotate() {
}

void Tree::TreeNode::leftRotate() {
}

void Tree::TreeNode::delete_1(TreeNode *n){

}

void Tree::TreeNode::delete_2(TreeNode *n){

}

void Tree::TreeNode::delete_3(TreeNode *n){

}

void Tree::TreeNode::delete_4(TreeNode *n){

}

void Tree::TreeNode::delete_5(TreeNode *n){

}

void Tree::TreeNode::delete_6(TreeNode *n){

}

void Tree::TreeNode::replaces(TreeNode* child){

}

void Tree::TreeNode::delete_one(TreeNode* bl){

}

Tree::TreeNode *Tree::TreeNode::remove(Tree::TreeNode *p, int n){
    if (!p) {
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