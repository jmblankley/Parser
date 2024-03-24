/***************************************************************
 * Author: Joshua M. Blankley                                  *
 * Date: February 2024                                         *
 *                                                             *
 * Description:                                                *
 * This file defines functions for parsing and processing      *
 * grammar constructs. It includes implementations for         *
 * functions like program, factor, term, etc., which handle    *
 * different aspects of parsing.                               *
 ***************************************************************/

#include "Grammar.hpp"
#include "Token.hpp"

using namespace std;

// global indentation integer
int indent = 0;

// Function: getIndent
// Parameters: none
// Purpose: Helper function that uses a string and integer to construct indentation
string getIndent()
{
	return string(indent, ' ');
}
// Function: program
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a program construct from the input stream.
string program(std::ifstream &is)
{
	string result = "";
	int pos = is.tellg();

	Token tok;
	tok.get(is);

	if (tok.type() == INTEGER || tok.type() == FLOAT || tok.type() == VOID)
	{
		is.seekg(pos);
		string decVal = declaration(is);
		string proVal = program(is);
		result += decVal + proVal;
	}
	else
	{
		is.seekg(pos);
		result += compound(is);
	}

	is.seekg(pos);
	return result;
}
// Function: factor
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a factor construct from the input stream.
string factor(ifstream &is)
{
	string result = "";

	Token fac;
	fac.get(is);

	if (fac.type() == ID)
	{
		result += fac.value();

		int pos = is.tellg();

		Token next;
		next.get(is);

		if (next.type() == LPAREN)
		{
			result += next.value() + " ";

			result += exprlist(is);

			Token rPar;
			rPar.get(is);

			if (rPar.type() == RPAREN)
			{
				result += " " + rPar.value();
			}
		}
		else
		{
			is.seekg(pos);
			return result;
		}
	}
	else if (fac.type() == NUM_REAL || fac.type() == NUM_INT)
	{
		result += fac.value();
	}
	else if (fac.type() == LPAREN)
	{
		result += fac.value() + " ";
		result += expr(is);

		Token rPar;
		rPar.get(is);

		if (rPar.type() == RPAREN)
		{
			result += " " + rPar.value();
		}
	}

	return result;
}
// Function: term
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a term construct from the input stream.
string term(ifstream &is)
{
	string result = "";

	result += factor(is); // Read factor and update result
	int pos = is.tellg();

	Token next;
	next.get(is);

	if (next.type() == MULOP)
	{
		result += " " + next.value() + " ";
		result += term(is); // Recursive call, which may read more input
	}
	else
	{
		is.seekg(pos);
	}

	return result;
}
// Function: simpexpr
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a simple expression construct from the input stream.
string simpexpr(std::ifstream &is)
{
	string result = "";

	result += term(is);
	int pos = is.tellg();

	Token next;
	next.get(is);

	if (next.type() == ADDOP)
	{
		result += " " + next.value() + " ";
		result += simpexpr(is);
	}
	else
	{
		is.seekg(pos);
	}

	return result;
}
// Function: expr
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses an expression construct from the input stream.
string expr(std::ifstream &is)
{
	string result = "";

	result += simpexpr(is);
	int pos = is.tellg();

	Token next;
	next.get(is);

	if (next.type() == RELOP)
	{
		result += " " + next.value() + " ";
		result += simpexpr(is);
	}
	else
	{

		is.seekg(pos);
	}
	return result;
}
// Function: exprlist
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses an expression list construct from the input stream.
string exprlist(std::ifstream &is)
{
	string result = "";

	result += expr(is);
	int pos = is.tellg();

	Token comTok;
	comTok.get(is);

	if (comTok.type() == COMMA)
	{
		result += comTok.value();
		result += exprlist(is);
	}
	else
	{
		is.seekg(pos);
	}

	return result;
}
// Function: stmt
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a statement construct from the input stream.
string stmt(std::ifstream &is)
{
	string result = getIndent() + "";

	Token statement;
	statement.get(is);

	if (statement.type() == ID)
	{

		result += statement.value();

		int pos = is.tellg();

		Token next;
		next.get(is);

		if (next.type() == LPAREN)
		{
			result += " " + next.value() + " ";

			result += exprlist(is);

			Token rPar;
			rPar.get(is);

			if (rPar.type() == RPAREN)
			{
				result += " " + rPar.value();
			}
			else
			{
				is.seekg(pos);
				return result;
			}
		}
		else if (next.type() == ASSIGNOP)
		{
			result += " " + next.value() + " ";
			result += expr(is);
		}
		else
		{
			is.seekg(pos);
			return result;
		}
	}
	else if (statement.type() == IF)
	{
		indent++;
		result += statement.value() + " ";
		result += expr(is);

		int pos = is.tellg();

		Token then;
		then.get(is);

		if (then.type() == THEN)
		{
			result += then.value() + "\n";
			result += compound(is);

			Token els;
			els.get(is);

			if (els.type() == ELSE)
			{
				indent--;
				result += "\n" + getIndent() + els.value() + "\n";
				result += compound(is);
			}
		}
		else
		{
			is.seekg(pos);
			return result;
		}
	}
	else if (statement.type() == WHILE)
	{
		indent++;
		result += statement.value() + " ";

		int pos = is.tellg();

		Token next;
		next.get(is);

		if (next.type() == LPAREN)
		{
			result += next.value() + " ";
			result += expr(is);

			Token rPar;
			rPar.get(is);

			if (rPar.type() == RPAREN)
			{
				result += " " + rPar.value() + "\n";
				result += compound(is);
			}
		}
		else
		{
			is.seekg(pos);
			return result;
		}
	}
	else
	{
		result += compound(is);
		return result;
	}
	return result;
}
// Function: stmtlist
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a statement list construct from the input stream.
string stmtlist(std::ifstream &is)
{
	string result = "";

	result += stmt(is);
	int pos = is.tellg();

	Token next;
	next.get(is);

	if (next.type() == SEMICOLON)
	{
		result += next.value() + "\n";
		result += stmtlist(is);
	}
	else
	{
		is.seekg(pos);
	}

	return result;
}
// Function: compound
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a compound construct from the input stream.
string compound(std::ifstream &is)
{
	string result = getIndent() + "";

	int pos = is.tellg();

	Token tok;
	tok.get(is);

	if (tok.type() == BEGIN)
	{

		indent++;
		result += tok.value() + "\n";
		result += stmtlist(is);

		Token end;
		end.get(is);
		if (end.type() == END)
		{
			indent--;
			result += "\n" + getIndent() + end.value();
		}
	}
	else
	{
		is.seekg(pos);
	}

	return result;
}
// Function: type
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a type construct from the input stream.
string type(std::ifstream &is)
{
	string result = "";

	int pos = is.tellg();

	Token tok;
	tok.get(is);

	if (tok.type() == INTEGER || tok.type() == FLOAT || tok.type() == VOID)
	{
		result += tok.value() + " ";
	}
	else
	{
		is.seekg(pos);
	}

	return result;
}
// Function: idlist
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses an idlist construct from the input stream.
string idlist(std::ifstream &is)
{
	string result = "";

	Token tok;
	tok.get(is);

	if (tok.type() == ID)
	{
		result += tok.value();

		int pos = is.tellg(); // always set the pos (position back to where you will need to reset from!!!!)
		// get next token
		Token comma;
		comma.get(is);

		if (comma.type() == COMMA)
		{
			result += comma.value() + " ";
			result += idlist(is); // Recursive call for the next identifier
		}
		else
		{
			is.clear();
			is.seekg(pos);
			return result;
		}
	}

	return result;
}
// Function: declaration
// Parameters: std::ifstream& is (input stream)
// Purpose: Parses a declaration construct from the input stream.
string declaration(std::ifstream &is)
{
	int pos = is.tellg();
	// Read the type token first
	string typeValue = type(is);

	// Now parse the idlist
	string idlistValue = idlist(is);

	string result = typeValue + idlistValue;

	Token semi;
	semi.get(is);

	if (semi.type() == SEMICOLON)
	{
		result += semi.value() + "\n";
		result += declaration(is);
	}
	else
	{
		result += "\n";
		is.seekg(pos);
	}

	return getIndent() + result;
}
