# Calculator
cpp implementation of calculator that can calculate +, - , / , * , ^ , % and parse parenthesis 

## Pseudocode

From Main: User enters Input (in the form of String Expression)
Input is fed through the Calculator c 
```
class Calculator 
```
Calculator is default
To be used by class calulator:
```
string expr; //The Input
string::iterator it = begin(expr); //always starts at the beginning of the expression
stack<pair<operator_t, double>> tempEXPR; //for later use in evaluate()
double value; //This is what is printed at the end
```

Expression is assigned to a constant reference of String locations
Exception: 
```
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
```
```
Enum Class enum_op_t // A place to assign operators so it's easier to reference them later
        OP_ADD = '+',
        OP_SUB = '-',
        OP_EXP = '^',
        OP_MUL = '*',
        OP_DIV = '/',
        OP_MOD = '%',
        NULLTYPE = '0' //this will be important later in the evaluate function

class operator_t 
function operator_t //assigns a variable to my enum operator types, an int to represent priority(PEMDAS), and a char to represent position (left or right)
type s= enum_op_t 
int i= priority
char a= position //this is mostly for the exponent and its postional relationship with Parenthesis
```
**GetOp()**
Use and iterator to assign priority to each operator using the variables established in class
example:
```
case '+':
            it++;
            return operator_t(enum_op_t::OP_ADD, 1, 'L');
```
"Assign '+' with 1 priority (this is the lowest value, 3 is the highest), and Left position" 
continue for all operators

**GetNum()**

assign 'it' to a temporary iterator tmp 
Continuously scan the expression for digits (0-9) and '.' (for doubles)
This will continue looping until there all the numbers have been located 
Start at 'it' and create a string 'tmp' length 
Assign that string to string tstr 
Change tstr from a string to double returnVal
performOP() //the arithmatic function 

```
assigns '+' to left + right 
        '-' to left - right
        '/' to left/right and includes a throw for division by zero
        '%' to fmod(left,right) and includes a throw for zero
        '^' to pow(left, right)
        '*' to left*right
```
**GetValue()**

A dereferenced iterator checks for (0-9), if found, the values are sent to GetNum()
```
if '(' the expression is sent through evaluate, which puts it through performOP 
    if the next Parenthesis is not ')'
        check: if its the end of the experession throw error (Unbalances Parenthesis)
    else, keep going and filter through evaluate/getValue again as necessary 
if '-' multiply whatever is left at the end of getValue by -1 (for negative numbers) 
Returns a double returnval 
```
**Evaluate()**

Takes the values from returnval and evaluates them
tempExpr is filled with NULLTYPE and 0 so it can be 'empty' without being empty 
```
while (tempExpr is not empty)
    var = operators (getOP())
    while(a variable in the expression has a priority less than the variable at the front 
    OR (while the variables priority equals the top variables priority AND the variables position is Left))
        if(the the only variable is NULLTYPE)
            This is the final value. Remove it from the stack and return it as a double
        else
            the return value (returnval) = performOP(variable at top of the stack, the next double (this is a space for new values produced by previous calculations)
            and next double) //so if the expression is (1+5)-1 first performOp is '+' 1(L) 5(R) l + r or 1+5 which would produce 6, then '-' 6(L) 1(R) 6-1 inevitably producing 5
    
    when a final value is reached filter that through GetValue() one last time to get a double value 
```
Final value is printed by Calculator 



