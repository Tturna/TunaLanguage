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
		text = text_;
		pos = -1;
		currentChar = NAC;
		Advance();
	}

	/// <summary>
	/// Creates and returns a list of Tokens made from the source code this class was defined with.
	/// </summary>
	/// <returns>std::vector<IToken*></returns>
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
			else {
				try {
					tokens.push_back(new Token<>(typeMap.at(string(1, currentChar))));
				}
				catch (...){
					cout << "Lexing error: Illegal character.";
					continue;
				}
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
