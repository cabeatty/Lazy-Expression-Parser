/**
 * It is what it is.  I wrote an expression parser, with a lazy variable handling method.
 * Didnt use a single line of code from the book.
 * Created by colin on 02/02/17.
**/

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

double parse(char*& expr)
{
    char* end_ptr;
    double res = strtod(expr, &end_ptr);
    expr = end_ptr;
    return res;
}
double multdiv(char*& expr)
{
    double num1 = parse(expr);
    for(;;) {
        char op = *expr;
        if(op != '/' && op != '*')
        {
            return num1;
        }
        expr++;
        double num2 = parse(expr);
        if(op == '/')
            num1 /= num2;
        else
            num1 *= num2;
    }
}
double addsub(char*& expr)
{
    double num1 = multdiv(expr);
    for(;;) {
        char op = *expr;
        if(op != '-' && op != '+')
            return num1;
        expr++;
        double num2 = multdiv(expr);
        if(op == '-')
            num1 -= num2;
        else
            num1 += num2;
    }
}
double send(char* expr)
{

    return addsub(expr);
}

double evaluate(string s, vector<string> vars)
{
    char storage[2][vars.size()];
    if (vars.size() == 0)
        cout<<"No variables"<<endl;
    else
        for(int i = 0; i < vars.size(); i++)
        {
            vector<char> v(vars[i].begin(), vars[i].end());
            storage[i][0] = v[0];  //variable name
            storage[i][1] = v[2];  //variable value
        }
    vector<char> v(s.begin(), s.end());
    char * exp = new char[v.size()];

    //Do the variable replacement, the lazy way.  Did it this way because this is week 4 and we should not be writing software
    //of this caliber at this point.  Why a 200 level course is trying to cram the entire content of 300 level course (CSE 335) into
    //a single homework assignment is beyond me, especially this early in the semester.  Therefore you get the lazy way.

    for(int i=0; i<v.size(); i++)
    {
        exp[i] = v[i];

        for (int j = 0; j < vars.size(); j++)
        {
            if(exp[i] == storage[j][0])
                exp[i] = storage[j][1];
        }
    }

    return send(exp);
}

int main()
{
    string input;
    double result;
    vector<string> var;
    cout << "Enter a basic mathematical expression to be evaluated."<< endl;
    cout << "You will have the option to declare variables first." << endl;
    cout << "If you don't want to just enter a 0." << endl;
    cout << "!!Please refrain from adding any spaces.!!" << endl;
    cout << "An example of what A program would look like: " << endl;
    cout << "A=1\n"
            "B=2\n"
            "C=3\n"
            "0\n"
            "A+B+C\n" << endl;

    cout << "Variables to declare" << endl;
    string temp;
    cout << ">";
    cin >> temp;

    while (temp.compare("0"))
    {
        var.push_back(temp);
        cout << ">";
        cin >> temp;
    }

    for (int i = 0; i < var.size(); i++)
        cout << var[i] << endl;

    cout << "Expression to evaluate: " << endl;
    cout << ">";
    cin >> input;

    result = evaluate(input, var);
    cout << "The result of the expression [ " << input << " ] is:" << endl;
    cout << result << endl;

    return 0;
}