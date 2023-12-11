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
bool compare(const std::vector<std::pair<char, int>> &a, const std::vector<std::pair<char, int>> &b);
void print(const std::vector<std::pair<char, int>> &a, const std::vector<std::pair<char, int>> &b);

vector<pair<char, int>> sort(vector<pair<char, int>> freq)
{

    vector<pair<char, int>> newFreq;

    int size = freq.size();
    while (!freq.empty())
    {
        pair<char, int> maxFreq = freq[0];
        for (auto &pair : freq)
        {
            if (pair.second > maxFreq.second)
            {
                maxFreq = pair;
            }
            else if (pair.second == maxFreq.second)
            {
                bool check1 = isupper(pair.first) ? true : false;
                bool check2 = isupper(maxFreq.first) ? true : false;

                if (check1 && !check2)
                {
                    maxFreq = pair;
                }
                else if (!check1 && check2)
                {
                    maxFreq = maxFreq;
                } //* pair thuong Max Hoa => giữ nguyên || pair Hoa max Hoa => so sánh giá trị
                  //*                                   || pair thường max thường => so sánh giá trị
                else if (pair.first > maxFreq.first)
                {
                    maxFreq = pair;
                }
            }
        }
        newFreq.push_back(maxFreq);

        char remove = maxFreq.first;
        auto it = std::remove_if(freq.begin(), freq.end(),
                                 [remove](const std::pair<char, int> &p)
                                 { return p.first == remove; });
        freq.erase(it);
    }

    return newFreq;
}

//* đầu vào là 1 chuỗi -> đầu ra chuỗi name đã được mã hóa Caesar và trả về danh sách freq có thứ tự giảm dần
vector<pair<char, int>> string_Processing(string &name)
{
    //* bước 1: liệt kê tuần suất xuất hiện của các kí tự riêng biệt trong tên của khách hàng (phân biệt hoa và thường)
    //* tạo thành một danh sách theo vị trí của các kí tự vào trước và vào sau
    //! VD : name = "aDdbaaabbb" -> kết quả bước này: freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
    // TODO

    map<char, int> freq_char;
    for (char c : name)
    {
        freq_char[c]++;
    }

    vector<pair<char, int>> freq_prev;
    for (const auto &pair : freq_char)
    {
        freq_prev.push_back(pair);
    }

    // for(auto pair: freq_prev){
    //     cout << pair.first << " " << pair.second << endl;
    // }

    //* bước 2: mã hóa Caesar chuỗi name thành chuỗi mới và mã hóa luôn freq_prev
    //! VD : name = "aDdbaaabbb", freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
    //! kq : name = "eEefeeefff", freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}]
    // TODO
    int k = 0;
    for (int i = k; i < name.size(); i++)
    {
        for (auto &pair : freq_prev)
        {
            if (name[i] == pair.first)
            {
                char base = isupper(pair.first) ? 'A' : 'a';
                name[i] = base + (name[i] - base + pair.second) % 26;
                k++;
                break;
            }
        }
    }

    for (auto &pair : freq_prev)
    {
        char base = isupper(pair.first) ? 'A' : 'a';
        pair.first = base + (pair.first - base + pair.second) % 26;
    }

    //* bước 3: công dồn freq_prev với các kí tự giống nhau sau khi mã hóa
    //^ chú ý cộng dồn lên phái đầu ví dụ dưới 'e' có 2 chỗ nên ta chọn đầu vector để giữ lại
    //! vd freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}] -> kq:  freq = [{e,5}, {E,1}, {f,4}]
    // TODO
    vector<pair<char, int>> freq;
    for (auto &pair : freq_prev)
    {
        if (freq.empty())
        {
            freq.push_back(pair);
        }
        else
        {
            bool flag = false; //* chưa có trong freq
            for (auto &pair1 : freq)
            {
                if (pair1.first == pair.first)
                {
                    pair1.second += pair.second;
                    flag = true;
                    break;
                }
            }

            if (!flag)
            {
                freq.push_back(pair);
            }
        }
    }

    //* bước 4: sort chuỗi freq mới tìm được phía trên theo chiều giảm dần
    //^ chú ý nếu tuần suất hiện bằng nhau thì kí tự nào lớn hơn thì lớn hơn, kí tự hoa lớn hơn kí tự thường
    // TODO
    freq = sort(freq);

    return freq;
}

int main()
{
    //! test 1: kiểm tra bước 1 bước 2
    string name = "aaa";
    cout << "test 1 - name = " << name << " : ";
    string nameResult = "ddd";
    std::vector<std::pair<char, int>> result = {{'d', 3}};
    std::vector<std::pair<char, int>> you = string_Processing(name);
    if (compare(result, you) && nameResult == name)
        cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 2: kiểm tra bước 1 bước 2
    name = "zzz";
    cout << "test 2 - name = " << name << " : ";
    nameResult = "ccc";
    result = {{'c', 3}};
    you = string_Processing(name);
    if (compare(result, you) && nameResult == name)
        cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 3: kiểm tra bước 3 và 4
    name = "aAzzAB";
    cout << "test 3 - name = " << name << " : ";
    nameResult = "bCbbCC";
    result = {{'C', 3}, {'b', 3}};
    you = string_Processing(name);
    if (compare(result, you) && nameResult == name)
        cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 4: kiểm tra bước 3 và 4
    name = "azdbc";
    cout << "test 4 - name = " << name << " : ";
    nameResult = "baecd";
    result = {{'e', 1}, {'d', 1}, {'c', 1}, {'b', 1}, {'a', 1}};
    you = string_Processing(name);
    if (compare(result, you) && nameResult == name)
        cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 5:
    name = "aAcc";
    cout << "test 5 - name = " << name << " : ";
    nameResult = "bBee";
    result = {{'e', 2}, {'B', 1}, {'b', 1}};
    you = string_Processing(name);
    if (compare(result, you) && nameResult == name)
        cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 6:
    name = "cac";
    cout << "test 6 - name = " << name << " : ";
    nameResult = "ebe";
    result = {{'e', 2}, {'b', 1}};
    you = string_Processing(name);
    if (compare(result, you) && nameResult == name)
        cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 7:
    name = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
    cout << "test 7 - name = " << name << " : ";
    nameResult = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
    result = {{'a', 26}};
    you = string_Processing(name);
    if (compare(result, you) && nameResult == name)
        cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 8:
    name = "aaaaaaaaaaaaaaaaaaaaaaaaab";
    cout << "test 8 - name = " << name << " : ";
    nameResult = "zzzzzzzzzzzzzzzzzzzzzzzzzc";
    result = {{'z', 25}, {'c', 1}};
    you = string_Processing(name);
    if (compare(result, you) && nameResult == name)
        cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }
}

void print(const std::vector<std::pair<char, int>> &a, const std::vector<std::pair<char, int>> &b)
{
    cout << "solution     : ";
    for (auto i : a)
        cout << "{" << i.first << ":" << i.second << "} -> ";
    cout << "\nsolution_you : ";
    for (auto i : b)
        cout << "{" << i.first << ":" << i.second << "} -> ";
    cout << "\n";
}

bool compare(const std::vector<std::pair<char, int>> &a, const std::vector<std::pair<char, int>> &b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (size_t i = 0; i < a.size(); ++i)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}
