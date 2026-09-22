//
// Created by jakea on 9/18/2026.
//

#ifndef UNTITLED1_AVL_H
#define UNTITLED1_AVL_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;


class AVLTree {
public:
    string insert(const string& name, int id);
    string removeId(int id);
    string searchId(int id);
    string searchName(const string& name);
    vector<string> printInorder();
    vector<string> printPreorder();
    vector<string> printPostorder();
    int printLevelCount();
    int removeInorder(const string& level);

private:
    struct Node{
        int val;
        Node* left;
        Node* right;
        int height;
    };
    Node* root = nullptr;
    AVLTree::Node* AVLTree::helperInsert(Node* helpRoot, const string& name, int id);
    AVLTree::Node* AVLTree::helperRemove(Node* helpRoot, int id);
    void helperInorder(Node* helpRoot);
    AVLTree::Node* helperSearch(Node* helpRoot, int id);
};

void AVLTree::helperInorder(Node* helpRoot) {
    if (helpRoot == nullptr) {
        cout << "";
    }else {
        helperInorder(helpRoot->left);
        cout << helpRoot->val << " ";
        helperInorder(helpRoot->right);
    }
};

AVLTree::Node* AVLTree::helperInsert(Node* helpRoot, const string& name, int id) {
    if (helpRoot == nullptr) {
        return new Node{name, id, nullptr, nullptr, 0};
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
#endif //UNTITLED1_AVL_H
