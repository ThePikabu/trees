#include <iostream>
#include "Tree.h"

#define RED 1
#define BLACK 0

Tree::RbNode::RbNode() : TreeNode() {
    color = RED;
    P = nullptr;
}

Tree::RbNode::RbNode(int n) : TreeNode(n) {
    color = RED;
    P = nullptr;
}

Tree::RbNode::RbNode(TreeNode *par, int n) {
    key = n;
    color = RED;
    L = R = nullptr;
    P = par;
}

int Tree::RbNode::getColor() {
    return color;
}

void Tree::RbNode::setColor(int i) {
    color = i;
}

void Tree::RbNode::setParent(TreeNode *par) {
    P = par;
}

Tree::TreeNode *Tree::RbNode::getGrand() {
    if (P != nullptr) {
        return P->P;
    } else {
        return nullptr;
    }
}

Tree::TreeNode *Tree::RbNode::getUncle() {
    TreeNode *p = getGrand();
    if (p == nullptr) {
        return nullptr;
    }
    if (P == p->L) {
        return p->R;
    } else {
        return p->L;
    }
}

void Tree::RbNode::rightRotate() {
    TreeNode *tmp = L;
    tmp->P = P;
    if (P != nullptr) {
        if (P->L == this) {
            P->L = tmp;
        } else {
            P->R = tmp;
        }
    }

    L = tmp->R;
    if (tmp->R != nullptr) {
        tmp->R->P = this;
    }

    P = tmp;
    tmp->R = this;
}

void Tree::RbNode::leftRotate() {
    TreeNode *tmp = R;
    tmp->P = P;
    if (P != nullptr) {
        if (P->L == this) {
            P->L = tmp;
        } else {
            P->R = tmp;
        }
    }

    R = tmp->L;
    if (tmp->L != nullptr) {
        tmp->L->P = this;
    }

    P = tmp;
    tmp->L = this;
}

void Tree::RbNode::InsertRepairTree(TreeNode *n) {
    if (n->P == nullptr) {
        insert_case1(n);
    } else if (n->P->getColor() == BLACK) {
        insert_case2(n);
    } else if (n->getUncle() != nullptr && n->getUncle()->getColor() == RED) {
        insert_case3(n);
    } else {
        insert_case4(n);
    }
}

void Tree::RbNode::insert_case1(TreeNode *n) {
    n->setColor(BLACK);
}

void Tree::RbNode::insert_case2(TreeNode *n) {
    return;
}

void Tree::RbNode::insert_case3(TreeNode *n) {
    n->P->setColor(BLACK);
    n->getUncle()->setColor(BLACK);
    n->getGrand()->setColor(RED);
    InsertRepairTree(n->getGrand());
}

void Tree::RbNode::insert_case4(TreeNode *n) {
    TreeNode *p = n->P;
    TreeNode *g = n->getGrand();

    if (n == p->R && p == g->L) {
        p->leftRotate();
        n = n->L;
    } else if (n == p->L && p == g->R) {
        p->rightRotate();
        n = n->R;
    }

    insert_case5(n);
}

void Tree::RbNode::insert_case5(TreeNode *n) {
    TreeNode *p = n->P;
    TreeNode *g = n->getGrand();

    if (n == p->L) {
        g->rightRotate();
    } else {
        g->leftRotate();
    }
    p->setColor(BLACK);
    g->setColor(RED);
}

void Tree::RbNode::fixAdd(TreeNode *n) {
    insert_case1(n);
}

void Tree::RbNode::InsertRecurse(TreeNode *rot, TreeNode *n) {
    // Recursively descend the tree until a leaf is found.
    if (rot != nullptr && n->key < rot->key) {
        if (rot->L != nullptr) {
            InsertRecurse(rot->L, n);
            return;
        } else {
            rot->L = n;
        }
    } else if (rot != nullptr) {
        if (rot->R != nullptr) {
            InsertRecurse(rot->R, n);
            return;
        } else {
            rot->R = n;
        }
    }

    n->P = rot;
    n->L = nullptr;
    n->R = nullptr;
    n->setColor(RED);
}

Tree::TreeNode *Tree::RbNode::add(TreeNode *rot, int n) {
    if (key == 0) {
        key = n;
        color = BLACK;
        return this;
    } else {
        TreeNode *node = new RbNode(n);

        InsertRecurse(rot, node);

        InsertRepairTree(node);

        rot = node;

        while (rot->P != nullptr) {
            rot = rot->P;
        }
        return rot;
    }
}

Tree::TreeNode *Tree::RbNode::findMin(Tree::TreeNode *p) {
    return p->L ? p->L->findMin(p->L) : p;
}

void Tree::RbNode::ReplaceNode(TreeNode *n) {
    TreeNode *child = findMin(n);
    child->P = n->P;
    if (n == n->P->L) {
        n->P->L = child;
    } else {
        n->P->R = child;
    }
}

Tree::TreeNode *Tree::RbNode::getSibling() {
    if (this == P->L) {
        return P->R;
    } else {
        return P->L;
    }
}

void Tree::RbNode::delete_1(TreeNode *bl) {
    if (P != nullptr) {
        delete_2(bl);
    }
}

void Tree::RbNode::delete_2(TreeNode *bl) {
    TreeNode *s = bl->getSibling();
    if (s && s->getColor() == RED) {
        P->setColor(RED);
        s->setColor(BLACK);
        if (this == P->L) {
            P->leftRotate();
        } else {
            P->rightRotate();
        }
    }
    delete_3(bl);
}

void Tree::RbNode::delete_3(TreeNode *bl) {
    TreeNode *s = bl->getSibling();
    if (s && P->getColor() == BLACK && s->getColor() == BLACK && s->L && s->R &&
        s->L->getColor() == BLACK && s->R->getColor() == BLACK) {
        s->setColor(RED);
        P->delete_1(P);
    } else {
        delete_4(bl);
    }
}

void Tree::RbNode::delete_4(TreeNode *bl) {
    TreeNode *s = getSibling();
    if (s && s->L && s->R && P->getColor() == BLACK && s->getColor() == BLACK &&
        s->L->getColor() == BLACK && s->R->getColor() == BLACK) {
        s->setColor(RED);
        P->setColor(BLACK);
    } else {
        delete_5(bl);
    }
}

void Tree::RbNode::delete_5(TreeNode *bl) {
    TreeNode *s = bl->getSibling();
    if (s && s->getColor() == BLACK) {
        if (this == P->L && s->R && s->R->getColor() == BLACK &&
            s->L->getColor() == RED) {
            s->setColor(RED);
            s->L->setColor(BLACK);
            s->rightRotate();
        } else if (this == P->R && s->L && s->L->getColor() == BLACK &&
                   s->R->getColor() == RED) {
            s->setColor(RED);
            s->R->setColor(BLACK);
            s->leftRotate();
        }
    }
    delete_6(bl);
}

void Tree::RbNode::delete_6(TreeNode *bl) {
    TreeNode *s = bl->getSibling();
    int c = P->getColor();
    if (s) {
        s->setColor(c);
        P->setColor(BLACK);
    }
    if (s && this == P->L) {
        if (s->R) s->R->setColor(BLACK);
        P->leftRotate();
    } else if (s && s->L) {
        s->L->setColor(BLACK);
        P->rightRotate();
    }
}

void Tree::RbNode::replaces(TreeNode *child) {
    child->P = P;
    if (this == P->L) {
        P->L = child;
    } else {
        P->R = child;
    }
}

void Tree::RbNode::delete_one(TreeNode *bl) {
    TreeNode *child = (bl->R) ? bl->L : bl->R;
    if (!child) {
        bl->delete_1(bl);
    } else {
        bl->replaces(child);
        if (bl->getColor() == BLACK) {
            if (child->getColor() == RED) {
                child->setColor(BLACK);
            } else {
                child->delete_1(child);
            }
        }
    }
    delete (bl);
}

Tree::TreeNode *Tree::RbNode::find(int n) {
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

Tree::TreeNode *Tree::RbNode::remove(TreeNode *t, int input) {
    TreeNode *finder = t->find(input);
    if (finder == nullptr) {
        std::cout << "Not found" << std::endl;
        return t;
    }
    TreeNode *g = finder->findMin(finder);
    int memory = g->key;
    g->key = finder->key;
    finder->key = memory;
    g->delete_one(g);
    if (t->P != nullptr) return t->P;
    else return t;
}
