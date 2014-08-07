#include <stack>
#include <iostream>
#include <cctype>
using namespace std;


double Calculate(istream& ins);
void eval(stack<double>& numbers, stack<char>& ops);
int main()
{
    double ans;
    cout << "Flank all operations with parenthesis!!" << endl;
    cout << "enter an expression: ";
    ans=Calculate(cin);
    cout << ans << endl;
}

double Calculate(istream& ins)
{
    stack<double> numbers;
    stack<char> ops;
    char punct;
    double num;
    char op;
    while(ins && ins.peek()!='\n')
    {
	if(ispunct(ins.peek()))
	{
	    ins >> punct;
	    if((punct=='+')||(punct=='-')||(punct=='/')||(punct=='*'))
	    {
		op=punct;
		ops.push(op);
	    }
	    if(punct==')')
	    {
		eval(numbers, ops);
	    }
	}
	if(isdigit(ins.peek()))
	{
	    ins >> num;
	    numbers.push(num);
	}
    }
    return numbers.top();
}

void eval(stack<double>& numbers, stack<char>& ops)
{
    double num;
    double num2;
    double ans;
    num2=numbers.top();
    numbers.pop();

    num=numbers.top();
    numbers.pop();
    if(ops.top()=='+')
    {
	ans=num+num2;
    }
    if(ops.top()=='-')
    {
	ans=num-num2;
    }
    if(ops.top()=='/')
    {
	ans=num/num2;
    }
    if(ops.top()=='*')
    {
	ans=num*num2;
    }
    ops.pop();

    numbers.push(ans);
}
