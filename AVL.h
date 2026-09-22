//
// Created by jakea on 9/18/2026.
//

#ifndef UNTITLED1_AVL_H
#define UNTITLED1_AVL_H
#include <string>
#include <vector>
using namespace std;


class AVLTree {
public:
    string insert(const string& name, const string& id);
    string removeId(const string& id);
    string searchId(const string& id);
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
    AVLTree::Node* helperInsert(Node* helpRoot, int key);
    void helperInorder(Node* helpRoot);
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

AVLTree::Node* AVLTree::helperInsert(Node* helpRoot, int key) {
    if (helpRoot == nullptr) {
        return new Node(key);
    }
    if (key < helpRoot->val) {
        helpRoot->left = helperInsert(helpRoot->left, key);
    }else {
        helpRoot->right = helperInsert(helpRoot->right, key);
    }
    return helpRoot;
};



#endif //UNTITLED1_AVL_H