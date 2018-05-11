#include <iostream>
#include <math.h>
#include <queue>
#include <stack>
#include <string>
using namespace std;

/**
 * @brief Test whether @a s is one of {+,-,*,/}
 */
bool isOperator(char s) {
  if (s == '+' || s == '-' || s == '*' || s == '/' ||
      s == '(' /*|| s == ')'*/ || s == '^')
    return true;
  return false;
}

/**
 * @brief Tests whether @a s is an operand
 */
bool isOperand(char s) { return !isOperator(s); }

/**
 * @brief Returns the precedence of operand @a op
 */
int precedenceExpr(char op) {
  if (op == '+' || op == '-') {
    return 1;
  } else if (op == '*' || op == '/') {
    return 2;
  } else if (op == '(') {
    return 3;
  } else
    return 4;
}

int precedencePila(char op) {
  if (op == '(') {
    return 0;
  } else if (op == '+' || op == '-') {
    return 1;
  } else if (op == '*' || op == '/') {
    return 2;
  } else {
    return 3;
  }
}

/**
 * @brief Tests whether @a op1 has higher priority than @a op2
 */
bool hashigherPrec(char op1, char op2) {
  return precedencePila(op1) >= precedenceExpr(op2);
}

/**
 * @brief Translates expression in @a expr from infix to postfix notation.
 *
 * This function assumes the possible set of operands {'+', '-', '*', '/'} and
 * also assumes that the expression consists only of digits, i.e. elements of
 * [0..9].
 *
 * Logic:
 * 1) Parse the expression from left to right, each token t = expr[i] is
 *    considered at a time.
 * 2) t can be either an operand (i.e. t \in {0,1,...,9}) or an operator (i.e. t
 *    \in {'+', '-', '*', '/'})
 * 3) If is an operand, t is appended to the result.
 * 4) If is an operator we cannot put it in the result straight away. Instead we
 *    keep it until we find the right hand operator. To keep it we use a stack.
 */
string infixToPostfix(const string &expr) {
  stack<char> s;
  string result;
  for (int i = 0; i < expr.size(); i++) {
    if (isOperand(expr[i])) {
      if (expr[i] == ')') {
        while (!s.empty() && s.top() != '(') {
          result.push_back(s.top());
          s.pop();
        }
        s.pop();
      } else
        result.push_back(expr[i]);
    } else if (isOperator(expr[i])) {
      while (!s.empty() && hashigherPrec(s.top(), expr[i])) {
        result.push_back(s.top());
        s.pop();
      }
      s.push(expr[i]);
    }
  }
  while (!s.empty()) {
    result.push_back(s.top());
    s.pop();
  }
  return result;
}

int operation(int b, int a, char op) {
  if (op == '*')
    return b * a;
  else if (op == '/')
    return b / a;
  else if (op == '+')
    return a + b;
  else if (op == '-')
    return b - a;
  else if (op == '^')
    return pow(b, a);
}

void evaluate(string expPF) {
  queue<char> q;
  vector<int> v;
  stack<int> s;
  int result;
  int A = 50;
  int B = 20;

  for (int i = 0; i < expPF.size(); i++) {
    if (isOperand(expPF[i])) {
      if (expPF[i] == 'A') {
        v.push_back(A);
      } else if (expPF[i] == 'B')
        v.push_back(B);
    } else
      q.push(expPF[i]);
  }

  for (int i = 0; i < v.size(); i++) {
    /*result = operation(v[i], v[i + 1], q.front());
    q.pop();*/
    cout << v[i];
  }
  // return result;
}

int main(void) {
  cout << "Welcome to the infix to postfix translator" << endl;
  // Getting the expression from the user
  // string expr;
  // getline(cin, expr);

  // From an arbitrary string

  // Example: "A+B*C"
  //     According to the arithmetic we could put the following parenthesis:
  //     A + (B * C) : Given that * has higher precedence than +, the we
  //     obtain.
  //
  //     A + (B C *) : We convert to postfix the first term
  //
  //     A (B C *) + : We convert the second term
  //
  //     A B C * +   : We remove the parenthesis as they are not needed in
  //                   postfix notation.
  // string expr("5+4*3");
  // cout << "Expression to convert:\n\t" << expr << endl;
  // cout << "Postfix form: " << infixToPostfix(expr) << endl;

  string expr2("A+B*C-D*E");           // Should result in: ABC*+DE*-
  string expr3("A*B");                 // Should result in: AB+CD-*A-
  string expr4("A*(B+C-(D/E^F)-G)-H"); // Should result in: ABCD+DEF^/-G-*H-

  // cout << "Expression to convert:\n\t" << expr2 << endl;
  cout << "Expression to convert:\n\t" << expr3 << endl;
  // cout << "Postfix form: " << infixToPostfix(expr2) << endl;
  cout << "Postfix form: " << infixToPostfix(expr3) << endl;

  // int x = (int)re - 48;
  // cout << "Evaluate: " << re << endl;

  //  char r = operation('g', '?', '+');
  //  cout << "Operation Test: " << r << endl;

  evaluate(infixToPostfix(expr3));
  cout << endl;
  return 0;
}
