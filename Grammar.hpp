/**********************************************
 * Author: Joshua M Blankley                  *
 * Date: February 2024                        *
 *                                            *
 * Description:                               *
 * This header file defines functions for     *
 * parsing and processing grammar constructs. *
 * It includes declarations for functions     *
 * like factor, term, expr, etc., which       *
 * handle different aspects of parsing.       *
 **********************************************/

#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_

#include <iostream>
#include <fstream>

using namespace std;

#include "Token.hpp"

string factor(ifstream &is);
string term(ifstream &is);
string term2(std::ifstream &is, string inVal);
string simpexpr(std::ifstream &is);
string simpexpr2(std::ifstream &is, string inVal);
string expr(std::ifstream &is);
string expr2(std::ifstream &is, string inVal);
string exprlist(std::ifstream &is);
string stmt(std::ifstream &is);
string stmtlist(std::ifstream &is);
string compound(std::ifstream &is);
string type(std::ifstream &is);
string idlist(ifstream &is);
string idlist2(ifstream &is);
string declaration(ifstream &is);
string program(std::ifstream &is);

#endif