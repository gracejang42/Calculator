# Calculator
cpp implementation of calculator that can calculate +, - , / , * , ^ , % and parse parenthesis 

## Pseudocode

From Main: User enters Input (in the form of String Expression)
Input is fed through the Calculator c 
'''
class Calculator 
'''
Calculator is default
To be used by class calulator:
'''
string expr; //The Input
string::iterator it = begin(expr); //always starts at the beginning of the expression
stack<pair<operator_t, double>> tempEXPR; //for later use in evaluate()
double value; //This is what is printed at the end
'''

Expression is assigned to a constant reference of String locations
Exception: 
'''
Parastack (Holds String and Char locations)
        If '(' then push to the top of the stack
            If '(' 
                If Parastack is empty or the top of the stack is not '('
                throw error (Unbalanced Parentheses) 
    else remove from stack 
        if Parastack is not empty by the end
            throw error (Unbalanced Parenthesis)
        else, put the Value through evaluate()
        catch
'''

A place to assign operators so it's easier to reference them later:
'''
OP_ADD = '+',
        OP_SUB = '-',
        OP_EXP = '^',
        OP_MUL = '*',
        OP_DIV = '/',
        OP_MOD = '%',
        NULLTYPE = '0' //this will be important later in the evaluate function
'''
