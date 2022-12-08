# Building-an-interpreter
This is a simple interpreter for a simple language. However some of the code is missing, and I don't know where it is stored. The problem is at displaying the computational results.
The grammar rules of the language and its tokens were given in Programming Assignment 1 and 2. You are required to modify the parser you have implemented for the simple programming language to implement an interpreter for it. The specifications of the language is based on the following grammar rules specified in EBNF notations.

Prog ::= PROGRAM IDENT StmtList END PROGRAM

DeclStmt ::= (INT | FLOAT) IdentList

IdentList ::= IDENT, {, IDENT}

StmtList ::= Stmt; {Stmt;}

Stmt ::= DeclStmt | ControlStmt

ControlStmt ::= AssigStmt | IfStmt | WriteStmt

WriteStmt ::= WRITE ExprList

IfStmt ::= IF (LogicExpr) ControlStmt

AssignStmt ::= Var = Expr

ExprList ::= Expr {, Expr}

Expr ::= Term {(+|-) Term}

Term ::= SFactor {( *| / | % ) SFactor}

SFactor ::= (+ | -) Factor | Factor

LogicExpr ::= Expr (== | >) Expr

Var ::= IDENT

Factor = IDENT | ICONST | RCONST | SCONST | (Expr)

The following points describe the programming language. You have already implemented all of the syntactic rules of the language as part of the parser implementation. The points related to the dynamic semantics (i.e. runt-time checks) of the language must be implemented in your interpreter. These include points 7-15 in the following list. These points are:
<ol>
<li>The language has two types: INT, and FLOAT.</li>
<li>The PLUS and MINUS operators in Expr represent addition and subtraction operations.</li>
<li>The MULT, DIV, and REM operators in represent multiplication, division and remainder operations.</li>
<li>The PLUS, MINUS, MULT, DIV, and REM operators are left associative.</li>
<li>MUL, DIV, and REM have higher precedence than PLUS and MINUS.</li>
<li>Unary operator for the sign have higher precedence than MULT, DIV, and REM.</li>
<li>All variables have to be declared in declaration statements.</li>
<li>An IfStmt evaluates a logical expression (LogicExpr) as a condition. If the logical expression value is true, then the Stmt block is executed, otherwise it is not.</li>
<li>A WriteStmt evaluates the list of expressions (ExprList), and prints their values in order from left to right.</li>
<li>The ASSOP operator in the AssignStmt that assigns a value to a variable. It evaluates the Expr on the right-hand side and saves its value in a memory location associated with the left-hand side variable (Var). The left-hand side variable can be assigned any of the numeric types (i.e., INT, FLOAT) of the language. For example, an integer variable can be assigned a real value, and a real variable can be assigned an integer value. In either case, conversion of the value to the type of the variable must be applied. It is illegal to assign a string literal (SCONST) to a numeric type variable.</li>
<li>The binary operations for addition, subtraction, multiplication, and division are performed upon two numeric operands (i.e., INT or FLOAT) of the same or different types. If the operands are of the same type, the type of the result is the same type as the operator’s operands. Otherwise, the type of the result is real.</li>
<li>The binary operation for REM must be performed upon two integer operands. It is illegal to have a real operand for the REM operator.</li>
<li>The EQUAL and GTHAN relational operators operate upon two compatible operands. The evaluation of a logical expression, based on EQUAL or GTHAN operation, must be of a Boolean type that produces either a true or false value that controls whether the statement(s) of the selection IfStmt is executed or not.</li>
<li>It is an error to use a variable in an expression before it has been assigned.</li>
<li>The unary sign operators (+ or -) are applied upon a unary numeric operands (i.e., INT or FLOAT).</li>
