#include <iostream>
#include "PostfixCalculator.hpp"
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>

PostfixCalculator::PostfixCalculator():
PostfixExp(""){}


    /**@post Gets the string balanceString which contains the infix expression
       @param string balanceString
       @return true or false if there is balanced parenthesis or not
     */
bool PostfixCalculator::PBalanced(std::string balanceString){
	int countO = 0;
	int countC = 0;
		for(int i = 0; i <= balanceString.length(); i++){
			if(balanceString[i] == '('){
				countO++;
			}
			else if(balanceString[i] == ')'){
				countC++;
			}
		}
		if(countO == countC){
			return true;
		}
		else{
			return false;
		}
}

    /**@post Gets the string of numbers which contains the infix expression
       @param string num_string
       @return true or false if the index of the string contains a number
     */
bool PostfixCalculator::num (std::string num_string){
	for(int i = 0; i<num_string.length();i++){
		if(!isdigit(num_string[i])){
			return false;
		}
	}

	return true;
}	

    /**@post Gets the string imp which contains the operands.
       @param string imp
       @return the which operand has the higher precendence
     */
int PostfixCalculator::precedence(std::string imp){
	if(imp == "+" || imp == "-" || imp == "–"){
		return 1;
	}
	else if(imp == "*"||imp == "/"){
		return 2;
	}
}

/*@param takes a string represenation to the infix expression
  @post parses it into corresponding postfix expression and returns
   the postfix expressionm as a string
**/
std::string PostfixCalculator::convertToPostfix(std::string infix_expression){ 

	std::stringstream hi;
	std::string PostfixExp;
	std::stack<std::string> a_Stack;
	std::string ch;

	hi<<infix_expression;

	if(PBalanced(infix_expression)== false){
		throw(PrecondViolatedExcep("Unbalanced parenthesis"));
		}


	while(!hi.eof()){ 

		hi>>ch;
	
		if(num(ch) == true){
			PostfixExp = PostfixExp + ch + " ";
		}

		else if(ch =="("){
			a_Stack.push(ch);
		}	
	

		else if( ch=="+" || ch=="-" || ch=="*" || ch=="/" || ch == "–"){
				while(!a_Stack.empty() && (a_Stack.top() != ")") && precedence(ch)<= precedence(a_Stack.top()))
				{
					PostfixExp = PostfixExp + a_Stack.top() + " "; 
					a_Stack.pop();
				}

				a_Stack.push(ch); 

			}
			else if(ch==")"){
				while(!a_Stack.empty() && a_Stack.top() != "("){
					PostfixExp = PostfixExp + a_Stack.top() + " ";
					a_Stack.pop();
				}
				if(a_Stack.empty() == false && a_Stack.top() == "("){
					a_Stack.pop();
				}
			}
		else{
			throw(PrecondViolatedExcep("Unknown operator"));
			}
		}

	while(!a_Stack.empty())
	{
		PostfixExp = PostfixExp + a_Stack.top() + " ";
		a_Stack.pop();
	}
return PostfixExp;
}

/*@param takes a string representation of the postfix expression
  @post calculates the result and return it. it assumes that the 
  postfix expression is well formed
**/
	double PostfixCalculator::calculatePostfix(std::string postfix_expression){
		std::stack<double> a1;
		std::stringstream hello(postfix_expression);
		std::string numb;

		double result = 0;
		while(hello>>numb){

			if(num(numb) == true){
				double NUMBER_ = std::stof(numb);
				a1.push(NUMBER_);
			}

			else if(numb == "+"){
				double pop1 = a1.top();
				a1.pop();
				double pop2 = a1.top();
				a1.pop();
				result = pop2 + pop1;
				a1.push(result);
			}

			else if(numb == "-" || numb == "–"){
				double pop1 = a1.top();
				a1.pop();
				double pop2 = a1.top();
				a1.pop();
				result = pop2 - pop1;
				a1.push(result);			
			}

			else if(numb == "*"){	
				double pop1 = a1.top();
				a1.pop();
				double pop2 = a1.top();
				a1.pop();
				result = pop2 * pop1;
				a1.push(result);	

			}

			else if(numb == "/"){
				double pop1 = a1.top();
				a1.pop();
				double pop2 = a1.top();
				a1.pop();
				result = pop2/pop1;
				a1.push(result);			
			}

		}
	
		return result;
	}


/*@param takes string input_file_name which takes in a file and reads is
  @post will return the postfix in a postfix.txt and the results in a 
  results.txt file
**/
	 void PostfixCalculator::testCalculator(std::string input_file_name){
    	std::ifstream in_file;
    	in_file.open(input_file_name); 

    	std::ofstream out_file;
    	std::ofstream out_file_two;
    	out_file.open("results.txt");
    	out_file_two.open("postfix.txt");

    	if(in_file.fail()){
        std:: cout<<"File cannot be opened for reading"<< std::endl;
        exit(1);
        }
        std::string  in_text;

        while(std::getline(in_file, in_text)){
        	std::string conv_txt;
        	try{
        		  conv_txt = convertToPostfix(in_text);
        	}
        	catch(const PrecondViolatedExcep& E){
        		conv_txt = E.what();

        	}
        	out_file_two<<conv_txt<<"\n";
        	
        	if(!isdigit(conv_txt[0])){
        		out_file<<conv_txt<<"\n";
        	}
        	else{
        		out_file<<calculatePostfix(conv_txt)<<"\n";
        	}
        }
    	in_file.close();
    }
    

