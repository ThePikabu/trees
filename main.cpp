#include <iostream>
#include <exception>
#include <sstream>
#include <string>
#include "Tree.h"

#define min 1
#define max 256

using namespace std;

int tt = 0;

int getc(istringstream &iss) {
    char x;
    iss >> x;
    tt = 1;
    return (int) (x - '0');
}

int getn(istringstream &iss) {
    int x;
    iss >> x;
    tt = 2;
    return x;
}

int (*f)(istringstream &iss);

void welcome();

void help();

void manage(Tree *t);

int getRandomNumber();

int main() {
    srand(static_cast<unsigned int>(time(0)));

    string input;
    welcome();
    cin >> input;
    Tree *t = new Tree(input);
    cout << "Please choose type of your tree data: int or char" << endl;
    cin >> input;
    if (input == "char") {
        f = getc;
    } else if (input == "int") {
        f = getn;
    } else {
        cout << "ERROR. You didn't choose type of data" << endl;
        return -1;
    }
    help();

    /*t->add(27);
    t->add(12);
    t->add(8);
    t->add(17);
    t->add(35);
    t->add(29);
    t->add(41);
    t->print();*/

    manage(t);

    return 0;
}

void welcome() {
    cout << "Welcome to Tree Manager!" << endl;
    cout << "Write AVL or RB to get tree you are looking for (or anything else to get default binary tree)" << endl;
    //help();
}

void help() {
    cout << "+ to add number n in tree" << endl;
    cout << "- to remove number n from tree" << endl;
    cout << "? to tree contains number n?" << endl;
    cout << "r to add n random numbers in range of 1 to 256 to tree" << endl;
    cout << "p to print tree" << endl;
    cout << "h fot help" << endl;
    cout << "e to exit" << endl;
}

int getRandomNumber() {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void manage(Tree *t) {
    string com;
    char command = 'z';
    int n;
    if (t == nullptr) {
        t = new Tree();
    }
    getline(cin, com);
    do {
        getline(cin, com);
        istringstream iss(com);

        iss >> command;
        switch (command) {
            case 'e':
                break;
            case '+':
                /*cin >> n;*/
                if (com.length() == 1) {
                    cout << "Wrong command, try again" << endl;
                    break;
                }
                n = f(iss);
                t->add(n);
                break;
            case '-':
                /*cin >> n;*/
                if (com.length() == 1) {
                    cout << "Wrong command, try again" << endl;
                    break;
                }
                n = f(iss);
                t->remove(n);
                break;
            case '?':
                /*cin >> n;*/
                if (com.length() == 1) {
                    cout << "Wrong command, try again" << endl;
                    break;
                }
                n = f(iss);
                cout << t->find(n) << endl;
                break;
            case 'p':
                t->print(tt);
                break;
            case 'h':
                help();
            case 'r':
                if (tt == 1) {
                    cout << "Not working, sore" << endl;
                    break;
                }
                if (com.length() == 1) {
                    cout << "Wrong command, try again" << endl;
                    break;
                }
                cin >> n;
                for (int i = 0; i < n; ++i)
                    t->add(getRandomNumber());
                break;
            default:
                cout << "Wrong command, try again" << endl;
                break;
        }
    } while (command != 'e');
}