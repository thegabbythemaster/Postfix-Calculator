#ifndef POST_FIX_CALCULATOR_H_
#define POST_FIX_CALCULATOR_H_
#include <iostream>
#include <stack>
#include <string>
#include "PrecondViolatedExcep.hpp"

class PostfixCalculator
{
    
public:
    PostfixCalculator(); // constructor


/*@param takes a string represenation to the infix expression
  @post parses it into corresponding postfix expression and returns
   the postfix expressionm as a string
   in the string represenaton of the postfix expression, operands and 
   operators are also seperated by a single space
**/
    std::string convertToPostfix(std::string infix_expression);

/*@param takes a string representation of the postfix expression
  @post calculates the result and return it. it assumes that the 
  postfix expression is well formed
**/
    double calculatePostfix(std::string postfix_expression);

/*@param takes string input_file_name which takes in a file and reads is
  @post will return the postfix in a postfix.txt and the results in a 
  results.txt file
**/
    void testCalculator(std::string input_file_name);


    /**
     helper for determining a number
     @post Gets the string of numbers which contains the infix expression
     @param string num_string
     @param from the beginning of the string
     @param to the end of the string
     @return true or false if the index of the string contains a number
     */
    bool num (std::string num_string);

    /**
     helper for determining greater value of + - and * /
     @post Gets the string imp which contains the operands.
     @param string imp
     @param from the beginning of the string
     @param to the end of the string
     @return the which operand has the higher precendence
     */

    int precedence(std::string imp);

    /**
     helper for determining if there is balanced parenthesis
     @post Gets the string balanceString which contains the infix expression
     @param string balanceString
     @param from the beginning of the string
     @param to the end of the string
     @return true or false if there is balanced parenthesis or not
     */

    bool PBalanced(std::string balanceString);

private:
    std::string PostfixExp;

   
}; // end List
#endif
