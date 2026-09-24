//Jake Amaral
//ufid: 41389037

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "AVL.h"
#include <vector>
#include <random>
#include <string>
#include <algorithm>

using namespace std;

TEST_CASE("Bad commands fail", "[invalid]"){
    AVLTree tree;
    REQUIRE(tree.insert("J8ke", 41389037) == "unsuccessful");
    REQUIRE(tree.insert("Jake", 4138903) == "unsuccessful");
    REQUIRE(tree.insert("J8ke", 4138903) == "unsuccessful");
    REQUIRE(tree.insert("Jake", 413890370) == "unsuccessful");
    REQUIRE(tree.insert("Jake", 41907) == "unsuccessful");
    REQUIRE(tree.remove(42389037) == "unsuccessful");
}

TEST_CASE("Rotations test", "[rotations]"){
    AVLTree tree;

    SECTION("right rotation (LL)") {
        tree.insert("Jake", 11111113);
        tree.insert("Nate", 11111112);
        tree.insert("Yanta", 11111111);
        vector<string> expected = {"Nate", "Yanta", "Jake"};
        REQUIRE(tree.printPreorder() == expected);
    }
    SECTION("left rotation (RR)") {
        tree.insert("Jake", 11111111);
        tree.insert("Nate", 11111112);
        tree.insert("Yanta", 11111113);
        vector<string> expected = {"Nate", "Jake", "Yanta"};
        REQUIRE(tree.printPreorder() == expected);
    }
    SECTION("double rotation (LR)") {
        tree.insert("Jake", 11111113);
        tree.insert("Nate", 11111111);
        tree.insert("Yanta", 11111112);
        vector<string> expected = {"Yanta", "Nate", "Jake"};
        REQUIRE(tree.printPreorder() == expected);
    }
    SECTION("double rotation (RL)") {
        tree.insert("Jake", 11111111);
        tree.insert("Nate", 11111113);
        tree.insert("Yanta", 11111112);
        vector<string> expected = {"Yanta", "Jake", "Nate"};
        REQUIRE(tree.printPreorder() == expected);
    }
    SECTION("already balanced") {
        tree.insert("Jake", 11111112);
        tree.insert("Nate", 11111113);
        tree.insert("Yanta", 11111111);
        vector<string> expected = {"Jake", "Yanta", "Nate"};
        REQUIRE(tree.printPreorder() == expected);
    }
}

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!

TEST_CASE("Insert/Remove/Check Inorder", "[large]"){
    AVLTree tree;
    vector<int> expected;
    while (expected.size() < 100) {
        int id = 10000000 + rand() % 90000000;
        if (count(expected.begin(), expected.end(), id) == 0) {
            expected.push_back(id);
            tree.insert("Student", id);
        }
    }
    sort(expected.begin(), expected.end());
    REQUIRE(tree.inorderId() == expected);
    for (int i = 0; i < 10; i++){
        int index = rand() % expected.size();
        tree.remove(expected[index]);
        expected.erase(expected.begin() + index);
    }
    REQUIRE(tree.inorderId().size() == 90);
    REQUIRE(tree.inorderId() == expected);
}
