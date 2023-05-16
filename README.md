# Shunting-Yard
## VU Amsterdam, 2021
Shunting Yard Algorithm can parse mathematical expressions in infix notation, and produce a representation in reverse polish notation (RPN), that can be used e.g. for computing the value of the expression.

Examples:
infix expression	      RPN representation
12.5 + 1.1	            12.5 1.1 +
1 + 5 * 8 + 1	          1 5 8 * + 1 +
( 1 + 5 ) * ( 8 + 1 )	  1 5 + 8 1 + * 
2.5 / 3	                2.5 3 /


Simplifications:

1. Expressions consist of floating-point numbers (C++ type double), the operators +, -, *, /, %, and parentheses ( )
  -> +, -, *, / perform the well-known computations on floating-point numbers
  -> % converts (truncates) both its floating-point operands to integer numbers and then computes the division remainder (and converts the result back to floating point)
  
2. This means: no variables, no functions, no other operators (as part of the infix expressions)
3. Our five operators +, -, *, /, % are left-associative
4. We have two levels of operator precendence: +, - are low, and *, /, % are high

It reads lines of text from std::cin, each line consists of an expression in infix notation. For an expression, it applies the shunting-yard algorithm to compute the corresponding RPN notation, and evaluates the RPN notation to compute the numerical value.Finally it prints the RPN notation, followed by = and the numerical value of the expression. The program ends when an empty line has been read from std::cin.

Example of a correct execution of the program (alternating lines of input and output):

1 + 5 * 8 + 1
1 5 8 * + 1 + = 42
( 1 + 5 ) * ( 8 + 1 )
1 5 + 8 1 + * = 54
1 + 2 * 3 / 4 + 5
1 2 3 * 4 / + 5 + = 7.5
-.5e3 + 42
-500 42 + = -458
-7.9 % 4.2
-7.9 4.2 % = -3



Sources: 
Shunting-yard Algorithm
  -> https://en.wikipedia.org/wiki/Shunting-yard_algorithm
Operator precedence in C and C++ 
  -> https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B#Operator_precedence
