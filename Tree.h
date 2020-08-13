#pragma once

#ifndef TREES_TREE_H
#define TREES_TREE_H

//using namespace std;

class Tree {
    class AvlNode;

    class RbNode;

    class TreeNode;

    class TreePrinter;

    TreeNode *root;

    TreePrinter *tp;

    std::string type;
public:
    Tree();

    Tree(std::string input);

    ~Tree();

    Tree(int n);

    Tree(int N, int *arr);

    void print(int tt);

    void add(int n);

    void remove(int n);

    TreeNode *remove(TreeNode *q, int n);

    bool find(int n);

    void balance();

    void rand(int n);

};

class Tree::TreePrinter {

public:
    struct Trunk;

    virtual void showTrunks(Trunk *p);

    virtual void printTree(int tt, TreeNode *t, Trunk *prev, bool isR);
};

class Tree::TreeNode {
protected:
    int key;
    TreeNode *L;
    TreeNode *R;
    TreeNode *P;

    friend class AvlNode;

    friend class RbNode;

    friend class Tree;

public:
    TreeNode();

    TreeNode(int n);

    ~TreeNode();

    virtual TreeNode *add(TreeNode *q, int n);

    virtual TreeNode* find(int n);

    virtual TreeNode *maxNode(TreeNode *root); // нафег не надо

    virtual TreeNode *minNode(TreeNode *root);

    virtual TreeNode *rightRotate(TreeNode *q);

    virtual TreeNode *leftRotate(TreeNode *q);

    virtual void rightRotate();

    virtual void leftRotate();

    virtual int bfactor();

    virtual void fixHeight();

    virtual int height();

    virtual int height(TreeNode *q);

    virtual TreeNode *balance();

    virtual TreeNode *findMin(TreeNode *p);

    virtual TreeNode *removeMin(TreeNode *p);

    friend TreeNode *Tree::remove(TreeNode *q, int n);

    friend void Tree::TreePrinter::printTree(int tt, TreeNode *t, Tree::TreePrinter::Trunk *prev, bool isR);

    virtual int getColor();

    virtual void fixAdd(TreeNode *q);

    virtual TreeNode *getUncle();

    virtual TreeNode *getGrand();

    virtual void setColor(int i);

    virtual void setParent(TreeNode *par);

    virtual TreeNode *getSibling();

    virtual void delete_1(TreeNode *n);

    virtual void delete_2(TreeNode *n);

    virtual void delete_3(TreeNode *n);

    virtual void delete_4(TreeNode *n);

    virtual void delete_5(TreeNode *n);

    virtual void delete_6(TreeNode *n);

    virtual void delete_one(TreeNode *bl);

    virtual void replaces(TreeNode *child);

    virtual TreeNode *remove(TreeNode *t, int input);

    Tree::TreeNode* operator +(int input){
        return this->add(this, input);
    }

    Tree::TreeNode* operator -(int input){
        return this->remove(this, input);
    }
};

class Tree::AvlNode : public TreeNode {
protected:
    int level;
public:
    AvlNode();

    AvlNode(int n);

    ~AvlNode();

    TreeNode *add(TreeNode *q, int n);

    TreeNode *remove(TreeNode *p, int n);

    TreeNode *balance();

    int height();

    int height(TreeNode *q);

    int bfactor();

    void fixHeight();

    TreeNode* find(int n);

    TreeNode *findMin(TreeNode *p);

    TreeNode *removeMin(TreeNode *p);

    TreeNode *rightRotate(TreeNode *q);

    TreeNode *leftRotate(TreeNode *q);
};

class Tree::RbNode : public TreeNode {
protected:
    //TreeNode *parent;

    int color;
public:
    RbNode();

    RbNode(int n);

    RbNode(TreeNode *par, int n);

    ~RbNode();

    int getColor();

    TreeNode *add(TreeNode *q, int n);

    void fixAdd(TreeNode *q);

    void rightRotate();

    void leftRotate();

    TreeNode *getUncle();

    TreeNode *getGrand();

    void setColor(int i);

    void setParent(TreeNode *par);

    TreeNode *getParent(TreeNode *q);

    void InsertRecurse(TreeNode *rot, TreeNode *n);

    void InsertRepairTree(TreeNode *n);

    void insert_case1(TreeNode *n);

    void insert_case2(TreeNode *n);

    void insert_case3(TreeNode *n);

    void insert_case4(TreeNode *n);

    void insert_case5(TreeNode *n);

    TreeNode *getSibling();

    TreeNode *findMin(TreeNode *p);

    void ReplaceNode(TreeNode *n);

    void delete_1(TreeNode *n);

    void delete_2(TreeNode *n);

    void delete_3(TreeNode *n);

    void delete_4(TreeNode *n);

    void delete_5(TreeNode *n);

    void delete_6(TreeNode *n);

    void replaces(TreeNode *child);

    void delete_one(TreeNode *bl);

    TreeNode *remove(TreeNode *t, int input);

    TreeNode* find(int n);
};

#endif //TREES_TREE_H
