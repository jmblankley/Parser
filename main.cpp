/****************************************************************
 * Author: Joshua M. Blankley                                   *
 * Date: February 2024                                          *
 *                                                              *
 * Description:                                                 *
 * This program parses a file containing grammar specifications *
 * using the Token and Grammar classes. It reads an input file  *
 * specified as a command-line argument, processes it, and      *
 * prints the resulting parsed output.                          *
 ***************************************************************/

#include <iostream>
#include <fstream>
#include <string>

#include "Grammar.hpp"
#include "Token.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	// Check if the correct number of command-line arguments is provided
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <input_file>" << endl; // Print usage message to standard error stream
		return 1;												 // Exit program with error code 1
	}

	ifstream inFile(argv[1]); // Open input file specified in command-line arguments

	if (!inFile) // Check if the input file is successfully opened
	{
		cerr << "Error: Unable to open input file." << endl; // Print error message to standard error stream
		return 1;											 // Exit program with error code 1
	}

	cout << program(inFile) << endl; // Call the program function to parse the input file and print the parsed output

	inFile.close(); // Close the input file

	return 0; // Exit program with success code 0
}
