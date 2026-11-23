#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isBalanced(string input)
{
    stack<char> symbols;

    for(char ch : input)
    {
        if(ch == '(' || ch == '[' || ch == '{')
        {
            symbols.push(ch);
        }

        else if(ch == ')' || ch == ']' || ch == '}')
        {
            if(symbols.empty())
            {
                return false;
            }

            char top = symbols.top();
            symbols.pop();

            if((ch == ')' && top != '(') ||
            (ch == ']' && top != '[') ||
            (ch == '}' && top != '{'))
            {
                return false;
            }
        }
    }

    return symbols.empty();
}

int main()
{
    string input;

    cout << "Enter symbols: ";
    getline(cin, input);

    if(isBalanced(input))
    {
        cout << "Symbols are balanced\n";
    }
    else
    {
        cout << "Symbols are NOT balanced\n";
    }

    return 0;
}