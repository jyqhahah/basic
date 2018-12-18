/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "../StanfordCPPLib/tokenscanner.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

/*bool trueCondition(Expression* condition, EvalState & state) {
	if (condition->eval(state)) return true;
	return false;
}*/


void Let::execute(EvalState & state) {
	state.setValue(var, exp->eval(state));
}

void Print::execute(EvalState & state) {
	cout << exp->eval(state) << endl;
}

void Input::execute(EvalState & state) {
	bool is_ok;
	while (1) {
		try {
			is_ok =true;
			cout << " ? ";
			string str;
			getline(cin, str);
			TokenScanner scanner;
			scanner.setInput(str);
			Expression *EXP = readE(scanner);
			if (EXP->getType() != CONSTANT) {
				cout << "INVALID NUMBER" << endl; error("INVALID NUMBER");
			}
                int val = stringToInteger(str);
				state.setValue(var, val);
		}
		catch (...) {
			is_ok = false;
		}
		if (is_ok) {
			break;
		}
	}
}

void If::execute(EvalState & state) {
	if (condition->eval(state) == 1) program.gotoLine(linen);
}

void Goto::execute(EvalState & state) {
	program.gotoLine(linen);
}

void Rem::execute(EvalState & state) {

}

StatementType If::getType() {
	return IF;
}

StatementType Let::getType() {
	return LET;
}

StatementType Print::getType() {
	return PRINT;
}

StatementType Input::getType() {
	return INPUT;
}

StatementType Goto::getType() {
	return GOTO;
}

StatementType End::getType() {
	return END;
}

StatementType Rem::getType() {
	return REM;
}