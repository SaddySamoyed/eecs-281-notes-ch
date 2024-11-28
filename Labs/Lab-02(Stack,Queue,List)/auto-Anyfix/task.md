The fixity of an operator describes its position relative to its operands. 

A prefix operator precedes its operands and a postfix operator follows them. In the case of operators that
operate on exactly two operands, we can also say that an infix operator appears between
its operands. An example of each:

-3  The one-operand minus sign for negation is a prefix operato
4!  The exclamation mark for factorial is a postfix operator
5 + 6 The plus sign for addition is an infix operator

Your task, however, is to evaluate expressions written in anyfix notation, meaning any
operator can act as a prefix, postfix, or infix operator depending on context. For consistency
across operators, you need only handle these four:
+ Addition
- Subtraction
* Multiplication
/ Integer division

All four take exactly two operands.

There is no negative sign; - always means subtraction.
What does ¡±depending on context¡± mean? As an expression is evaluated from left to right:
    When an operator is encountered that does not immediately have two operands waiting
    for it, it will wait until the second operand arrives before it operates. Examples:
    1. In + 1 2, the addition operator waits for 1 and 2 and then adds them
    2. In 3 ? 4, the multiplication operator has 3 waiting but must wait for 4 before it can perform multiplication

    When a number is encountered that does not immediately cause a waiting operator to
    have two operands, it will wait. Examples:
    1. In 3 * 4, the 3 waits and is later operated on by the multiplication operator
    2. In 5 6 -, both 5 and 6 wait and are later operated on by the subtraction operator

When an operator operates on operands, it produces a result that is immediately encountered. 
This means an expression like (1 - 2) * 3 will be evaluated how we would ordinarily evaluate it.

More-recently-encountered operators and operands take precedence. This means the ex?pression 3 2 1 - / is evaluated by subtracting 1 from 2, and then dividing 3 by the result.
Similarly, * + 4 5 6 is evaluated by adding 4 to 5, then multiplying the result by 6.

When evaluation of an anyfix expression finishes, there will be exactly zero operators and
one number waiting. The result of evaluation is that number.

You must write a function that accepts a single well-formed anyfix expression and returns
the result of evaluating that expression. A well-formed anyfix expression consists of n digits
and n - 1 operators in any order, and nothing else. Not even whitespace.

Each digit represents a separate number. 12 means one followed by two, not twelve.

Your implementation must be in the form of a function matching this prototype:
std :: int64_t evaluate ( std :: string const & expression );