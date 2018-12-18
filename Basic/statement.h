/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

class Program;
#include "evalstate.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include <map>
#include "exp.h"
#include "program.h"
using namespace std;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

enum StatementType {IF, LET, GOTO, PRINT, INPUT, END, REM};

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;


   virtual StatementType getType() = 0;
	

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class Let : public Statement {
private :
	string line;
	string var;
	Expression* exp;
	Program & program;

public :
	Let(string line, Program & program, string var,Expression * exp ) : line(line), program(program), var(var), exp(exp) {};
	~Let() {};
	virtual void execute(EvalState & state);
	virtual StatementType getType();


};

class Print : public Statement {

public :
	Print(string line, Program & program, Expression * exp) : line(line), program(program), exp(exp) {};
	~Print() {};
	virtual void execute(EvalState & state);
	virtual StatementType getType();

private :
	string line;
	string var;
	Program & program;
	Expression * exp;
	//int result;
};

class Input : public Statement {

public :
	Input(string line, Program & program, string var) : line(line), program(program), var(var) {};
	~Input() {};
	virtual void execute(EvalState & state);
	virtual StatementType getType();

private:
	string line;
	string var;
	Program & program;
};

class If : public Statement {

public :
	If(string line, Program & program, Expression* condition, int linen) : line(line), program(program), condition(condition), linen(linen) {};
	~If() {};
	virtual void execute(EvalState & state);
	virtual StatementType getType();

private :
	string line;
	Expression* condition;
	Program & program;
 	int linen;
};

class Goto : public Statement {

public : 
	Goto(string line, Program & program, int linen) : line(line), program(program), linen(linen) {};
	~Goto() {};
	virtual void execute(EvalState & state);
	virtual StatementType getType();

private :
	string line;
	Program & program;
	int linen;
};

class End : public Statement {
	virtual StatementType getType();
};

class Rem : public Statement {
    virtual void execute(EvalState & state);
	virtual StatementType getType();
};
#endif
