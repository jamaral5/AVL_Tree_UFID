//
// Created by jakea on 9/18/2026.
//

#include "AVL.h"
#include <vector>

//HELP FUNCTIONS

void AVLTree::helperPreorder(Node* helpRoot) {
    if (helpRoot == nullptr) {
        return;
    }
    cout << helpRoot->val << " ";
    helperPreorder(helpRoot->left);
    helperPreorder(helpRoot->right);
};

void AVLTree::helperPostorder(Node* helpRoot) {
    if (helpRoot == nullptr) {
        return;
    }
    helperPostorder(helpRoot->left);
    helperPostorder(helpRoot->right);
    cout << helpRoot->val << " ";
};


void AVLTree::helperInorder(Node* helpRoot) {
    if (helpRoot == nullptr) {
        return;
    }
    helperInorder(helpRoot->left);
    cout << helpRoot->val << " ";
    helperInorder(helpRoot->right);
};

void AVLTree::helperInordersort(Node* helpRoot, vector<int>& vals) {
    if (helpRoot == nullptr) {
        return;
    }
    helperInordersort(helpRoot->left, vals);
    vals.push_back(helpRoot->val);
    helperInordersort(helpRoot->right, vals);

};

AVLTree::Node* AVLTree::helperInsert(Node* helpRoot, const string& name, int id) {
    if (helpRoot == nullptr) {
        return new Node{id, nullptr, nullptr, 0, name};
    }
    if (id < helpRoot->val) {
        helpRoot->left = helperInsert(helpRoot->left, name, id);
    }else {
        helpRoot->right = helperInsert(helpRoot->right, name, id);
    }
    return helpRoot;
};

AVLTree::Node* AVLTree::helperSearch(Node* helpRoot, int id) {
    if (helpRoot == nullptr) {
        return nullptr;
    }
    if (id < helpRoot->val) {
        return helperSearch(helpRoot->left, id);
    }
    if (id > helpRoot->val) {
        return helperSearch(helpRoot->right, id);
    }
    return helpRoot;
};

void AVLTree::helperSearchname(Node* helpRoot, string name, vector<string>& vals) {
    if (helpRoot == nullptr) {
        return;
    }
    helperSearchname(helpRoot->left, name, vals);
    if (helpRoot->name == name) {
        vals.push_back(to_string(helpRoot->val));
    }
    helperSearchname(helpRoot->right, name, vals);
};

int AVLTree::helperMax(Node* helpRoot) {
    if (helpRoot == nullptr) {
        return 0;
    }
    return max(helperMax(helpRoot->left), helperMax(helpRoot->right));
};

AVLTree::Node* AVLTree::helperRemove(Node* helpRoot, int id) {
    if (helpRoot == nullptr) {
        return nullptr;
    }
    if (id < helpRoot->val) {
        helpRoot->left = helperRemove(helpRoot->left, id);
        return helpRoot;
    }
    if (id > helpRoot->val) {
        helpRoot->right = helperRemove(helpRoot->right, id);
        return helpRoot;
    }
    if (id == helpRoot->val) {
        if (helpRoot->left == nullptr && helpRoot->right == nullptr) {
            delete helpRoot;
            return nullptr;
        }else if(helpRoot->left == nullptr) {
            Node* temp = helpRoot->right;
            delete helpRoot->right;
            return temp;
        }else if(helpRoot->right == nullptr) {
           Node* temp = helpRoot->left;
            delete helpRoot;
            return temp;
        }
    }
    while (helpRoot->right->left != nullptr) {
        helpRoot->right = helpRoot->right->left;
    }
    helpRoot->val = helpRoot->right->val;
    helpRoot->name = helpRoot->right->name;
    helpRoot->right = helperRemove(helpRoot->right, helpRoot->right->val);
    return helpRoot;
};

//BEGIN REAL FUNCTIONS

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

