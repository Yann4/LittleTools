#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

using std::vector;
using std::queue;
using std::stack;
using std::string;

using std::cout;
using std::endl;

struct oper
{
    string val;
    int prio;
    bool rightAss;
    oper(){};
    oper(string val, int prio, bool rightAss):val(val), prio(prio), rightAss(rightAss){};
};

struct expr_element
{
    bool isOperator;

    double num;
    oper op;

    expr_element(double val): num(val), isOperator(false){};
    expr_element(oper val): op(val), isOperator(true){};
};
queue<expr_element> infix_to_rpn(string infix);

int main(int argc, char** argv)
{
    string expr = "100+50/(10*(50+1)^2)";
    queue<expr_element> q = infix_to_rpn(expr);
    
    while(!q.empty())
    {
        if(q.front().isOperator)
        {
            cout << q.front().op.val << " ";
        }else
        {
            cout << q.front().num << " ";
        }
        q.pop();
    }
    cout << endl;
}

vector<oper> construct_op_list()
{
    vector<oper> ops;
    
    oper temp_op("+", 2, false);
    ops.push_back(temp_op);
    
    temp_op = oper("-", 2, false);
    ops.push_back(temp_op);
    
    temp_op = oper("*", 3, false);
    ops.push_back(temp_op);
    
    temp_op = oper("/", 3, false);
    ops.push_back(temp_op);
    
    temp_op = oper("^", 4, true);
    ops.push_back(temp_op);
    
    temp_op = oper("(", 999, true);
    ops.push_back(temp_op);

    return ops;
}

queue<expr_element> infix_to_rpn(string infix)
{
    vector<oper> operators = construct_op_list();
    string numbers = "1234567890";
    
    queue<expr_element> output;
    stack<oper> ops;
    
    for(int i = 0; i < infix.size(); ++i)
    {
        string token = infix.substr(i, 1);
        //Token is a number
        if(numbers.find(token) != std::string::npos)
        {
            int cnt = 0;
            while(numbers.find(infix.at(i+cnt)) != std::string::npos || infix.at(i+cnt) == '.')
            {
                cnt++;
            }
            token = infix.substr(i, cnt);
            
            output.push(expr_element(std::stod(token)));
            i += cnt - 1;
        }else if(token == ")")
        {
            while( ops.top().val != "(")
            {
                if(!ops.empty())
                {
                    output.push(ops.top());
                    ops.pop();
                }else
                {
                    cout << "Mismatched brackets" << endl;
                }
            }
            ops.pop();
            
        }else //Token is an operator
        {
            oper o1;
            for(int j = 0; j < operators.size(); j++)
            {
                oper o = operators.at(j);
                if(o.val == token)
                {
                    o1 = o;
                    break;
                }
            }
            
            if(!ops.empty())
            {
                oper o2 = ops.top();
                
                if(o2.val != "(" && ((!o1.rightAss && o1.prio <= o2.prio) || (o1.rightAss && o1.prio < o2.prio)))
                {
                    ops.pop();
                    output.push(expr_element(o2));
                }
            }
            ops.push(o1);
        }
    }
    
    while(!ops.empty())
    {
        output.push(ops.top());
        ops.pop();
    }
    
    return output;
}


