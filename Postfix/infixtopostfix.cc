#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Test whether @a s is one of {+,-,*,/}
 */
bool isOperator(char s) {
  if (s == '+' || s == '-' || s == '*' || s == '/' || s == '(' || s == ')')
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
int precedence(char op) {
  if (op == ')') {
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
  return precedence(op1) >= precedence(op2);
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
    if (isOperand(expr[i]))
      result.push_back(expr[i]);

    else if (isOperator(expr[i])) {
      while (!s.empty() && hashigherPrec(s.top(), expr[i]) && s.top() != '(') {
        if (expr[i] == ')') {
          while (s.top() != '(') {
            result.push_back(s.top());
            s.pop();
          }

        }

        else {
          result.push_back(s.top());
          s.pop();
        }
      }
      if (expr[i] != ')') {
        s.push(expr[i]);
      }
    }
  }
  while (!s.empty()) {
    if (s.top() == '(' || s.top() == ')') {
      s.pop();
    } else {
      result.push_back(s.top());
      s.pop();
    }
  }
  return result;
}

int main(void) {
  cout << "Welcome to the infix to postfix translator" << endl;
  // Getting the expression from the user
  // string expr;
  // getline(cin, expr);

  // From an arbitrary string

  // Example: "A+B*C"
  //     According to the arithmetic we could put the following parenthesis:
  //     A + (B * C) : Given that * has higher precedence than +, the we obtain.
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
  string expr2("A+B*C-D*E");   // Should result in: ABC*+DE*-
  string expr3("(A+B)-(C*D)"); // Should result in: AB+CD-*
  // string expr4("(A-B)*(B-C)/B"); // Should result in: AB+CD-*

  // cout << "Expression to convert:\n\t" << expr2 << endl;
  cout << "Expression to convert:\n\t" << expr3 << endl;
  // cout << "Postfix form: " << infixToPostfix(expr2) << endl;
  cout << "Postfix form: " << infixToPostfix(expr3) << endl;

  // IMPLEMENTACION DE LAS CONSTANTES

  return 0;
}
