#include "tuna.h"

using namespace std;

int main() {
	Lexer lexer = Lexer();

	while (true) {
		string input = "";
		cout << "Tuna> ";
		cin >> input;

		lexer.Initialize(input);

		vector<IToken*> tokens = lexer.MakeTokens();
		vector<string> tokenStrings = lexer.GetTokenStrings(tokens);

		int a = ((Token<int>*)tokens[0])->value;

		for (string s : tokenStrings)
			cout << s << ' ';

		cout << endl;
	}
}