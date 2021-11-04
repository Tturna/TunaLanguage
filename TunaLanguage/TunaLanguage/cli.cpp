#include "tuna.h"

using namespace std;

int main() {
	Lexer lexer = Lexer();

	while (true) {
		char cInput[256];
		cout << "Tuna> ";
		cin.getline(cInput, 256);
		string input = cInput;

		lexer.Initialize(input);
		vector<Token> tokens = lexer.MakeTokens();

		for (Token t : tokens)
			cout << t.type << ':' << t.value << ' ';

		cout << endl;
	}
}