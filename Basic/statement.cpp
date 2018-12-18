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

void Let::execute(EvalState & state) {
	state.setValue(var, exp->eval(state));
}

void Print::execute(EvalState & state) {
	cout << exp->eval(state) << endl;
}

void Input::execute(EvalState & state) {
	string str;
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	while (true)
	{
		cout << " ? ";
		str.clear();
		char ch = getchar();
		while (ch != '\n') str.push_back(ch), ch = getchar();
		bool check = true;
		for (int i = 0; i < str.length(); ++i) {
			if (i == 0 && str[i] == '-') continue;
			if (!isdigit(str[i])) {
				check = false;
				cout << "INVALID NUMBER" << endl;
				break;
			}
		}
		if (check) {
			int val;
			val = stringToInteger(str);
			state.setValue(var, val);
			break;
		}
	}
}

bool If::trueIf( EvalState & state) {
	return condition->eval(state)==1;
}

void If::execute(EvalState & state) {
    if(condition->eval(state) == 1) program.gotoLine(linen);
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