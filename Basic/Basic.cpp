/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   //cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

bool checkRepet(string str) {
	if (str == "IF")    return false;
	if (str == "THEN")  return false;
	if (str == "LET")   return false;
	if (str == "PRINT") return false;
	if (str == "INPUT") return false;
	if (str == "GOTO")  return false;
	if (str == "REM")   return false;
	if (str == "END")   return false;
	if (str == "RUN")   return false;
	if (str == "QUIT")  return false;
	if (str == "LIST")  return false;
	if (str == "CLEAR") return false;
	if (str == "HELP")  return false;
	return true;
}

bool checkRepet1(string str) {
	if (str == "LET")   return false;
	if (str == "PRINT") return false;
	if (str == "INPUT") return false;
	if (str == "RUN")   return false;
	if (str == "QUIT")  return false;
	if (str == "LIST")  return false;
	if (str == "CLEAR") return false;
	if (str == "HELP")  return false;
	return true;
}

bool checkRepet2(string str) {
	if (str == "IF")    return false;
	if (str == "LET")   return false;
	if (str == "PRINT") return false;
	if (str == "INPUT") return false;
	if (str == "GOTO")  return false;
	if (str == "REM")   return false;
	if (str == "END")   return false;
	return true;
}

bool check(string str) {
	int pos;
	for (int i = 0; i < str.length(); ++i) 
	if (str[i] != ' ') { 
		pos = i;
		if (!isalpha(str[pos])) return false;
		while (str[pos] != ' ') ++pos;
		break;
	}
	for (int i = pos; i < str.length(); ++i) if (str[i] != ' ') return false;
	return true;
}

/*void InputCorrect(string line, EvalState & state, string & var ) {
	string::size_type posInput = line.find("INPUT");
	string mainSentence = line.substr(posInput + 5);
	if ( !check(mainSentence)|| !checkRepet(mainSentence)) 
		error("SYNTAX ERROR");
	
	return;
}

void PrintCorrect(string line, EvalState & state, int & result) {
	string::size_type posPrint = line.find("PRINT");
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	string mainSentence = line.substr(posPrint + 5);
	scanner.setInput(mainSentence);
	Expression *exp = parseExp(scanner);
	int value = exp->eval(state);
	result = value;
	return;
}

void LetCorrect(string line, EvalState & state, string & var, int & value) {
	if (line.find("=") == string::npos) { error("SYNTAX ERROR");}
	string::size_type posLet = line.find("LET"), posOp = line.find("=");
	string Lhs = line.substr(posLet + 3, posOp - posLet - 3);
	string Rhs = line.substr(posOp + 1);
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(Lhs);
	var = scanner.nextToken();
	if (!check(Lhs) || !checkRepet(Lhs)) error("SYNTAX ERROR");

	scanner.setInput(Rhs);
	Expression *expR = parseExp(scanner);
	int Rvalue = expR->eval(state);
	value = Rvalue;
	return;
}

void IfCorrect(string line, EvalState & state, bool &condition, int &linen) {
	char op;
	bool isFind = false;
	if (line.find("=") != string::npos) { op = '=', isFind = true; }
	if (line.find("<") != string::npos) {
		if (isFind) error("SYNTAX ERROR");
		else {
			op = '<'; isFind = true;
		}
	}
	if (line.find(">") != string::npos) {
		if (isFind) error("SYNTAX ERROR");
		else {
			op = '>'; isFind = true;
		}
	}
	if (line.find("THEN") == string::npos || line.find(op) > line.find("THEN")) error("SYNTAX ERROR");;

	string::size_type posIf = line.find("IF"), posOp = line.find(op), posThen = line.find("THEN");

	string Lhs = line.substr(posIf + 2, posOp - posIf - 2);
	string Rhs = line.substr(posOp + 1, posThen - posOp - 1);
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();

	scanner.setInput(Lhs);
	Expression *expL = parseExp(scanner);
	int Lvalue = expL->eval(state);

	scanner.setInput(Rhs);
	Expression *expR = parseExp(scanner);
	int Rvalue = expR->eval(state);

	if (Lvalue == Rvalue) condition = true;
	else condition = false;

	string mainSentence = line.substr(posThen + 4);
	scanner.setInput(mainSentence);
	string mainSentence1 = scanner.nextToken();
	if (scanner.hasMoreTokens() || !isdigit(mainSentence1[0])) error("SYNTAX ERROR");
    int result = stringToInteger(mainSentence);
	linen = result;
	return ;
}

void GotoCorrect(string line, EvalState & state, int &linen) {
	string::size_type posGoto = line.find("GOTO");
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	string mainSentence = line.substr(posGoto + 4);
	scanner.setInput(mainSentence);
	string mainSentence1 = scanner.nextToken();
	if (scanner.hasMoreTokens() || !isdigit(mainSentence1[0])) error("SYNTAX ERROR");
	int result = stringToInteger(mainSentence);
	linen = result;
	return;
}*/

void processLine(string line, Program & program, EvalState & state) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	int linenumber;
	Expression *exp = readE(scanner);
	if (exp->getType() == IDENTIFIER) {
		if (checkRepet1(exp->toString())) error("SYNTAX ERROR");
		else {
               if (exp->toString() == "LET") {
					string var; 
					auto exp2 = readE(scanner);
					if (scanner.hasMoreTokens()) error("SYNTAX ERROR");
					auto lhs = ((CompoundExp*)exp2)->getLHS();
					auto rhs = ((CompoundExp*)exp2)->getRHS();
					auto op = ((CompoundExp*)exp2)->getOp();
					if (op != "=" || !checkRepet(lhs->toString())) error("SYNTAX ERROR");
					var = lhs->toString();
					Let sentence(line, program, var, rhs);
					sentence.execute(state);
					return;
				}
			   if (exp->toString() == "INPUT") {
				   auto exp2 = readE(scanner);
				   string var = exp2->toString();
				   if (!checkRepet(exp2->toString())) error("SYNTAX ERROR");
				   if (scanner.hasMoreTokens() ||exp2->getType()!=IDENTIFIER) {
						error("SYNTAX ERROR");
					}
					Input sentence(line, program, var);
					sentence.execute(state);
					return;
				}
				if (exp->toString() == "PRINT") {
					auto exp2 = readE(scanner);
					if (scanner.hasMoreTokens()) {
						error("SYNTAX ERROR");
					}
                    Print sentence(line, program,exp2);
					sentence.execute(state);
					return;
				}
				if (exp->toString() == "RUN") {
					program.RunProgram(state);
					return;
				}
				if (exp->toString() == "HELP") {
					cout << "It's a BASIC interpreter." << endl;
					return;
				}
				if (exp->toString() == "QUIT") {
					exit(0);
				}
				if (exp->toString() == "LIST") {
					program.print();
					return;
				}
				if (exp->toString() == "CLEAR") {
					program.clear();
					state.clear();
					return;
				}
			
		}
	}
	if (exp->getType() == CONSTANT) {
		int value = exp->eval(state);
		linenumber = value;
		delete exp;
		program.addSourceLine(linenumber, line);
		if (!scanner.hasMoreTokens()) {
			program.removeSourceLine(linenumber);
			return;
		}
	    exp = readE(scanner);
		 if (exp->toString() == "LET") {
			 string var;
			 auto exp2 = readE(scanner);
			 if (scanner.hasMoreTokens()) error("SYNTAX ERROR");
			 auto lhs = ((CompoundExp*)exp2)->getLHS();
			 auto rhs = ((CompoundExp*)exp2)->getRHS();
			 auto op = ((CompoundExp*)exp2)->getOp();
			 if (op != "=" || !checkRepet(lhs->toString())) error("SYNTAX ERROR");
			 var = lhs->toString();
			 auto sentence = new Let(line, program, var, rhs);
			 program.setParsedStatement(linenumber, sentence);
		 }
		 if (exp->toString() == "GOTO") {
			 int linen;
			 auto exp2 = readE(scanner);
			 if (checkRepet(exp2->toString())) error("SYNTAX ERROR");
			 if (scanner.hasMoreTokens()) error("SYNTEX ERROR");
			 linen = exp2->eval(state);
             auto sentence = new Goto(line,program, linen);
			 program.setParsedStatement(linenumber, sentence);
		 }
		 if (exp->toString() == "IF") {
			 int linen;
			 auto exp2 = readE(scanner);
			 auto condition = (CompoundExp*)exp2;
			 auto op  = ((CompoundExp*)exp2)->getOp();
			 if (op != "=" && op != ">" && op != "<") error("SYNTEX ERROR");
			 auto exp3 = readE(scanner);
			 if (exp3->toString() != "THEN") error("SYNTEX ERROR");
			 auto exp4 = readE(scanner);
			 if (exp4->getType() != CONSTANT) error("SYNTEX ERROR");
			 linen = exp4->eval(state);
			 auto sentence = new If(line, program, condition, linen);
			 program.setParsedStatement(linenumber, sentence);
		 }
		 if (exp->toString() == "INPUT") {
			 auto exp2 = readE(scanner);
			 if (!checkRepet(exp2->toString())) error("SYNTAX ERROR");
			 string var = exp2->toString();
			 if (scanner.hasMoreTokens() || exp2->getType() != IDENTIFIER) {
				 error("SYNTAX ERROR");
			 }
			 auto sentence = new Input(line, program, var);
			 program.setParsedStatement(linenumber, sentence);
		 }
		 if (exp->toString() == "PRINT") {
			 auto exp2 = readE(scanner);
			 if (scanner.hasMoreTokens()) {
				 error("SYNTAX ERROR");
			 }
             auto sentence = new Print(line, program, exp2);
			 program.setParsedStatement(linenumber, sentence);
		 }
		 if (exp->toString() == "REM") {
			 auto sentence = new Rem();
			 program.setParsedStatement(linenumber, sentence);
		 }
		 if (exp->toString() == "END") {
			 if (scanner.hasMoreTokens()) error("SYNTAX ERROR");
		 }
		 if (checkRepet2(exp->toString())) error("SYNTAX ERROR");
	 }

	/* Expression *exp = parseExp(scanner);
	 int value = exp->eval(state);
	 cout << value << endl;
	 delete exp;*/
}

