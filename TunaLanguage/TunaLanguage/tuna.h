#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>

using namespace std;

//////////////////////////////////
// CONSTANTS

// Token type map, except numbers
const map<string, string> typeMap{
	{ "+", "PLUS" },
	{ "-", "MINUS" },
	{ "*", "MUL" },
	{ "/", "DIV" },
	{ "(", "LPAREN" },
	{ ")", "RPAREN" }
};

// Number types
const string TT_INT = "INT";
const string TT_FLOAT = "FLOAT";

// Other constants
const string DIGITS = "0123456789";
const char NAC = '§';

/// <summary>
/// Token class to store data about each element of code (e.g. operator, variable...)
/// </summary>
class Token {
public:
	string type;
	string value;

	Token(string type_, string value_) {
		type = type_;
		value = value_;
	}

	Token(string type_) {
		type = type_;
	}
};

class Position {
public:
	int index;
	int line;
	int column;

	Position(int index_, int line_, int column_) {
		index = index_;
		line = line_;
		column = column_;
	}

	void Advance(char currentCharacter) {
		index++;
		column++;

		if (currentCharacter == '\n') {
			line++;
			column = 0;
		}
	}
};

/// <summary>
/// Lexer or Tokenizer class to translate the source code into tokens.
/// </summary>
class Lexer {
public:
	string text = "";
	Position pos = Position(-1, 0, -1);
	char currentChar = NAC;

	Lexer() {}

	Lexer(string text_) {
		text = text_;
		Advance();
	}

	/// <summary>
	/// Advance to the next character in the source code and store it. Stores NULL if end of file.
	/// </summary>
	void Advance() {
		pos.Advance(currentChar);
		currentChar = pos.index < text.length() ? text[pos.index] : NAC;
	}

	void Initialize(string text_) {
		text = text_;
		pos = Position(-1, 0, -1);
		currentChar = NAC;
		Advance();
	}

	/// <summary>
	/// Creates and returns a list of Tokens made from the source code.
	/// </summary>
	/// <returns>std::vector<IToken*></returns>
	vector<Token> MakeTokens() {
		vector<Token> tokens;
		string tabAndSpace = " \t";

		// Iterate through all the characters in the source code string
		while (currentChar != NAC) {
			if (DIGITS.find(currentChar) != string::npos) {
				tokens.push_back(MakeNumber());
				continue;
			}
			else {
				try {
					tokens.push_back(Token(typeMap.at(string(1, currentChar))));
				}
				catch (...){
					cout << "Error: Illegal character. (ln: " + to_string(pos.line) + ", cn: " + to_string(pos.column) + ")";
					continue;
				}
			}

			Advance();
		}

		return tokens;
	}

	Token MakeNumber() {
		string numStr = "";
		bool hasDecimal = false;

		while ((DIGITS + ".").find(currentChar) != string::npos) {
			hasDecimal = currentChar == '.';
			numStr += currentChar;
			Advance();
		}

		return hasDecimal ? Token(TT_FLOAT, numStr) : Token(TT_INT, numStr);
	}
};
