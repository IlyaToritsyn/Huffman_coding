#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <Windows.h>

using namespace std;

class Node
{
    public:
        int count;
        char symbol;

        Node* left;
        Node* right;

        Node()
        {

        }

        Node(char __symbol, int __count)
        {
            symbol = __symbol;
            count = __count;
        }

        Node(Node* l, Node* r)
        {
            symbol = 0;
            left = l;
            right = r;
            count = l->count + r->count;
        }
};

void BuildTable(Node* root, vector<bool>& code, map<char, vector<bool>>& table)
{
    if (root->left)
    {
        code.push_back(0);
        BuildTable(root->left, code, table);
    }

    if (root->right)
    {
        code.push_back(1);
        BuildTable(root->right, code, table);
    }

    if (root->symbol)
        table[root->symbol] = code;
    if (code.size())
        code.pop_back();
}

bool SortNode(const Node* a, const Node* b)
{
    return a->count < b->count;
}

string Decode(string& str, map<vector<bool>, char>& table)
{
    string out = "";

    vector<bool> code;

    for (int i = 0; i < str.length(); i++)
    {
        code.push_back(str[i] == '0' ? false : true);

        if (table[code])
        {
            out += table[code];

            code.clear();
        }
    }

    return out;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int a = 0, c;

    cout << "Введите строку:" << endl;

    string raw;

    getline(cin, raw);

    map<char, int> symbols;

    for (int i = 0; i < raw.length(); i++)
        symbols[raw[i]]++;

    list<Node*> trees;

    map<char, int>::iterator itr;

    for (itr = symbols.begin(); itr != symbols.end(); itr++)
    {
        Node* p = new Node(itr->first, itr->second);

        trees.push_back(p);
    }

    if (trees.size() == 0)
    {
        cout << "Строка пуста." << endl;

        system("pause");

        return 0;
    }

    else
    {
        if (trees.size() == 1)
        {
            Node* root = trees.front();

            cout << " - " << a << endl;
            cout << a << endl;

            system("pause");
        }

        else
        {
            while (trees.size() != 1)
            {
                trees.sort(SortNode);

                Node* l = trees.front();

                trees.pop_front();

                Node* r = trees.front();

                trees.pop_front();

                Node* parent = new Node(l, r);

                trees.push_back(parent);
            }

            Node* root = trees.front();

            vector<bool> code;

            map<char, vector<bool> > table;

            BuildTable(root, code, table);

            for (itr = symbols.begin(); itr != symbols.end(); itr++)
            {
                cout << itr->first << " - ";

                for (int j = 0; j < table[itr->first].size(); j++)
                    cout << table[itr->first][j];

                cout << endl;
            }

            string out = "";

            for (int i = 0; i < raw.length(); i++)
                for (int j = 0; j < table[raw[i]].size(); j++)
                {
                    out += table[raw[i]][j] + '0';

                    cout << table[raw[i]][j];
                }

            cout << endl;

            while (true);

            system("pause");
        }
    }
}