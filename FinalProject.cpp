#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>
#include <algorithm>
#include <stack>
#include <memory>
#include <cmath>
#include <cctype>
using namespace std;

//CSCI Final Project: Advanced Calculator
//Grace Horton 

class Calculator
{
private:
    Calculator() = default;
    //Exception Catch 
    //prints final value
    Calculator(string const &str) : expr(str)
    {
        try
        {
            stack<string::value_type> para_stack;
            for (const auto &ch : expr)
            {
                switch (ch)
                {
                case '(':
                    para_stack.push('(');
                    break;
                case ')':
                    if (para_stack.empty() || para_stack.top() != '(')
                        throw runtime_error("Error: Unbalanced Parentheses");
                    else
                        para_stack.pop();
                    break;
                default:
                    break;
                }
            }
            if (!para_stack.empty())
                throw runtime_error("Error: Unbalanced Parentheses");
            value = evaluate();
            cout << value << "\n";
        }
        catch (exception const &e)
        {
            cerr << e.what() << "\n";
        }
    }
    //holder for operators so it's easier to call on them later
    enum class enum_op_t : char
    {
        OP_ADD = '+',
        OP_SUB = '-',
        OP_EXP = '^',
        OP_MUL = '*',
        OP_DIV = '/',
        OP_MOD = '%',
        NULLTYPE = '0'
    };
    //assigns a variable to operators, a priority integer that ranks the operators according to PEMDAS
    //and a char variable that finds the location of the operator
    class operator_t
    {
    public:
        enum_op_t type;
        int priority = 0;
        char position;
        operator_t(enum_op_t const &s, int i = 0, char a = 'L')
            : type(s), priority(i), position(a) {}

    };

    string expr;
    string::iterator it = begin(expr);
    stack<pair<operator_t, double>> tempEXPR;
    double value;

    //uses an iterator to find assigned operators and assigns them to the variables established in operator_t
    auto getOp()
    {
        switch (*it)
        {
        case '+':
            it++;
            return operator_t(enum_op_t::OP_ADD, 1, 'L');
        case '-':
            it++;
            return operator_t(enum_op_t::OP_SUB, 1, 'L');
        case '*':
            it++;
            return operator_t(enum_op_t::OP_MUL, 2, 'L');
        case '/':
            it++;
            return operator_t(enum_op_t::OP_DIV, 2, 'L');
        case '^':
            it++;
            return operator_t(enum_op_t::OP_EXP, 3, 'R');
        case '%':
            it++;
            return operator_t(enum_op_t::OP_MOD, 2, 'L');
        default:
            return operator_t(enum_op_t::NULLTYPE);
            break;
        }
    }
    //locates numbers and decimal points (for doubles) in the string expression and returns them as doubles
    auto getNum()
    {
        string::iterator tmp = it;
        for (; isdigit(*(tmp)) || *tmp == '.'; ++tmp)
        {
        }
        string tstr = string(it, tmp); 
        auto returnval = stod(tstr);
        it = tmp;
        return returnval;
    }
    //actually does the math. l stands for left double, r is right double
    auto performOp(operator_t var, double l, double r)
    {
        switch (var.type)
        {
        case enum_op_t::OP_ADD:
            return l + r;
        case enum_op_t::OP_DIV:
            if (!r)
            {
                throw runtime_error("Error: DO NOT DIVIDE BY ZERO ARE YOU CRAZY???");
            }
            else
                return l / r;
        case enum_op_t::OP_MUL:
            return l * r;
        case enum_op_t::OP_SUB:
            return l - r;
        case enum_op_t::OP_MOD:
            if (!r)
            {
                throw runtime_error("Error: mod 0 is FORBIDDEN O_o.");
            }
            else
                return fmod(l, r);
        case enum_op_t::OP_EXP:
            return pow(l, r);
        default:
            return 0.0;
        }
    }
    //Connector Function: This function connects most of my other functions
    //This is where the parenthesis parsing happens
    //makes negative numbers possible
    double getValue()
    {
        double returnVal = 0;
        switch (*it)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            returnVal = getNum();
            break;
        case '(':
            it++;
            returnVal = evaluate();
            if (*it != ')')
            {
                if (it <= end(expr))
                    throw runtime_error("Error: Inconsistent parentheses");
            }
            it++;
            break;
        case '+':
            it++;
            returnVal = getValue();
            break;
        case '-':
            it++;
            returnVal = getValue() * (-1);
            break;
        default:
            throw runtime_error("Error: Invalid Expression");
        }
        return returnVal;
    }
    //This function checks variables (established by type in operator_t) priority. 
    //It feeds the value through performOP according to the priority (PEMDAS)
    double evaluate()
    {
        tempEXPR.push({operator_t{enum_op_t::NULLTYPE}, 0}); //fills with NULL so while loop will work
        double returnval = getValue();
        while (!tempEXPR.empty())
        {
            operator_t var{getOp()};
            while (var.priority < tempEXPR.top().first.priority || (var.priority == tempEXPR.top().first.priority && var.position == 'L'))
            {
                if (tempEXPR.top().first.type == enum_op_t::NULLTYPE)
                {
                    tempEXPR.pop();
                    return returnval;
                }
                returnval = performOp(tempEXPR.top().first, tempEXPR.top().second, returnval);
                tempEXPR.pop();
            }
            tempEXPR.push({var, returnval});
            returnval = getValue();
        }
        return 0;
    }

public:
    static auto getSolution(string expression)
    {
        Calculator c(expression);
        return c;
    }
};
//make sure to type a capital "Q" to quit 
int main()
{
    for (;;)
    {
        string Q; 
        cout << "Welcome to the CSCI Exclusive Calculator! Please enter your equation (Press Q to quit): ";
        string input;
        getline(cin, input);
        if(input == "Q")
        {
            exit(0); 
        }
        else
        {
            Calculator::getSolution(input);
        }
    }
    return 0;
}
