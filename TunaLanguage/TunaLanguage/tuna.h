#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

//////////////////////////////////
// CONSTANTS

// Token types
const string TT_INT = "INT";
const string TT_FLOAT = "FLOAT";
const string TT_PLUS = "PLUS";
const string TT_MINUS = "MINUS";
const string TT_MUL = "MUL";
const string TT_DIV = "DIV";
const string TT_LPAREN = "LPAREN";
const string TT_RPAREN = "RPAREN";

// Other constants
const string DIGITS = "0123456789";
const char NAC = '§';

class Error {
public:
	string errorName;
	string details;

	Error() {}

	Error(string errorName_, string details_) {
		errorName = errorName_;
		details = details_;
	}

	string AsString() {
		return errorName + ": " + details;
	}
};

class IllegalCharacterError : Error {
public:

	IllegalCharacterError(string details_) {
		errorName = "Illegal Character";
		details = details_;
	}
};


class IToken {
public:
	string type;
};

template<typename T = int>
class Token : public IToken {
public:
	T value;

	Token(string type_, T value_) {
		type = type_;
		value = value_;
	}

	Token(string type_) {
		type = type_;
	}
};

/// <summary>
/// Lexer or Tokenizer class to translate the source code into tokens.
/// </summary>
class Lexer {
public:
	string text = "";
	int pos = -1;
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
		pos++;
		currentChar = pos < text.length() ? text[pos] : NAC;
	}

	void Initialize(string text_) {
		if (text != "") return;
		text = text_;
		Advance();
	}

	/// <summary>
	/// Creates and returns a list of Tokens made from the source code this class was defined with.
	/// </summary>
	/// <returns>std::list<Token></returns>
	vector<IToken*> MakeTokens() {
		vector<IToken*> tokens;
		string tabAndSpace = " \t";

		while (currentChar != NAC) {
			if (tabAndSpace.find(currentChar) != string::npos) {

			}
			else if (DIGITS.find(currentChar) != string::npos) {
				tokens.push_back(MakeNumber());
				continue;
			}
			else if (currentChar == '+') {
				tokens.push_back(new Token<>(TT_PLUS));
			}
			else if (currentChar == '-') {
				tokens.push_back(new Token<>(TT_MINUS));
			}
			else if (currentChar == '*') {
				tokens.push_back(new Token<>(TT_MUL));
			}
			else if (currentChar == '/') {
				tokens.push_back(new Token<>(TT_DIV));
			}
			else if (currentChar == '(') {
				tokens.push_back(new Token<>(TT_LPAREN));
			}
			else if (currentChar == ')') {
				tokens.push_back(new Token<>(TT_RPAREN));
			}
			else {
				throw 801;
			}

			Advance();
		}

		return tokens;
	}

	IToken* MakeNumber() {
		string numStr = "";
		bool hasDecimal = false;

		while ((DIGITS + ".").find(currentChar) != string::npos) {
			if (currentChar == '.') hasDecimal = true;

			numStr += currentChar;
			Advance();
		}

		if (hasDecimal) {
			return new Token<float>(TT_FLOAT, stof(numStr));
		}
		else {
			return new Token<int>(TT_INT, stoi(numStr));
		}
	}

	vector<string> GetTokenStrings(vector<IToken*> tokens) {
		vector<string> strings;
		for (size_t i = 0; i < tokens.size(); i++)
		{
			IToken itoken = *tokens[i];
			string type = itoken.type;

			if (type == "FLOAT") strings.push_back(type + ":" + to_string(((Token<float>*)(tokens[i]))->value));
			else if (type == "INT") strings.push_back(type + ":" + to_string(((Token<int>*)(tokens[i]))->value));
			else strings.push_back(type);
		}

		return strings;
	}
};
