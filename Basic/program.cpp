/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include <map>
#include "program.h"
#include "statement.h"
#include "evalstate.h"
#include "parser.h"

using namespace std;





Program::Program() {
   
}

Program::~Program() {
	Line.clear();
	Stmt.clear();
}

void Program::clear() {
	Line.clear();
	Stmt.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
	map<int, string>::iterator it;
	it = Line.find(lineNumber);
	if (it != Line.end()) Line.erase(it);
	Line.insert(pair<int, string>(lineNumber, line));
}

void Program::removeSourceLine(int lineNumber) {
	map<int, string>::iterator it;
	it = Line.find(lineNumber);
	if (it != Line.end()) Line.erase(it);
}

string Program::getSourceLine(int lineNumber) {
	map<int, string>::iterator it;
	it = Line.find(lineNumber);
	if (it == Line.end()) return "";
	else return it->second;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
	Stmt[lineNumber] = stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
	map<int, string>::iterator it1;
	map<int, Statement*>::iterator it2;
	it1 = Line.find(lineNumber);
	it2 = Stmt.find(lineNumber);
	if (it1 == Line.end()||it2 == Stmt.end()) return NULL;
	else return it2->second;
}

int Program::getFirstLineNumber() {
	if (!Line.empty()) return Line.begin()->first;
    else return -1;     
}

int Program::getNextLineNumber(int lineNumber) {
	
	map<int, string>::iterator it;
	it = Line.upper_bound(lineNumber);
	if (it != Line.end()) return it->first;
    else return -1;     
}

void Program::print() {
	map<int, string>::iterator it;
	now = getFirstLineNumber();
	for (int i = 0; now != -1; i++) {
		it = Line.find(now);
		cout << it->second << endl;
		now = getNextLineNumber(now);
	}
}

void Program::RunProgram(EvalState &state) {
	map<int, Statement*>::iterator it=Stmt.begin();
    now = getFirstLineNumber();
	/*for (int i = 0; now != -1&&it->second->getType()!=END; i++) {
		it = Stmt.find(now);
		if (it != Stmt.end()) { now = getNextLineNumber(now); if (it->second->getType() == REM) continue;else it->second->execute(state); }
		else {
			it++;
			if (it == Stmt.end()) return;
			else error("LINE NUMBER ERROR");
		}
	}*/
	for (int i = 0;; i++) {
		it = Stmt.find(now);
		if (it != Stmt.end()){
		if (it->second->getType() == GOTO) { it->second->execute(state); it = Stmt.find(now); if (it == Stmt.end()) error("LINE NUMBER ERROR"); }
		if (it->second->getType() == IF) { 
			auto it1 = (If*)(it->second); 
			if (it1->trueIf(state)) {
				//int now1 = now;
				it1->execute(state);
				it = Stmt.find(now);
				//auto it2 = --it;
				if (it == Stmt.end())
					error("LINE NUMBER ERROR");
					//now = getNextLineNumber(now1);
			}
			else now = getNextLineNumber(now);
		}
		if (it->second->getType() == END) { break; }
		if (it->second->getType() != GOTO &&
			it->second->getType() != IF &&
			it->second->getType() != END) {
			now = getNextLineNumber(now);
			if (it->second->getType() == REM) continue;
			else it->second->execute(state);
		}
		}
		else break;
	}
}

void Program::gotoLine(int linenumber) {
	now = linenumber;
}
