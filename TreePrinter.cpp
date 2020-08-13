#include <iostream>
#include "Tree.h"

using namespace std;


struct Tree::TreePrinter::Trunk {
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

void Tree::TreePrinter::showTrunks(Trunk *p) {
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

void Tree::TreePrinter::printTree(int tt, TreeNode *root, Trunk *prev, bool isR) {
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(tt, root->R, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isR) {
        trunk->str = ".---";
        prev_str = "   |";
    } else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    if (tt == 1) {
        cout << (char) (root->key + '0') << endl;
    } else
        cout << root->key << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(tt, root->L, trunk, false);
}


