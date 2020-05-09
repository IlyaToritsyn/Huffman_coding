#include <locale>
#include <iostream>
#include <vector>
#include <list>
#include <map>
//#include <string>
#include <stdio.h>
#include <wchar.h>
//#include <string>
//#include <unistd.h>
//#include <stdexcept>
//#include <string.h>

//#include <Windows.h>
#include <stdio.h> /* Для printf */
#include <locale.h> /* Для русского языка */
#include <string>
//#include <io.h>
#include <fcntl.h>
using namespace std;

class Node
{
public:
    int count;
    wchar_t symbol;

    Node* left;
    Node* right;

    Node()
    {

    }

    Node(wchar_t __symbol, int __count)
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

void BuildTable(Node* root, vector<bool>& code, map<wchar_t, vector<bool>>& table)
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

//wstring Decode(wstring& str, map<vector<bool>, wchar_t>& table)
//{
//    wstring out(L"\n");
//
//    vector<bool> code;
//
//    for (int i = 0; i < str.length(); i++)
//    {
//        code.push_back(str[i] == '0' ? false : true);
//
//        if (table[code])
//        {
//            out += table[code];
//
//            code.clear();
//        }
//    }
//
//    return out;
//}

int main()
{
    /*locale loc;
try {
loc = std::locale ( "ru_RU.utf8" );
}
catch( std::runtime_error ) {
loc = std::locale ( loc, "", std::locale::ctype );
}
locale::global( loc );*/
//SetConsoleCP(1251);
//SetConsoleOutputCP(1251);
//setlocale(LC_ALL,"Russian");
//setlocale( LC_ALL, "ru_RU.utf8" );
    //system("chcp 1251 > nul");

    locale::global(locale(""));
    //system("chcp 1251");
    //setlocale(LC_ALL, "Rus"); /* Обязательно должно быть первым */
    /*_setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);*/

    //std::wcout << L"Unicode -- English -- Русский -- Ελληνικά -- Español." << std::endl;
    // или
    //wprintf(L"%s", L"Unicode -- English -- Русский -- Ελληνικά -- Español.\n");

    //setlocale(LC_ALL, "rus");

    int a = 0, c;

    wcout << L"Введите строку:" << endl;

    //string raw;

    //getline(cin, raw);
    wstring raw(L"\n");
    getline(wcin, raw);
    map<wchar_t, int> symbols;

    for (int i = 0; i < raw.length(); i++)
        symbols[raw[i]]++;

    list<Node*> trees;

    map<wchar_t, int>::iterator itr;

    for (itr = symbols.begin(); itr != symbols.end(); itr++)
    {
        Node* p = new Node(itr->first, itr->second);

        trees.push_back(p);
    }

    if (trees.size() == 0)
    {
        wcout << L"Строка пуста." << endl;

        system("pause");

        return 0;
    }

    else
    {
        if (trees.size() == 1)
        {
            Node* root = trees.front();

            wcout << L" - " << a << endl;
            wcout << a << endl;

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

            map<wchar_t, vector<bool> > table;

            BuildTable(root, code, table);

            for (itr = symbols.begin(); itr != symbols.end(); itr++)
            {
                wcout << itr->first << L" - ";

                for (int j = 0; j < table[itr->first].size(); j++)
                    wcout << table[itr->first][j];

                wcout << endl;
            }

            wstring out(L"\n");

            for (int i = 0; i < raw.length(); i++)
                for (int j = 0; j < table[raw[i]].size(); j++)
                {
                    out += table[raw[i]][j] + '0';

                    wcout << table[raw[i]][j];
                }

            wcout << endl;

            while (true);

            system("pause");
        }
    }
}