//
// Created by jakea on 9/18/2026.
//

#include "AVL.h"
#include <vector>

//HELP FUNCTIONS
int AVLTree::getHeight(Node* n) {
    if (n == nullptr) {
        return 0;
    }
    return n->height;
};

int AVLTree::getBF(Node* n) {
    if (n == nullptr) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
};

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
};

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
};

void AVLTree::helperPreorder(Node* helpRoot, vector<string>& final) {
    if (helpRoot == nullptr) {
        return;
    }
    final.push_back(helpRoot->name);
    helperPreorder(helpRoot->left, final);
    helperPreorder(helpRoot->right, final);
};

void AVLTree::helperPostorder(Node* helpRoot, vector<string>& final) {
    if (helpRoot == nullptr) {
        return;
    }
    helperPostorder(helpRoot->left, final);
    helperPostorder(helpRoot->right, final);
    final.push_back(helpRoot->name);
};


void AVLTree::helperInorder(Node* helpRoot, vector<string>& final) {
    if (helpRoot == nullptr) {
        return;
    }
    helperInorder(helpRoot->left, final);
    final.push_back(helpRoot->name);
    helperInorder(helpRoot->right, final);
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
        return new Node{id, nullptr, nullptr, 1, name};
    }
    if (id < helpRoot->val) {
        helpRoot->left = helperInsert(helpRoot->left, name, id);
    }
    if (id > helpRoot-> val){
        helpRoot->right = helperInsert(helpRoot->right, name, id);
    }
    helpRoot->height = 1 + max(getHeight(helpRoot->left), getHeight(helpRoot->right));
    if (getBF(helpRoot) > 1 && id < helpRoot->left->val) {
        return rotateRight(helpRoot);
    }
    if (getBF(helpRoot) < -1 && id > helpRoot->right->val) {
        return rotateLeft(helpRoot);
    }
    if (getBF(helpRoot) > 1 && id > helpRoot->left->val) {
        helpRoot->left = rotateLeft(helpRoot->left);
        return rotateRight(helpRoot);
    }
    if (getBF(helpRoot) < -1 && id < helpRoot->right->val) {
        helpRoot->right = rotateRight(helpRoot->right);
        return rotateLeft(helpRoot);
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
    return 1 + max(helperMax(helpRoot->left), helperMax(helpRoot->right));
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
            delete helpRoot;
            return temp;
        }else if(helpRoot->right == nullptr) {
           Node* temp = helpRoot->left;
            delete helpRoot;
            return temp;
        }
    }
    Node* after = helpRoot->right;
    while (after->left != nullptr) {
        after = after->left;
    }
    helpRoot->val = after->val;
    helpRoot->name = after->name;
    helpRoot->right = helperRemove(helpRoot->right, after->val);
    return helpRoot;
};

//BEGIN REAL FUNCTIONS

string AVLTree::insert(const string& name, int id) {
    if (name.empty()) {
        return "unsuccessful";
    }
    for (char c : name) {
        bool lowercase = (c>='a' && c<='z');
        bool uppercase = (c>='A' && c<='Z');
        bool space = (c==' ');
        if (!lowercase && !uppercase && !space) {
            return "unsuccessful";
        }
    }
    if (id < 10000000 || id > 99999999) {
        return "unsuccessful";
    }
    if (helperSearch(root, id) != nullptr) {
        return "unsuccessful";

    }
    root = helperInsert(root, name, id);
    return "successful";
};

string AVLTree::remove(int id) {
    if (helperSearch(root, id) == nullptr) {
        return "unsuccessful";
    }
    root = helperRemove(root, id);
    return "successful";
};
string AVLTree::searchId(int id) {
    if (helperSearch(root, id) == nullptr) {
        return "unsuccessful";
    }
    return helperSearch(root, id)->name;
};

string AVLTree::searchName(const string& name) {
    vector<string> vals;
    helperSearchname(root, name, vals);
    if (vals.empty()) {
        return "unsuccessful";
    }
    string final;
    for (int i = 0; i < (int)vals.size(); i++) {
        final += vals[i];
        final += "\n";
    }
    return final;
};

vector<string> AVLTree::printInorder() {
    vector<string> final;
    helperInorder(root, final);
    return final;
};

vector<string> AVLTree::printPreorder() {
    vector<string> final;
    helperPreorder(root, final);
    return final;
};

vector<string> AVLTree::printPostorder() {
    vector<string> final;
    helperPostorder(root, final);
    return final;
};

vector<int> AVLTree::inorderId() {
    vector<int> vals;
    helperInordersort(root, vals);
    return vals;
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
    if (n >= (int)vals.size()) {
        return "unsuccessful";
    }
    root = helperRemove(root, vals[n]);
    return "successful";
};


