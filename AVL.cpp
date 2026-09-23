//
// Created by jakea on 9/18/2026.
//

#include "AVL.h"
#include <vector>

string AVLTree::insert(const string& name, int id) {
    if (helperSearch(root, id) == nullptr) {
        return "unsuccessful";
    }
    helperInsert(root, name, id);
    return "successful";
};
string AVLTree::remove(int id) {
    if (helperSearch(root, id) == nullptr) {
        return "unsuccessful";
    }
    helperRemove(root, id);
    return "successful";
};
string AVLTree::searchId(int id) {
    if (helperSearch(root, id) == nullptr) {
        return "unsuccessful";
    }
    helperSearch(root, id);
    return "successful";
};

string AVLTree::searchName(const string& name) {
    vector<string> vals;
    string final;
    helperSearchname(root, name, vals);
    if (vals.empty()) {
        return "unsuccesful";
    }
    for (int i = 0; i < (int)vals.size(); i++) {
        final += vals[i];
        final += "\n";
    }
    return "successful";
};

void AVLTree::printInorder() {
    helperInorder(root);
};

void AVLTree::printPreorder() {
    helperPreorder(root);
};

void AVLTree::printPostorder() {
    helperPostorder(root);
};

int AVLTree::printLevelCount() {
    return helperMax(root);
};

string AVLTree::removeInorder(int n) {
    vector<int> vals;
    helperInordersort(root, vals);
    if (n < 0) {
        return "unsuccessful";
    }
    if (n > (int)vals.size()) {
        return "unsuccessful";
    }
    helperRemove(root, vals[n]);
    return "successful";
};

