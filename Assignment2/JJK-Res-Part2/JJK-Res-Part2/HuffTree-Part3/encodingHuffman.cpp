#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

class Node
{
public:
    int weight;
    char c;
    int height;
    Node *left;
    Node *right;
    friend class HuffTree_AVL;

public:
    Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : height(1), weight(weight), c(c), left(left), right(right) {}
    bool isChar() const { return c != '\0'; }
};

//* TIẾN HÀNH đệ quy để lấy ra ra kết quả encoding
//^ chú ý: cứ node bên trái thì mã hóa là '0', node bên phải mã hóa là '1'.
void encodingHuffman_rec(vector<string> &encoding, Node *node, string s = "")
{
    // TODO
    if (node->left == nullptr && node->right == nullptr)
    {
        encoding[node->c] = s;
        return;
    }

    encodingHuffman_rec(encoding, node->left, s += '0');

    s = s.erase(s.size() - 1);
    encodingHuffman_rec(encoding, node->right, s += '1');
}
//* đầu vào là 1 cây và name đã được mã hóa Caesar -> đầu ra là result kết quả cần tìm.
int encodingHuffman(Node *root, string nameCaesar)
{
    if (root->left == nullptr && root->right == nullptr)
        return 0;

    //* bước 1: lấy chuỗi kết quả của các kí tự đã mã hóa
    //* ví dụ cây 2('a', 'b') ta lưu encoding['a'] = '0' và encoding['b'] = '1'
    vector<string> encoding(256, "");
    encodingHuffman_rec(encoding, root);

    //* bước 2 lấy ra 10 kí tự nhị phân cuối sau khi mã hóa nameCaesar thành mã nhị phân lấy từ phải đên trái
    //! VD : 00000000000000000001 -> kq: 10000000000
    //^ chú ý: đừng có mà giải mã hết nameCaesar -> giải mã khi nào đủ 10 kí tự nhị phân là dừng
    // TODO
    //* nameCaesar = "aab"; => 001
    string encod;
    for (int i = nameCaesar.size(); i >= 0; i--)
    {
        encod = encoding[nameCaesar[i]] + encod;

        if (encod.length() > 10)
        {
            break;
        }
    }
    if (encod.length() > 10)
    {
        int lenCut = 10;
        int startIndex = encod.length() - lenCut;
        encod = encod.substr(startIndex, lenCut);
    }
    reverse(encod.begin(), encod.end());

    //* bước 3 mã hóa binary sang thập phân -> này ez rồi
    int result = 0;
    // TODO
    if (!(root->left == nullptr && root->right == nullptr))
    {
        result = std::stoi(encod, nullptr, 2);
    }

    //* kiểm tra test thôi nếu bạn thầy mình bị sai
    // cout << "nameCaesar = " << nameCaesar << endl;
    // cout << "encoding : ";
    // for (int i = 0; i < encoding.size(); i++)
    // {
    //     if (encoding[i] != "")
    //         cout << char(i) << "=" << encoding[i] << " - ";
    // }
    // cout << "\nbinary = " << encod << endl;
    // cout << "result = " << result << endl;
    //********************

    return result;
}

int main()
{
    //* test 1
    {
        Node *root = new Node(4, '\0',
                              new Node(1, 'a'),
                              new Node(1, 'b'));
        string nameCaesar = "aab";

        reverse(nameCaesar.begin(), nameCaesar.end());

        int result = 1;
        int output_you = encodingHuffman(root, nameCaesar);
        if (result != output_you)
        {
            cout << "fail test 1 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else
            cout << "pass test 1 \n";
    }

    // //* test 2
    {
        Node *root = new Node(4, '\0',
                              new Node(1, 'a'),
                              new Node(1, 'b'));
        string nameCaesar = "baa";
        reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 4;
        int output_you = encodingHuffman(root, nameCaesar);
        if (result != output_you)
        {
            cout << "fail test 2 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else
            cout << "pass test 2 \n";
    }

    //* test 3
    {
        Node *root = new Node(4, '\0',
                              new Node(1, 'a'),
                              new Node(1, 'b'));
        string nameCaesar = "baaaaaaaaba";
        reverse(nameCaesar.begin(), nameCaesar.end());
        int result = pow(2, 9) + 1;
        int output_you = encodingHuffman(root, nameCaesar);
        if (result != output_you)
        {
            cout << "fail test 3 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else
            cout << "pass test 3 \n";
    }

    // //* test 4
    {
        Node *root = new Node(4, '\0',
                              new Node(1, 'a'),
                              new Node(1, 'b'));
        string nameCaesar = "aaaaaaaaaab";
        reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 0;
        int output_you = encodingHuffman(root, nameCaesar);
        if (result != output_you)
        {
            cout << "fail test 4 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else
            cout << "pass test 4 \n";
    }

    // //* test 5
    {
        //! 4(7('d','c'), 14(2('a','b'), 'e'))
        //! 'd':00 'c':01 'a':100 'b':101 'e'11
        Node *root = new Node(4, '\0',
                              new Node(7, '\0',
                                       new Node(3, 'd'),
                                       new Node(2, 'c')),
                              new Node(14, '\0',
                                       new Node(2, '\0',
                                                new Node(1, 'a'),
                                                new Node(1, 'b')),
                                       new Node(10, 'e')));
        string nameCaesar = "e";
        reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 3;
        int output_you = encodingHuffman(root, nameCaesar);
        if (result != output_you)
        {
            cout << "fail test 5 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else
            cout << "pass test 5 \n";
    }

    //* test 6
    {
        //! 4(7('d','c'), 14(2('a','b'), 'e'))
        //! 'd':00 'c':01 'a':100 'b':101 'e'11
        Node *root = new Node(4, '\0',
                              new Node(7, '\0',
                                       new Node(3, 'd'),
                                       new Node(2, 'c')),
                              new Node(14, '\0',
                                       new Node(2, '\0',
                                                new Node(1, 'a'),
                                                new Node(1, 'b')),
                                       new Node(10, 'e')));
        string nameCaesar = "dddda";
        reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 0;
        int output_you = encodingHuffman(root, nameCaesar);
        if (result != output_you)
        {
            cout << "fail test 6 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else
            cout << "pass test 6 \n";
    }

    // //* test 7
    {
        //! 4(7('d','c'), 14(2('a','b'), 'e'))
        //! 'd':00 'c':01 'a':100 'b':101 'e'11
        Node *root = new Node(4, '\0',
                              new Node(7, '\0',
                                       new Node(3, 'd'),
                                       new Node(2, 'c')),
                              new Node(14, '\0',
                                       new Node(2, '\0',
                                                new Node(1, 'a'),
                                                new Node(1, 'b')),
                                       new Node(10, 'e')));
        string nameCaesar = "eeeea";
        reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 1020;
        int output_you = encodingHuffman(root, nameCaesar);
        if (result != output_you)
        {
            cout << "fail test 7 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else
            cout << "pass test 7 \n";
    }

    //* test 8
    {
        //! 4(7('d','c'), 14(2('a','b'), 'e'))
        //! 'd':00 'c':01 'a':100 'b':101 'e'11
        Node *root = new Node(4, '\0',
                              new Node(7, '\0',
                                       new Node(3, 'd'),
                                       new Node(2, 'c')),
                              new Node(14, '\0',
                                       new Node(2, '\0',
                                                new Node(1, 'a'),
                                                new Node(1, 'b')),
                                       new Node(10, 'e')));
        string nameCaesar = "eeeeec";
        reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 1023; //* 1111111111
        int output_you = encodingHuffman(root, nameCaesar);
        if (result != output_you)
        {
            cout << "fail test 8 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else
            cout << "pass test 8 \n";
    }
}