#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<list>
#include <utility> 
#include <algorithm>
#include <sstream>
using namespace std;



class Node{
public:
    int weight;
    char c;
    int height;
    Node* left;
    Node* right;
    
    friend class HuffTree_AVL;
public:
    Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr): height(1), weight(weight), c(c), left(left), right(right) {}
};

std::string huffmanTreeToString(const Node* tree) ;




//********* CODE ********************************************************************

//TODO: điền code vào chú ý sau newNode = balanceTree(newNode, count); thêm dòng bên dưới in ra
//* cout << "output_you = " << huffmanTreeToString(newNode) << "\n";
//* gửi phần vector<pair<char, int>> qua anh để anh chạy rồi bug cho dễ


//*********** code bên dưới không bận tâm ***************************
int main()
{
    //TODO nhập vector sai vào 
    vector<pair<char, int>> v = {{'l',9},{'w',4},{'q',4},{'p',4},{'x',3},{'m',3},{'k',3},{'g',3},{'z',2},{'r',2},{'i',2},{'a',2},{'v',1},{'u',1},{'s',1},{'f',1},{'d',1},{'c',1},{'b',1}};
    
    //TODO test
    Node* result = buildHuff(v);
    cout << "output_you = " << huffmanTreeToString(result) << "\n";
    return 1;
}

std::string huffmanTreeToString(const Node* tree) {
    std::stringstream ss;

    if (tree == nullptr) {
        return "";
    }

    if (tree->c) {
        ss << "[" << tree->weight << "," << tree->c << "]";
    } else {
        ss << "[" << tree->weight << "]";
    }

    if (tree->left != nullptr || tree->right != nullptr) {
        ss << "(";
        ss << huffmanTreeToString(tree->left);
        ss << ",";
        ss << huffmanTreeToString(tree->right);
        ss << ")";
    }

    return ss.str();
}
