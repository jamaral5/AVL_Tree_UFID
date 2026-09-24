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

    string remove(int id);

    string searchId(int id);

    string searchName(const string& name);

    string removeInorder(int n);

    vector<string> printInorder();

    vector<string> printPreorder();

    vector<string> printPostorder();

    vector<int> inorderId();

    int printLevelCount();

private:
    struct Node{

        int val;

        Node* left;

        Node* right;

        int height;

        string name;
    };
    Node* root = nullptr;

    Node* helperInsert(Node* helpRoot, const string& name, int id);

    Node* helperRemove(Node* helpRoot, int id);

    Node* helperSearch(Node* helpRoot, int id);

    Node* rotateLeft(Node* n);

    Node* rotateRight(Node* n);

    void helperInorder(Node* helpRoot, vector<string>& final);

    void helperPreorder(Node* helpRoot, vector<string>& final);

    void helperPostorder(Node* helpRoot, vector<string>& final);

    void helperInordersort(Node* helpRoot, vector<int>& vals);

    void helperSearchname(Node* helpRoot, string name, vector<string>& vals);

    int helperMax(Node* helpRoot);

    int getHeight(Node* n);

    int getBF(Node* n);
};

#endif //UNTITLED1_AVL_H
